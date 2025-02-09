
#include "IsAcceleratingCondition.h"
#include <Arduino.h>
#include <exo/ExoskeletonJointHandle.h>
#include <util/DebugSerial.h>



void IsAcceleratingCondition::configure(ExoskeletonJointHandle &joint, float accelerationThreshold) {
    c_joint = &joint;

    if (!c_joint->canTrackPosition())
    {
        DEBUG_SERIAL.println(F("Cannot configure IsAcceleratingCondition! The joint does not have a position encoder."));
    }
    c_accelerationThreshold = accelerationThreshold;
    c_prior_velocity = 0;
    c_millis_start = millis();
    setConfigured();
}

bool IsAcceleratingCondition::evalCondition() {
    // if moving toward flexion or a...
    float currentVelocity = c_joint->getVelocity();
    unsigned long time_end = millis();

    // if moving towards flexion and is positive then true
    // if moving towards extension and is negative then true
    // ow then false

    float currentAcceleration = ((currentVelocity - c_prior_velocity)/((time_end-c_millis_start)/1000.0));

    DEBUG_SERIAL.println(currentAcceleration);
    if ((c_joint->getVelocity()) > 0) {
        return currentAcceleration > c_accelerationThreshold;
    } else {
        return currentAcceleration < - c_accelerationThreshold;
    }
}

IsAcceleratingCondition::IsAcceleratingCondition():
    ::ICondition(true) {}

void IsAcceleratingCondition::restore() {}
