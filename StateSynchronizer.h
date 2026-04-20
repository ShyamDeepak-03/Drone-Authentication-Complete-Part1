#ifndef STATESYNCHRONIZER_H
#define STATESYNCHRONIZER_H

#include <omnetpp.h>
#include <map>
#include "DroneAuthMessages_m.h"

using namespace omnetpp;

/**
 * StateSynchronizer - Manages state synchronization between GCS nodes
 * 
 * Keeps both Primary and Backup GCS with identical drone authentication state
 */
class StateSynchronizer {
private:
    // Drone state information
    struct DroneState {
        int droneId;
        bool authenticated;
        std::string commitment;
        long publicKey;
        simtime_t lastAuthTime;
        int authCount;
        simtime_t lastSyncTime;
    };
    
    std::map<int, DroneState> droneStates;
    
    // Statistics
    long syncMessagesSent;
    long syncMessagesReceived;
    long stateUpdates;
    simtime_t lastFullSync;
    
    // Configuration
    bool isPrimary;
    double syncDelay;  // Maximum acceptable sync delay (ms)
    
    cSimpleModule *module;

public:
    StateSynchronizer(cSimpleModule *mod, bool primary = true) 
        : module(mod), isPrimary(primary), 
          syncMessagesSent(0), syncMessagesReceived(0), 
          stateUpdates(0), syncDelay(0.1) {
        lastFullSync = 0;
    }

    /**
     * PRIMARY: Create sync message after drone authentication
     */
    StateSyncMessage* createSyncMessage(int droneId, bool authenticated,
                                       const std::string &commitment,
                                       long publicKey, simtime_t authTime,
                                       int authCount, simtime_t currentTime) {
        if (!isPrimary) return nullptr;
        
        StateSyncMessage *sync = new StateSyncMessage();
        sync->setDroneId(droneId);
        sync->setAuthenticated(authenticated);
        sync->setCommitment(commitment.c_str());
        sync->setPublicKey(publicKey);
        sync->setLastAuthTime(authTime);
        sync->setAuthCount(authCount);
        sync->setFullSync(false);
        
        // Update local state
        DroneState &state = droneStates[droneId];
        state.droneId = droneId;
        state.authenticated = authenticated;
        state.commitment = commitment;
        state.publicKey = publicKey;
        state.lastAuthTime = authTime;
        state.authCount = authCount;
        state.lastSyncTime = currentTime;
        
        syncMessagesSent++;
        
        EV << "StateSynchronizer: Created sync for drone " << droneId << endl;
        
        return sync;
    }

    /**
     * BACKUP: Apply received sync message
     */
    void applySyncMessage(StateSyncMessage *sync, simtime_t currentTime) {
        if (isPrimary) return; // Primary doesn't receive syncs
        
        int droneId = sync->getDroneId();
        
        DroneState &state = droneStates[droneId];
        state.droneId = droneId;
        state.authenticated = sync->getAuthenticated();
        state.commitment = sync->getCommitment();
        state.publicKey = sync->getPublicKey();
        state.lastAuthTime = sync->getLastAuthTime();
        state.authCount = sync->getAuthCount();
        state.lastSyncTime = currentTime;
        
        syncMessagesReceived++;
        stateUpdates++;
        
        EV << "StateSynchronizer: Applied sync for drone " << droneId 
           << " (authenticated=" << state.authenticated << ")" << endl;
    }

    /**
     * Get drone state (for Backup to use after takeover)
     */
    bool getDroneState(int droneId, bool &authenticated, std::string &commitment,
                      long &publicKey, simtime_t &lastAuthTime, int &authCount) {
        auto it = droneStates.find(droneId);
        if (it == droneStates.end()) {
            return false;
        }
        
        DroneState &state = it->second;
        authenticated = state.authenticated;
        commitment = state.commitment;
        publicKey = state.publicKey;
        lastAuthTime = state.lastAuthTime;
        authCount = state.authCount;
        
        return true;
    }

    /**
     * Check if state exists for drone
     */
    bool hasState(int droneId) const {
        return droneStates.find(droneId) != droneStates.end();
    }

    /**
     * Get all synchronized drone IDs
     */
    std::vector<int> getSynchronizedDrones() const {
        std::vector<int> droneIds;
        for (const auto &pair : droneStates) {
            droneIds.push_back(pair.first);
        }
        return droneIds;
    }

    /**
     * Calculate sync delay for a drone
     */
    double getSyncDelay(int droneId, simtime_t currentTime) const {
        auto it = droneStates.find(droneId);
        if (it == droneStates.end()) return -1.0;
        
        return (currentTime - it->second.lastSyncTime).dbl();
    }

    /**
     * Check if sync is up to date
     */
    bool isSyncUpToDate(simtime_t currentTime, double maxDelay = 1.0) const {
        for (const auto &pair : droneStates) {
            double delay = (currentTime - pair.second.lastSyncTime).dbl();
            if (delay > maxDelay) {
                return false;
            }
        }
        return true;
    }

    // Statistics getters
    long getSyncMessagesSent() const { return syncMessagesSent; }
    long getSyncMessagesReceived() const { return syncMessagesReceived; }
    long getStateUpdates() const { return stateUpdates; }
    int getSynchronizedDroneCount() const { return droneStates.size(); }
};

#endif
