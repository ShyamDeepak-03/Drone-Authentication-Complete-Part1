#include <omnetpp.h>
#include "DroneAuthMessages_m.h"
#include "CryptoUtils.h"

using namespace omnetpp;

class Drone : public cSimpleModule {
private:
    int droneId;
    long long privateKey;
    long long publicKey;
    long long randomNonce;
    simtime_t authStartTime;
    cMessage *authTimer;
    std::string currentGCS;
    bool gcsFailoverEnabled;
    bool authenticationPending;
    
    // Statistics
    simsignal_t authAttemptsSignal;
    simsignal_t authSuccessSignal;
    simsignal_t authDelaySignal;
    
protected:
    void handleGCSAnnouncement(GCSAnnouncementMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    
    void startAuthentication();
    void handleChallenge(AuthChallenge *msg);
    void handleAuthResult(AuthResult *msg);
};

Define_Module(Drone);

void Drone::initialize() {
    droneId = par("droneId");
    
    // Crypto setup
    privateKey = CryptoUtils::random(1, CryptoUtils::getPrime() - 1);
    publicKey = CryptoUtils::generatePublicKey(privateKey);
    // Phase 2
    gcsFailoverEnabled = par("gcsFailoverEnabled").boolValue();
    currentGCS = "PrimaryGCS";
    authenticationPending = false;
    
    // Signals
    authAttemptsSignal = registerSignal("authAttempts");
    authSuccessSignal = registerSignal("authSuccess");
    authDelaySignal = registerSignal("authDelay");
    
    // Create and schedule auth timer
    authTimer = new cMessage("authTimer");
    scheduleAt(simTime() + par("authInterval"), authTimer);
    
    EV << "Drone " << droneId << " initialized" << endl;
}

void Drone::handleMessage(cMessage *msg) {
    // Phase 2: Handle GCS announcement
    if (GCSAnnouncementMessage *announcement = dynamic_cast<GCSAnnouncementMessage*>(msg)) {
        handleGCSAnnouncement(announcement);
        delete msg;
        return;
    }

    if (msg == authTimer) {
        startAuthentication();
        scheduleAt(simTime() + par("authInterval"), authTimer);
    }
    else if (AuthChallenge *challenge = dynamic_cast<AuthChallenge*>(msg)) {
        handleChallenge(challenge);
    }
    else if (AuthResult *result = dynamic_cast<AuthResult*>(msg)) {
        handleAuthResult(result);
    }
    else {
        delete msg;
    }
}

void Drone::handleGCSAnnouncement(GCSAnnouncementMessage *msg) {
    if (!gcsFailoverEnabled) {
        EV << "Drone " << droneId << ": Ignoring GCS announcement (failover disabled)" << endl;
        return;
    }
    
    std::string oldGCS = currentGCS;
    currentGCS = msg->getNewPrimaryAddress();
    
    EV << "================================================================" << endl;
    EV << "Drone " << droneId << ": GCS SWITCH NOTIFICATION" << endl;
    EV << "  Old GCS: " << oldGCS << endl;
    EV << "  New GCS: " << currentGCS << endl;
    EV << "  Reason: " << msg->getReason() << endl;
    EV << "  Time: " << msg->getTimestamp() << endl;
    EV << "================================================================" << endl;
    
    // Send acknowledgment
    GCSSwitchAckMessage *ack = new GCSSwitchAckMessage();
    ack->setDroneId(droneId);
    ack->setNewGCS(currentGCS.c_str());
    ack->setSwitchTime(simTime());
    ack->setSuccessful(true);
    
    send(ack, "gate$o");
    
    // If we had pending authentication, retry with new GCS
    if (authenticationPending) {
        EV << "Drone " << droneId << ": Retrying authentication with new GCS" << endl;
        cancelEvent(authTimer);
        scheduleAt(simTime() + 0.1, authTimer);
    }
}

void Drone::startAuthentication() {
    emit(authAttemptsSignal, 1L);
    authStartTime = simTime();
    
    // Phase 1: Generate random nonce and commitment
    randomNonce = CryptoUtils::random(1, CryptoUtils::getPrime() - 1);
    long long commitment = CryptoUtils::modPow(
        CryptoUtils::getGenerator(), 
        randomNonce, 
        CryptoUtils::getPrime()
    );
    
    // Send commitment to GCS
    AuthCommit *commitMsg = new AuthCommit();
    commitMsg->setDroneId(droneId);
    commitMsg->setCommitment(CryptoUtils::toString(commitment).c_str());
    commitMsg->setTimestamp(simTime());
    
    EV << "Drone " << droneId << " sending commitment: " << commitment << endl;
    send(commitMsg, "gate$o");
}

void Drone::handleChallenge(AuthChallenge *msg) {
    // Phase 3: Compute response s = r + c*x mod (p-1)
    long long challenge = CryptoUtils::fromString(msg->getChallenge());
    long long p = CryptoUtils::getPrime();
    
    long long response = (randomNonce + challenge * privateKey) % (p - 1);
    if (response < 0) response += (p - 1);
    
    // Send response
    AuthResponse *responseMsg = new AuthResponse();
    responseMsg->setDroneId(droneId);
    responseMsg->setResponse(CryptoUtils::toString(response).c_str());
    responseMsg->setTimestamp(simTime());
    
    EV << "Drone " << droneId << " sending response: " << response << endl;
    send(responseMsg, "gate$o");
    
    delete msg;
}

void Drone::handleAuthResult(AuthResult *msg) {
    simtime_t delay = simTime() - authStartTime;
    emit(authDelaySignal, delay);
    
    if (msg->getAuthenticated()) {
        emit(authSuccessSignal, 1L);
        EV << "Drone " << droneId << " authenticated successfully in " << delay << "s" << endl;
    } else {
        EV << "Drone " << droneId << " authentication FAILED: " << msg->getReason() << endl;
    }
    
    delete msg;
}

void Drone::finish() {
    cancelAndDelete(authTimer);
}
