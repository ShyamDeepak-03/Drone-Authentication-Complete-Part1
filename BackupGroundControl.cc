#include "BackupGroundControl.h"

BackupGroundControl::BackupGroundControl() {
    isPrimary = false;
    isActive = false;
    heartbeatMonitor = nullptr;
    stateSynchronizer = nullptr;
    heartbeatCheckTimer = nullptr;
    failoverInProgress = false;
    dronesReconnected = 0;
}

BackupGroundControl::~BackupGroundControl() {
    cancelAndDelete(heartbeatCheckTimer);
    delete heartbeatMonitor;
    delete stateSynchronizer;
}

void BackupGroundControl::initialize() {
    // Call parent initialization
    GroundControl::initialize();
    
    // Initialize as BACKUP (not primary)
    isPrimary = false;
    isActive = false;
    
    // Create monitoring components
    double heartbeatInterval = par("heartbeatInterval").doubleValue();
    double heartbeatTimeout = par("heartbeatTimeout").doubleValue();
    heartbeatMonitor = new HeartbeatMonitor(this, false, heartbeatInterval, heartbeatTimeout);
    
    stateSynchronizer = new StateSynchronizer(this, false);
    
    // Register signals
    failoverTriggeredSignal = registerSignal("failoverTriggered");
    failoverCompleteSignal = registerSignal("failoverComplete");
    heartbeatReceivedSignal = registerSignal("heartbeatReceived");
    stateSyncReceivedSignal = registerSignal("stateSyncReceived");
    
    // Start heartbeat monitoring
    heartbeatCheckTimer = new cMessage("heartbeatCheck");
    scheduleAt(simTime() + 0.5, heartbeatCheckTimer);
    
    EV << "BackupGCS initialized in STANDBY mode" << endl;
    EV << "  Heartbeat timeout: " << heartbeatTimeout << "s" << endl;
    EV << "  Monitoring Primary GCS..." << endl;
}

void BackupGroundControl::handleMessage(cMessage *msg) {
    // Check message type
    if (msg == heartbeatCheckTimer) {
        checkPrimaryHealth();
        // Schedule next check
        scheduleAt(simTime() + 0.5, heartbeatCheckTimer);
        return;
    }
    
    // Handle heartbeat from Primary
    if (HeartbeatMessage *hb = dynamic_cast<HeartbeatMessage*>(msg)) {
        handleHeartbeat(hb);
        delete msg;
        return;
    }
    
    // Handle state sync from Primary
    if (StateSyncMessage *sync = dynamic_cast<StateSyncMessage*>(msg)) {
        handleStateSync(sync);
        delete msg;
        return;
    }
    
    // Handle GCS switch acknowledgment from drones
    if (GCSSwitchAckMessage *ack = dynamic_cast<GCSSwitchAckMessage*>(msg)) {
        handleGCSSwitchAck(ack);
        delete msg;
        return;
    }
    
    // If we're ACTIVE (after failover), handle normal GCS messages
    if (isActive) {
        GroundControl::handleMessage(msg);
    } else {
        // In STANDBY mode, ignore drone messages
        delete msg;
    }
}

void BackupGroundControl::handleHeartbeat(HeartbeatMessage *msg) {
    emit(heartbeatReceivedSignal, 1L);
    heartbeatMonitor->recordHeartbeat(msg, simTime());
    
    EV << "BackupGCS: Received heartbeat from Primary" << endl;
    EV << "  Status: " << msg->getStatus() << endl;
    EV << "  Active drones: " << msg->getActiveDrones() << endl;
}

void BackupGroundControl::checkPrimaryHealth() {
    if (isActive) return; // Already active, no need to check
    if (failoverInProgress) return; // Failover already in progress
    
    bool primaryDead = heartbeatMonitor->isPrimaryDead(simTime());
    
    if (primaryDead) {
        EV << "================================================================" << endl;
        EV << "BackupGCS: PRIMARY GCS FAILURE DETECTED!" << endl;
        EV << "  Time since last heartbeat: " 
           << heartbeatMonitor->getTimeSinceLastHeartbeat(simTime()) << "s" << endl;
        EV << "  Timeout threshold: " 
           << heartbeatMonitor->getHeartbeatTimeout() << "s" << endl;
        EV << "================================================================" << endl;
        
        triggerFailover();
    }
}

void BackupGroundControl::handleStateSync(StateSyncMessage *msg) {
    emit(stateSyncReceivedSignal, 1L);
    stateSynchronizer->applySyncMessage(msg, simTime());
    
    EV << "BackupGCS: State synchronized for drone " << msg->getDroneId() << endl;
}

void BackupGroundControl::handleGCSSwitchAck(GCSSwitchAckMessage *msg) {
    if (!failoverInProgress) return;
    
    dronesReconnected++;
    
    EV << "BackupGCS: Drone " << msg->getDroneId() 
       << " confirmed switch (total: " << dronesReconnected << ")" << endl;
    
    // Check if all drones have reconnected
    // (In real implementation, you'd track expected number of drones)
}

void BackupGroundControl::triggerFailover() {
    EV << "================================================================" << endl;
    EV << "BackupGCS: INITIATING FAILOVER PROCEDURE" << endl;
    EV << "================================================================" << endl;
    
    emit(failoverTriggeredSignal, 1L);
    
    failoverInProgress = true;
    failoverStartTime = simTime();
    dronesReconnected = 0;
    
    // Step 1: Change state to ACTIVE
    isPrimary = true;
    isActive = true;
    
    EV << "BackupGCS: Changed state to ACTIVE" << endl;
    
    // Step 2: Load synchronized state
    EV << "BackupGCS: Loading synchronized state..." << endl;
    std::vector<int> syncedDrones = stateSynchronizer->getSynchronizedDrones();
    EV << "  Found " << syncedDrones.size() << " synchronized drones" << endl;
    
    // TODO: Apply synchronized state to GroundControl's registeredDrones
    // This requires accessing parent class's private members
    // For now, we'll continue with failover
    
    // Step 3: Broadcast announcement to all drones
    broadcastGCSAnnouncement();
    
    // Step 4: Complete failover
    scheduleAt(simTime() + 0.5, new cMessage("completeFailover"));
}

void BackupGroundControl::broadcastGCSAnnouncement() {
    EV << "BackupGCS: Broadcasting GCS announcement to all drones..." << endl;
    
    GCSAnnouncementMessage *announcement = new GCSAnnouncementMessage();
    announcement->setNewPrimaryAddress("BackupGCS");
    announcement->setReason("failover");
    announcement->setTimestamp(simTime());
    announcement->setDroneCount(5); // TODO: Get actual drone count
    
    // Broadcast to all connected drones
    int numGates = gateSize("gate");
    for (int i = 0; i < numGates; i++) {
        if (gate("gate$o", i)->isConnected()) {
            GCSAnnouncementMessage *copy = announcement->dup();
            send(copy, "gate$o", i);
            EV << "  Sent announcement to gate " << i << endl;
        }
    }
    
    delete announcement;
}

void BackupGroundControl::completeFailover() {
    failoverCompleteTime = simTime();
    double failoverDuration = (failoverCompleteTime - failoverStartTime).dbl();
    
    emit(failoverCompleteSignal, failoverDuration);
    
    EV << "================================================================" << endl;
    EV << "BackupGCS: FAILOVER COMPLETE!" << endl;
    EV << "  Start time: " << failoverStartTime << endl;
    EV << "  End time: " << failoverCompleteTime << endl;
    EV << "  Duration: " << failoverDuration << " seconds" << endl;
    EV << "  Drones reconnected: " << dronesReconnected << endl;
    EV << "  Status: OPERATIONAL" << endl;
    EV << "================================================================" << endl;
    
    failoverInProgress = false;
    
    // Send failover complete message
    FailoverCompleteMessage *complete = new FailoverCompleteMessage();
    complete->setDronesReconnected(dronesReconnected);
    complete->setFailoverStartTime(failoverStartTime);
    complete->setFailoverEndTime(failoverCompleteTime);
    complete->setFailoverDuration(failoverDuration);
    
    // Could send this to monitoring system or log it
    delete complete;
}

void BackupGroundControl::finish() {
    // Cleanup our own timers FIRST
//    if (heartbeatCheckTimer) {
  //      cancelAndDelete(heartbeatCheckTimer);
    //    heartbeatCheckTimer = nullptr;
//    }
    
//    EV << "=== BackupGCS Statistics ===" << endl;
    
  //  if (heartbeatMonitor) {
    //    EV << "Heartbeats received: " << heartbeatMonitor->getHeartbeatsReceived() << endl;
     //   delete heartbeatMonitor;
     //   heartbeatMonitor = nullptr;
   // }
    
    //if (stateSynchronizer) {
      //  EV << "State syncs received: " << stateSynchronizer->getSyncMessagesReceived() << endl;
       // EV << "Synchronized drones: " << stateSynchronizer->getSynchronizedDroneCount() << endl;
        //delete stateSynchronizer;
       // stateSynchronizer = nullptr;
    // }
    
   // if (isActive) {
     //   EV << "Final state: ACTIVE (took over from Primary)" << endl;
       // double failoverDuration = (failoverCompleteTime - failoverStartTime).dbl();
      //  EV << "Failover duration: " << failoverDuration << " seconds" << endl;
   // } else {
    //    EV << "Final state: STANDBY (no failover occurred)" << endl;
    //}
    
    // Set parent pointers to null so parent finish doesn't try to delete them again
    //GroundControl::heartbeatMonitor = nullptr;
    //GroundControl::stateSynchronizer = nullptr;
    //GroundControl::heartbeatTimer = nullptr;
    
    // Now safe to call parent finish
    //GroundControl::finish();
}
