#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <omnetpp.h>
#include <map>
#include <deque>
#include <set>

using namespace omnetpp;

class RateLimiter {
private:
    int maxRequestsPerWindow;
    double windowSizeSeconds;
    
    // Track by GATE index (physical connection) not drone ID
    std::map<int, std::deque<simtime_t>> gateRequestHistory;
    
    // Track authenticated drones (by ID) - these bypass limits
    std::set<int> authenticatedDrones;
    
    long totalRequests;
    long blockedRequests;
    long allowedRequests;

public:
    RateLimiter(int maxRequests = 5, double windowSize = 10.0) 
        : maxRequestsPerWindow(maxRequests), 
          windowSizeSeconds(windowSize),
          totalRequests(0),
          blockedRequests(0),
          allowedRequests(0) {}

    // Check request by GATE index (physical connection)
    bool checkRequestByGate(int gateIndex, int droneId, simtime_t currentTime) {
        totalRequests++;

        // If drone is authenticated, allow unlimited requests
        if (authenticatedDrones.count(droneId) > 0) {
            allowedRequests++;
            return true;
        }

        // Otherwise, rate limit by GATE (physical connection)
        cleanupOldRequests(gateIndex, currentTime);
        auto &history = gateRequestHistory[gateIndex];
        
        if (history.size() >= (size_t)maxRequestsPerWindow) {
            blockedRequests++;
            return false;
        }

        history.push_back(currentTime);
        allowedRequests++;
        return true;
    }

    void addAuthenticatedDrone(int droneId) { 
        authenticatedDrones.insert(droneId);
    }

    void removeAuthenticatedDrone(int droneId) {
        authenticatedDrones.erase(droneId);
    }

    long getTotalRequests() const { return totalRequests; }
    long getBlockedRequests() const { return blockedRequests; }
    long getAllowedRequests() const { return allowedRequests; }

private:
    void cleanupOldRequests(int gateIndex, simtime_t currentTime) {
        auto it = gateRequestHistory.find(gateIndex);
        if (it == gateRequestHistory.end()) return;
        
        auto &history = it->second;
        simtime_t windowStart = currentTime - windowSizeSeconds;
        
        while (!history.empty() && history.front() < windowStart) {
            history.pop_front();
        }
        
        if (history.empty()) {
            gateRequestHistory.erase(it);
        }
    }
};

#endif
