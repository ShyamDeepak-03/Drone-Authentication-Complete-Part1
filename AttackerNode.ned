simple AttackerNode
{
    parameters:
        int attackerId;
        string attackType = default("replay");
        int targetDroneId = default(0);
        double attackInterval @unit(s) = default(8s);
        int dosRequestsPerSecond = default(100);
        @display("i=status/excl3,red");
        @signal[attackAttempts](type=long);
        @signal[dosRequestsSent](type=long);
        @statistic[attackAttempts](title="Attack Attempts"; record=count,vector);
        @statistic[dosRequestsSent](title="DoS Requests Sent"; record=count,sum,vector);
    gates:
        inout gate;
}
