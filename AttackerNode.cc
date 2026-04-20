#include <omnetpp.h>
#include "DroneAuthMessages_m.h"

using namespace omnetpp;

class AttackerNode : public cSimpleModule {
private:
    int attackerId;
    std::string attackType;
    int targetDroneId;
    cMessage *attackTimer;
    cMessage *dosFloodTimer;
    int dosRequestsPerSecond;
    int dosCurrentBurst;
    simsignal_t attackAttemptsSignal;
    simsignal_t dosRequestsSentSignal;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    void performReplayAttack();
    void performImpersonationAttack();
    void performDoSAttack();
    void sendFakeRequest();
};

Define_Module(AttackerNode);

void AttackerNode::initialize() {
    attackerId = par("attackerId");
    attackType = par("attackType").stdstringValue();
    targetDroneId = par("targetDroneId");
    dosRequestsPerSecond = par("dosRequestsPerSecond").intValue();
    dosCurrentBurst = 0;

    attackAttemptsSignal = registerSignal("attackAttempts");
    dosRequestsSentSignal = registerSignal("dosRequestsSent");

    attackTimer = new cMessage("attackTimer");
    scheduleAt(simTime() + par("attackInterval"), attackTimer);

    if (attackType == "dos") {
        dosFloodTimer = new cMessage("dosFloodTimer");
        scheduleAt(simTime() + 0.001, dosFloodTimer);
    } else {
        dosFloodTimer = nullptr;
    }
}

void AttackerNode::handleMessage(cMessage *msg) {
    if (msg == attackTimer) {
        if (attackType == "replay") {
            performReplayAttack();
        } else if (attackType == "impersonation") {
            performImpersonationAttack();
        } else if (attackType == "dos") {
            performDoSAttack();
        }
        scheduleAt(simTime() + par("attackInterval"), attackTimer);
    }
    else if (msg == dosFloodTimer) {
        if (attackType == "dos") {
            sendFakeRequest();
            double interval = 1.0 / dosRequestsPerSecond;
            scheduleAt(simTime() + interval, dosFloodTimer);
        }
    }
    else {
        delete msg;
    }
}

void AttackerNode::performReplayAttack() {
    emit(attackAttemptsSignal, 1L);
    AuthCommit *replay = new AuthCommit();
    replay->setDroneId(targetDroneId);
    replay->setCommitment("123456789");
    replay->setTimestamp(simTime() - 15.0);
    send(replay, "gate$o");
}

void AttackerNode::performImpersonationAttack() {
    emit(attackAttemptsSignal, 1L);
    AuthCommit *fake = new AuthCommit();
    fake->setDroneId(targetDroneId);
    fake->setCommitment("999999999");
    fake->setTimestamp(simTime());
    send(fake, "gate$o");
}

void AttackerNode::performDoSAttack() {
    emit(attackAttemptsSignal, 1L);
}

void AttackerNode::sendFakeRequest() {
    emit(dosRequestsSentSignal, 1L);
    dosCurrentBurst++;
    
    AuthCommit *fake = new AuthCommit();
    
    // KEY: Use INVALID IDs (1000+) so validation can catch them
    // WITHOUT validation: these flood the queue
    // WITH validation: these get rejected immediately
    int fakeDroneId = 1000 + uniform(0, 9999);
    
    fake->setDroneId(fakeDroneId);
    
    char commitStr[32];
    sprintf(commitStr, "%lld", (long long)(uniform(100000, 999999999)));
    fake->setCommitment(commitStr);
    fake->setTimestamp(simTime());
    
    send(fake, "gate$o");
}

void AttackerNode::finish() {
    cancelAndDelete(attackTimer);
    if (dosFloodTimer != nullptr) {
        cancelAndDelete(dosFloodTimer);
    }
}
