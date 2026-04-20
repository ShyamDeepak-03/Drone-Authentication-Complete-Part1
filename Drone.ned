simple Drone
{
    parameters:
        @display("i=misc/drone");
        int droneId;
        double authInterval @unit(s) = default(exponential(10s));
        
        // Phase 2: Failover support
        bool gcsFailoverEnabled = default(false);
        
        @signal[authAttempts](type=long);
        @signal[authSuccess](type=long);
        @signal[authFailed](type=long);
        
        @statistic[authAttempts](title="Authentication Attempts"; record=count,vector);
        @statistic[authSuccess](title="Successful Authentications"; record=count,vector);
        @statistic[authFailed](title="Failed Authentications"; record=count,vector);
    
    gates:
        inout gate;
}
