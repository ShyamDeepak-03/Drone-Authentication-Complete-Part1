#ifndef GROUNDCONTROL_H
#define GROUNDCONTROL_H

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
protected:
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

#endif
