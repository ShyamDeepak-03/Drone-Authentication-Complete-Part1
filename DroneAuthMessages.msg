// DroneAuthMessages.msg
// Zero-Knowledge Proof Authentication Messages

cplusplus {{
#include <string>
}}

// Commitment Phase: Drone sends t = g^r mod p
packet AuthCommit {
    int droneId;
    string commitment;  // t value as string
    simtime_t timestamp;
}

// Challenge Phase: GCS sends random challenge
packet AuthChallenge {
    int droneId;
    string challenge;  // c value as string
    simtime_t timestamp;
}

// Response Phase: Drone sends s = r + c*x mod (p-1)
packet AuthResponse {
    int droneId;
    string response;  // s value as string
    simtime_t timestamp;
}

// Verification Result
packet AuthResult {
    int droneId;
    bool authenticated;
    string reason;
    simtime_t timestamp;
}
// ============================================================================
// PHASE 2: Dual GCS Messages
// ============================================================================

// Heartbeat message between GCS nodes
packet HeartbeatMessage {
    string senderGCS;           // "PrimaryGCS" or "BackupGCS"
    simtime_t timestamp;        // When heartbeat was sent
    string status = "alive";    // "alive", "shutting_down", "overloaded"
    int activeDrones;           // Number of authenticated drones
}

// State synchronization message
packet StateSyncMessage {
    int droneId;                    // Which drone's state
    bool authenticated;             // Authentication status
    string commitment;              // Last commitment value
    long publicKey;                 // Drone public key
    simtime_t lastAuthTime;         // Last authentication timestamp
    int authCount;                  // Total authentications
    bool fullSync = false;          // Is this a full state sync?
}

// GCS announces it's taking over
packet GCSAnnouncementMessage {
    string newPrimaryAddress;       // "BackupGCS" or "PrimaryGCS"
    string reason;                  // "failover", "planned_switch", "recovery"
    simtime_t timestamp;            // Announcement time
    int droneCount;                 // How many drones should reconnect
}

// Drone acknowledges GCS switch
packet GCSSwitchAckMessage {
    int droneId;                    // Which drone is acknowledging
    string newGCS;                  // Which GCS it switched to
    simtime_t switchTime;           // When switch completed
    bool successful;                // Switch successful?
}

// Failover complete notification
packet FailoverCompleteMessage {
    int dronesReconnected;          // How many drones reconnected
    simtime_t failoverStartTime;    // When failover started
    simtime_t failoverEndTime;      // When failover completed
    double failoverDuration;        // Duration in seconds
}
