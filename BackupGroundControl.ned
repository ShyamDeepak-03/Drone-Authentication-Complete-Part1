//
// BackupGroundControl - Backup GCS with automatic failover
//

simple BackupGroundControl extends GroundControl
{
    parameters:
        @class(BackupGroundControl);
        @display("i=device/antennatower;bgb=800,600");
        
        // Inherited from GroundControl:
        // - heartbeatInterval, heartbeatTimeout
        // - gate[] 
        
        @signal[failoverTriggered](type=long);
        @signal[failoverComplete](type=double);
        @signal[heartbeatReceived](type=long);
        @signal[stateSyncReceived](type=long);
        
        @statistic[failoverTriggered](title="Failover Triggered"; record=count,vector);
        @statistic[failoverComplete](title="Failover Duration"; record=stats,vector; unit=s);
        @statistic[heartbeatReceived](title="Heartbeats Received"; record=count,vector);
        @statistic[stateSyncReceived](title="State Syncs Received"; record=count,vector);
}
