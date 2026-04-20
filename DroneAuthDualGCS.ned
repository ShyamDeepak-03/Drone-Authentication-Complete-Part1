//
// DroneAuthDualGCS - Network with Primary and Backup GCS
//

import ned.DatarateChannel;

network DroneAuthDualGCS
{
    parameters:
        int numDrones = default(5);
        
    types:
        channel C extends DatarateChannel
        {
            datarate = 1Mbps;
            delay = uniform(10ms, 50ms);
        }
    
    submodules:
        // Primary GCS
        primaryGCS: GroundControl {
            parameters:
                @display("p=300,200;i=device/antennatower,green");
                dualGCSMode = true;
            gates:
                gate[6];  // 5 drones + 1 backup connection
        }
        
        // Backup GCS
        backupGCS: BackupGroundControl {
            parameters:
                @display("p=500,200;i=device/antennatower,blue");
            gates:
                gate[1];  // Just the primary link for now
        }
        
        // Drones
        drone[numDrones]: Drone {
            parameters:
                @display("p=100+100*cos(2*3.14159*index/numDrones),400+100*sin(2*3.14159*index/numDrones);i=misc/drone");
                droneId = index;
                gcsFailoverEnabled = true;
        }
    
    connections:
        // Connect drones to Primary GCS (gates 0-4)
        for i=0..numDrones-1 {
            drone[i].gate <--> C <--> primaryGCS.gate[i];
        }
        
        // Connect Primary to Backup (gate 5 of Primary, gate 0 of Backup)
        primaryGCS.gate[5] <--> C <--> backupGCS.gate[0];
        
        // NOTE: Drones are NOT physically connected to Backup
        // In Phase 2 simulation, we assume failover happens through
        // the Primary-Backup link (Backup receives announcements via Primary)
}
