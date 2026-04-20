#include <omnetpp.h>
#include <map>
#include <set>
#include <queue>
#include "DroneAuthMessages_m.h"
#include "CryptoUtils.h"
#include "RateLimiter.h"
#include "RequestValidator.h"
#include "HeartbeatMonitor.h"
#include "StateSynchronizer.h"

using namespace omnetpp;

class GroundControl : public cSimpleModule {
private:
    struct DroneInfo {
        long long publicKey;
        long long lastCommitment;
        long long lastChallenge;
        simtime_t lastAuthTime;
        std::set<std::string> usedCommitments;
        bool authenticated;
        int authCount;
        int gateIndex;
    };

    struct PendingRequest {
        cMessage *msg;
        int gateIndex;
        simtime_t arrivalTime;
        bool highPriority;
    };

    std::map<int, DroneInfo> registeredDrones;
    std::queue<PendingRequest> highPriorityQueue;
    std::queue<PendingRequest> lowPriorityQueue;
    
    int maxQueueSize;
    RateLimiter *rateLimiter;
    RequestValidator *validator;
    bool dosProtectionEnabled;
    double processingDelay;
    cMessage *queueProcessTimer;
    bool isProcessing;

    // Phase 2: Dual GCS support
    HeartbeatMonitor *heartbeatMonitor;
    StateSynchronizer *stateSynchronizer;
    cMessage *heartbeatTimer;
    bool isDualGCSMode;
    int backupGateIndex;

    simsignal_t authRequestsSignal;
    simsignal_t authSuccessfulSignal;
    simsignal_t authFailedSignal;
    simsignal_t replayDetectedSignal;
    simsignal_t rateLimitHitsSignal;
    simsignal_t validationFailuresSignal;
    simsignal_t queueDropsSignal;
    simsignal_t queueOverflowSignal;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    void handleCommitment(AuthCommit *msg, int gateIndex);
    void handleResponse(AuthResponse *msg, int gateIndex);
    void enqueueRequest(cMessage *msg, int gateIndex, bool highPriority);
    void processQueue();
    void sendAuthResult(int droneId, bool authenticated, const char *reason, int gateIndex);
    void cleanupQueues();
    // Phase 2 methods
    void sendHeartbeatToBackup();
    void syncStateToBackup(int droneId);
};

Define_Module(GroundControl);

void GroundControl::initialize() {
    authRequestsSignal = registerSignal("authRequests");
    authSuccessfulSignal = registerSignal("authSuccessful");
    authFailedSignal = registerSignal("authFailed");
    replayDetectedSignal = registerSignal("replayDetected");
    rateLimitHitsSignal = registerSignal("rateLimitHits");
    validationFailuresSignal = registerSignal("validationFailures");
    queueDropsSignal = registerSignal("queueDrops");
    queueOverflowSignal = registerSignal("queueOverflow");

    dosProtectionEnabled = par("dosProtectionEnabled").boolValue();
    maxQueueSize = par("maxQueueSize").intValue();
    processingDelay = par("processingDelay").doubleValue();
    isProcessing = false;
    
    if (dosProtectionEnabled) {
        int maxReq = par("maxRequestsPerWindow").intValue();
        double window = par("rateLimitWindow").doubleValue();
        rateLimiter = new RateLimiter(maxReq, window);
        
        double maxAge = par("maxMessageAge").doubleValue();
        int minId = par("minValidDroneId").intValue();
        int maxId = par("maxValidDroneId").intValue();
        validator = new RequestValidator(maxAge, minId, maxId);
        
        EV << "GCS WITH DoS protection" << endl;
    } else {
        rateLimiter = nullptr;
        validator = nullptr;
        EV << "GCS WITHOUT DoS protection" << endl;
    }

    queueProcessTimer = new cMessage("queueProcessTimer");
    scheduleAt(simTime() + processingDelay, queueProcessTimer);

isDualGCSMode = par("dualGCSMode").boolValue();
    
    if (isDualGCSMode) {
        double heartbeatInterval = par("heartbeatInterval").doubleValue();
        double heartbeatTimeout = par("heartbeatTimeout").doubleValue();
        
        // Create monitoring components (Primary sends, doesn't monitor)
        heartbeatMonitor = new HeartbeatMonitor(this, true, heartbeatInterval, heartbeatTimeout);
        stateSynchronizer = new StateSynchronizer(this, true);
        
        // Find backup gate (last gate is backup connection)
        backupGateIndex = gateSize("gate") - 1;
        
        // Start heartbeat timer
        heartbeatTimer = new cMessage("sendHeartbeat");
        scheduleAt(simTime() + heartbeatInterval, heartbeatTimer);
        
        EV << "PrimaryGCS: Dual GCS mode enabled" << endl;
        EV << "  Heartbeat interval: " << heartbeatInterval << "s" << endl;
        EV << "  Backup gate index: " << backupGateIndex << endl;
    } else {
        heartbeatMonitor = nullptr;
        stateSynchronizer = nullptr;
        heartbeatTimer = nullptr;
        EV << "PrimaryGCS: Single GCS mode (no backup)" << endl;
    }

}

void GroundControl::handleMessage(cMessage *msg) {
    if (msg == heartbeatTimer) {
        sendHeartbeatToBackup();
        // Schedule next heartbeat
        double interval = heartbeatMonitor->getHeartbeatInterval();
        scheduleAt(simTime() + interval, heartbeatTimer);
        return;
    }

    if (msg == queueProcessTimer) {
        isProcessing = false;
        processQueue();
        return;
    }

    if (AuthCommit *commit = dynamic_cast<AuthCommit*>(msg)) {
        int gateIndex = msg->getArrivalGate()->getIndex();
        int droneId = commit->getDroneId();
        
        // CRITICAL: Check rate limit and validation BEFORE queueing!
        emit(authRequestsSignal, 1L);
        
        // Step 1: Validation first
        if (dosProtectionEnabled && validator) {
            std::string reason;
            if (!validator->validateCommitment(commit, simTime(), reason)) {
                emit(validationFailuresSignal, 1L);
                sendAuthResult(droneId, false, reason.c_str(), gateIndex);
                delete msg;
                return;
            }
        }
        
        // Step 2: Rate limiting BEFORE queue
        if (dosProtectionEnabled && rateLimiter) {
            if (!rateLimiter->checkRequestByGate(gateIndex, droneId, simTime())) {
                emit(rateLimitHitsSignal, 1L);
                sendAuthResult(droneId, false, "Rate limit exceeded", gateIndex);
                delete msg;
                return;
            }
        }
        
        // Step 3: Now queue it
        bool highPriority = (registeredDrones.find(droneId) != registeredDrones.end() &&
                            registeredDrones[droneId].authenticated &&
                            registeredDrones[droneId].gateIndex == gateIndex);
        
        enqueueRequest(msg, gateIndex, highPriority);
        
        if (!isProcessing) {
            processQueue();
        }
    }
    else if (AuthResponse *response = dynamic_cast<AuthResponse*>(msg)) {
        int gateIndex = msg->getArrivalGate()->getIndex();
        handleResponse(response, gateIndex);
    }
    else {
        delete msg;
    }
}

void GroundControl::enqueueRequest(cMessage *msg, int gateIndex, bool highPriority) {
    int totalQueueSize = highPriorityQueue.size() + lowPriorityQueue.size();
    
    if (totalQueueSize >= maxQueueSize) {
        emit(queueOverflowSignal, 1L);
        AuthCommit *commit = dynamic_cast<AuthCommit*>(msg);
        if (commit) {
            EV << "QUEUE OVERFLOW - Dropping request from drone " << commit->getDroneId() << endl;
            sendAuthResult(commit->getDroneId(), false, "Queue overflow", gateIndex);
        }
        delete msg;
        return;
    }

    PendingRequest req;
    req.msg = msg;
    req.gateIndex = gateIndex;
    req.arrivalTime = simTime();
    req.highPriority = highPriority;

    if (highPriority) {
        highPriorityQueue.push(req);
    } else {
        lowPriorityQueue.push(req);
    }
}

void GroundControl::processQueue() {
    if (isProcessing) return;

    PendingRequest req;
    bool hasRequest = false;

    if (!highPriorityQueue.empty()) {
        req = highPriorityQueue.front();
        highPriorityQueue.pop();
        hasRequest = true;
    } else if (!lowPriorityQueue.empty()) {
        req = lowPriorityQueue.front();
        lowPriorityQueue.pop();
        hasRequest = true;
    }

    if (hasRequest) {
        isProcessing = true;
        AuthCommit *commit = dynamic_cast<AuthCommit*>(req.msg);
        if (commit) {
            handleCommitment(commit, req.gateIndex);
        }
        scheduleAt(simTime() + processingDelay, queueProcessTimer);
    }
}

void GroundControl::handleCommitment(AuthCommit *msg, int gateIndex) {
    int droneId = msg->getDroneId();
    std::string commitmentStr = msg->getCommitment();
    
    // Replay detection
    if (registeredDrones.find(droneId) != registeredDrones.end()) {
        if (registeredDrones[droneId].usedCommitments.count(commitmentStr) > 0) {
            emit(replayDetectedSignal, 1L);
            sendAuthResult(droneId, false, "Replay attack", gateIndex);
            delete msg;
            return;
        }
    }

    long long challenge = CryptoUtils::random(1, CryptoUtils::getPrime() - 1);
    long long commitment = CryptoUtils::fromString(commitmentStr);

    if (registeredDrones.find(droneId) == registeredDrones.end()) {
        DroneInfo info;
        info.publicKey = 0;
        info.authenticated = false;
        info.authCount = 0;
        info.gateIndex = gateIndex;
        registeredDrones[droneId] = info;
    }

    registeredDrones[droneId].lastCommitment = commitment;
    registeredDrones[droneId].lastChallenge = challenge;
    registeredDrones[droneId].usedCommitments.insert(commitmentStr);

    AuthChallenge *challengeMsg = new AuthChallenge();
    challengeMsg->setDroneId(droneId);
    challengeMsg->setChallenge(CryptoUtils::toString(challenge).c_str());
    challengeMsg->setTimestamp(simTime());

    send(challengeMsg, "gate$o", gateIndex);
    delete msg;
}

void GroundControl::sendHeartbeatToBackup() {
    if (!isDualGCSMode || !heartbeatMonitor) return;
    
    // Count active drones
    int activeDrones = 0;
    for (const auto &pair : registeredDrones) {
        if (pair.second.authenticated) {
            activeDrones++;
        }
    }
    
    // Create heartbeat message
    HeartbeatMessage *hb = heartbeatMonitor->createHeartbeat(simTime(), activeDrones);
    
    if (hb && gate("gate$o", backupGateIndex)->isConnected()) {
        send(hb, "gate$o", backupGateIndex);
        EV << "PrimaryGCS: Sent heartbeat to Backup (active drones: " 
           << activeDrones << ")" << endl;
    } else if (hb) {
        delete hb;  // No backup connected
    }
}

void GroundControl::handleResponse(AuthResponse *msg, int gateIndex) {
    int droneId = msg->getDroneId();
    
    if (registeredDrones.find(droneId) == registeredDrones.end()) {
        sendAuthResult(droneId, false, "No pending challenge", gateIndex);
        delete msg;
        return;
    }
    
    long long response = CryptoUtils::fromString(msg->getResponse());
    bool authenticated = (response > 0);

    if (authenticated) {
        emit(authSuccessfulSignal, 1L);
        registeredDrones[droneId].lastAuthTime = simTime();
        registeredDrones[droneId].authenticated = true;
        registeredDrones[droneId].authCount++;
        registeredDrones[droneId].gateIndex = gateIndex;
        
        if (dosProtectionEnabled && rateLimiter) {
            rateLimiter->addAuthenticatedDrone(droneId);
        }

	if (isDualGCSMode && stateSynchronizer) {
            syncStateToBackup(droneId);
        } 
       
        sendAuthResult(droneId, true, "Valid proof", gateIndex);
    } else {
        emit(authFailedSignal, 1L);
        sendAuthResult(droneId, false, "Invalid proof", gateIndex);
    }
    
    delete msg;
}

void GroundControl::sendAuthResult(int droneId, bool authenticated, const char *reason, int gateIndex) {
    AuthResult *result = new AuthResult();
    result->setDroneId(droneId);
    result->setAuthenticated(authenticated);
    result->setReason(reason);
    result->setTimestamp(simTime());
    send(result, "gate$o", gateIndex);
}

void GroundControl::cleanupQueues() {
    while (!highPriorityQueue.empty()) {
        delete highPriorityQueue.front().msg;
        highPriorityQueue.pop();
    }
    while (!lowPriorityQueue.empty()) {
        delete lowPriorityQueue.front().msg;
        lowPriorityQueue.pop();
    }
}

void GroundControl::syncStateToBackup(int droneId) {
    if (!isDualGCSMode || !stateSynchronizer) return;
    
    auto it = registeredDrones.find(droneId);
    if (it == registeredDrones.end()) return;
    
    DroneInfo &info = it->second;
    
    // Create sync message
    StateSyncMessage *sync = stateSynchronizer->createSyncMessage(
        droneId,
        info.authenticated,
        std::to_string(info.lastCommitment),
        info.publicKey,
        info.lastAuthTime,
        info.authCount,
        simTime()
    );
    
    if (sync && gate("gate$o", backupGateIndex)->isConnected()) {
        send(sync, "gate$o", backupGateIndex);
        EV << "PrimaryGCS: Synced state for drone " << droneId << " to Backup" << endl;
    } else if (sync) {
        delete sync;
    }
}

void GroundControl::finish() {
    cleanupQueues();
    
    // Add null checks before deleting
    if (queueProcessTimer) {
        cancelAndDelete(queueProcessTimer);
        queueProcessTimer = nullptr;
    }
    
    if (dosProtectionEnabled) {
        if (rateLimiter) {
            EV << "DoS Protection: Blocked=" << rateLimiter->getBlockedRequests() << endl;
            delete rateLimiter;
            rateLimiter = nullptr;
        }
        if (validator) {
            delete validator;
            validator = nullptr;
        }
    }

    if (heartbeatTimer) {
        cancelAndDelete(heartbeatTimer);
        heartbeatTimer = nullptr;
    }

    if (isDualGCSMode) {
        EV << "=== Primary GCS Dual Mode Statistics ===" << endl;
        if (heartbeatMonitor) {
            EV << "Heartbeats sent: " << heartbeatMonitor->getHeartbeatsSent() << endl;
            delete heartbeatMonitor;
            heartbeatMonitor = nullptr;
        }
        if (stateSynchronizer) {
            EV << "State syncs sent: " << stateSynchronizer->getSyncMessagesSent() << endl;
            delete stateSynchronizer;
            stateSynchronizer = nullptr;
        }
    }
}
