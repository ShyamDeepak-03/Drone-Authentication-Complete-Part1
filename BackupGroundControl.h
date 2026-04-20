#ifndef BACKUPGROUNDCONTROL_H
#define BACKUPGROUNDCONTROL_H

#include <omnetpp.h>
#include "GroundControl.h"
#include "HeartbeatMonitor.h"
#include "StateSynchronizer.h"
#include "DroneAuthMessages_m.h"

using namespace omnetpp;

/**
 * BackupGroundControl - Backup GCS with automatic failover capability
 * 
 * Operates in STANDBY mode monitoring Primary GCS
 * Automatically takes over if Primary fails
 */
class BackupGroundControl : public GroundControl {
private:
    // Backup-specific state
    bool isPrimary;              // Is this node currently primary?
    bool isActive;               // Is this node actively serving drones?
    
    // Monitoring components
    HeartbeatMonitor *heartbeatMonitor;
    StateSynchronizer *stateSynchronizer;
    
    // Timers
    cMessage *heartbeatCheckTimer;
    
    // Failover tracking
    simtime_t failoverStartTime;
    simtime_t failoverCompleteTime;
    bool failoverInProgress;
    int dronesReconnected;
    
    // Signals
    simsignal_t failoverTriggeredSignal;
    simsignal_t failoverCompleteSignal;
    simsignal_t heartbeatReceivedSignal;
    simsignal_t stateSyncReceivedSignal;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    
    // Heartbeat handling
    void handleHeartbeat(HeartbeatMessage *msg);
    void checkPrimaryHealth();
    
    // State sync handling
    void handleStateSync(StateSyncMessage *msg);
    
    // GCS switch handling
    void handleGCSSwitchAck(GCSSwitchAckMessage *msg);
    
    // Failover
    void triggerFailover();
    void completeFailover();
    void broadcastGCSAnnouncement();

public:
    BackupGroundControl();
    virtual ~BackupGroundControl();
};

Define_Module(BackupGroundControl);

#endif
