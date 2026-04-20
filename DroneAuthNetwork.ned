import ned.DatarateChannel;

channel WirelessChannel extends DatarateChannel
{
    parameters:
        datarate = default(1Mbps);
        delay = default(20ms);
        ber = default(1e-6);
}

network DroneAuthBasic
{
    parameters:
        int numDrones = default(5);

    submodules:
        gcs: GroundControl {
            @display("p=400,300;i=device/antennatower");
        }

        drone[numDrones]: Drone {
            droneId = index;
            @display("p=100+index*80,150;i=misc/drone");
        }

    connections:
        for i=0..numDrones-1 {
            drone[i].gate <--> WirelessChannel <--> gcs.gate++;
        }
}

network DroneAuthWithAttacks
{
    parameters:
        int numDrones = default(5);
        int numAttackers = default(2);

    submodules:
        gcs: GroundControl {
            @display("p=400,300;i=device/antennatower");
        }

        drone[numDrones]: Drone {
            droneId = index;
            @display("p=100+index*80,150;i=misc/drone");
        }

        attacker[numAttackers]: AttackerNode {
            attackerId = 1000 + index;
            // REMOVED: attackType = index == 0 ? "replay" : "impersonation";
            // Now attackType comes from omnetpp.ini
            targetDroneId = index % parent.numDrones;
            @display("p=200+index*150,450;i=status/excl3,red");
        }

    connections:
        for i=0..numDrones-1 {
            drone[i].gate <--> WirelessChannel <--> gcs.gate++;
        }

        for i=0..numAttackers-1 {
            attacker[i].gate <--> WirelessChannel <--> gcs.gate++;
        }
}

network DroneAuthScalability
{
    parameters:
        int numDrones = default(50);

    submodules:
        gcs: GroundControl {
            @display("p=500,300;i=device/antennatower");
        }

        drone[numDrones]: Drone {
            droneId = index;
            authInterval = exponential(10s);
            @display("i=misc/drone");
        }

    connections:
        for i=0..numDrones-1 {
            drone[i].gate <--> WirelessChannel <--> gcs.gate++;
        }
}
