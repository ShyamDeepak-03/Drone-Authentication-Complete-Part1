simple GroundControl
{
    parameters:
        @display("i=device/antennatower");
        
        // Existing DoS protection parameters
        bool dosProtectionEnabled = default(false);
        int maxRequestsPerWindow = default(10);
        double rateLimitWindow @unit(s) = default(10s);
        double maxMessageAge @unit(s) = default(5s);
        int minValidDroneId = default(0);
        int maxValidDroneId = default(999);
        int maxQueueSize = default(1000);
        double processingDelay @unit(s) = default(0.001s);
        
        // Phase 2: Dual GCS parameters
        bool dualGCSMode = default(false);
        double heartbeatInterval @unit(s) = default(1s);
        double heartbeatTimeout @unit(s) = default(3s);

        // Existing signals...
        @signal[authRequests](type=long);
        @signal[authSuccessful](type=long);
        @signal[authFailed](type=long);
        @signal[replayDetected](type=long);
        @signal[rateLimitHits](type=long);
        @signal[validationFailures](type=long);
        @signal[queueOverflow](type=long);
        
        // Existing statistics...
        @statistic[authRequests](title="Authentication Requests"; record=count,vector);
        @statistic[authSuccessful](title="Successful Authentications"; record=count,vector);
        @statistic[authFailed](title="Failed Authentications"; record=count,vector);
        @statistic[replayDetected](title="Replay Attacks Detected"; record=count,vector);
        @statistic[rateLimitHits](title="Rate Limit Hits"; record=count,vector);
        @statistic[validationFailures](title="Validation Failures"; record=count,vector);
        @statistic[queueOverflow](title="Queue Overflow Drops"; record=count,vector);

    gates:
        inout gate[];
}
