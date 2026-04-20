#ifndef REQUESTVALIDATOR_H
#define REQUESTVALIDATOR_H

#include <omnetpp.h>
#include <string>
#include "DroneAuthMessages_m.h"
#include "CryptoUtils.h"

using namespace omnetpp;

class RequestValidator {
private:
    double maxMessageAge;
    int minDroneId;
    int maxDroneId;
    long totalValidations;
    long validMessages;
    long invalidTimestamp;
    long invalidDroneId;

public:
    RequestValidator(double maxAge = 5.0, int minId = 0, int maxId = 999)
        : maxMessageAge(maxAge), minDroneId(minId), maxDroneId(maxId),
          totalValidations(0), validMessages(0), invalidTimestamp(0), invalidDroneId(0) {}

    bool validateCommitment(AuthCommit *msg, simtime_t currentTime, std::string &reasonOut) {
        totalValidations++;
        if (msg == nullptr) {
            reasonOut = "Null message";
            return false;
        }
        int droneId = msg->getDroneId();
        if (droneId < minDroneId || droneId > maxDroneId) {
            invalidDroneId++;
            reasonOut = "Invalid drone ID";
            return false;
        }
        simtime_t msgTime = msg->getTimestamp();
        double messageAge = (currentTime - msgTime).dbl();
        if (messageAge < 0 || messageAge > maxMessageAge) {
            invalidTimestamp++;
            reasonOut = "Invalid timestamp";
            return false;
        }
        validMessages++;
        reasonOut = "Valid";
        return true;
    }

    long getValidMessages() const { return validMessages; }
    long getInvalidTimestamp() const { return invalidTimestamp; }
    long getInvalidDroneId() const { return invalidDroneId; }
};

#endif
