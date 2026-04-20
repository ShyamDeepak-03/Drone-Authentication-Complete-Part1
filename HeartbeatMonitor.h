#ifndef HEARTBEATMONITOR_H
#define HEARTBEATMONITOR_H

#include <omnetpp.h>
#include "DroneAuthMessages_m.h"

using namespace omnetpp;

/**
 * HeartbeatMonitor - Manages heartbeat between Primary and Backup GCS
 * 
 * Primary Side: Sends heartbeats
 * Backup Side: Monitors heartbeats and detects failures
 */
class HeartbeatMonitor {
private:
    // Configuration
    double heartbeatInterval;       // How often to send (seconds)
    double heartbeatTimeout;        // When to consider Primary dead (seconds)
    
    // State
    simtime_t lastHeartbeatSent;    // Last time we sent heartbeat
    simtime_t lastHeartbeatReceived; // Last time we received heartbeat
    bool isPrimary;                 // Are we the primary GCS?
    
    // Statistics
    long heartbeatsSent;
    long heartbeatsReceived;
    long missedHeartbeats;
    
    // OMNeT++ module reference
    cSimpleModule *module;

public:
    HeartbeatMonitor(cSimpleModule *mod, bool primary = true, 
                     double interval = 1.0, double timeout = 3.0) 
        : module(mod), isPrimary(primary), 
          heartbeatInterval(interval), heartbeatTimeout(timeout),
          heartbeatsSent(0), heartbeatsReceived(0), missedHeartbeats(0) {
        lastHeartbeatSent = 0;
        lastHeartbeatReceived = 0;
    }

    /**
     * PRIMARY: Create and return a heartbeat message to send
     */
    HeartbeatMessage* createHeartbeat(simtime_t currentTime, int activeDrones) {
        if (!isPrimary) return nullptr;
        
        HeartbeatMessage *hb = new HeartbeatMessage();
        hb->setSenderGCS("PrimaryGCS");
        hb->setTimestamp(currentTime);
        hb->setStatus("alive");
        hb->setActiveDrones(activeDrones);
        
        lastHeartbeatSent = currentTime;
        heartbeatsSent++;
        
        return hb;
    }

    /**
     * BACKUP: Record received heartbeat
     */
    void recordHeartbeat(HeartbeatMessage *hb, simtime_t currentTime) {
        if (isPrimary) return; // Primary doesn't monitor heartbeats
        
        lastHeartbeatReceived = currentTime;
        heartbeatsReceived++;
        
        // Reset missed counter
        missedHeartbeats = 0;
        
        EV << "HeartbeatMonitor: Received heartbeat from " 
           << hb->getSenderGCS() 
           << " at " << currentTime << endl;
    }

    /**
     * BACKUP: Check if Primary is still alive
     * Returns true if Primary is considered DEAD
     */
    bool isPrimaryDead(simtime_t currentTime) {
        if (isPrimary) return false; // Primary can't be dead to itself
        
        // If we never received a heartbeat, Primary not dead yet
        if (lastHeartbeatReceived == 0) {
            return false;
        }
        
        // Calculate time since last heartbeat
        double timeSinceLastHeartbeat = (currentTime - lastHeartbeatReceived).dbl();
        
        // Check if exceeded timeout
        if (timeSinceLastHeartbeat > heartbeatTimeout) {
            missedHeartbeats++;
            EV << "HeartbeatMonitor: PRIMARY DEAD! No heartbeat for " 
               << timeSinceLastHeartbeat << " seconds" << endl;
            return true;
        }
        
        return false;
    }

    /**
     * Check if it's time to send next heartbeat
     */
    bool shouldSendHeartbeat(simtime_t currentTime) {
        if (!isPrimary) return false;
        
        if (lastHeartbeatSent == 0) return true; // First heartbeat
        
        double timeSinceLastSent = (currentTime - lastHeartbeatSent).dbl();
        return (timeSinceLastSent >= heartbeatInterval);
    }

    /**
     * Get time since last heartbeat
     */
    double getTimeSinceLastHeartbeat(simtime_t currentTime) {
        if (lastHeartbeatReceived == 0) return 0.0;
        return (currentTime - lastHeartbeatReceived).dbl();
    }

    // Getters for statistics
    long getHeartbeatsSent() const { return heartbeatsSent; }
    long getHeartbeatsReceived() const { return heartbeatsReceived; }
    long getMissedHeartbeats() const { return missedHeartbeats; }
    double getHeartbeatInterval() const { return heartbeatInterval; }
    double getHeartbeatTimeout() const { return heartbeatTimeout; }
};

#endif
