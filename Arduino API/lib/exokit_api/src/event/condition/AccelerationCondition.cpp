
#include "AccelerationCondition.h"
#include <Arduino.h>
#include <time.h>

#include "AtPositionCondition.h"
#include "util/DebugSerial.h"


void AccelerationCondition::configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float acceleration,
                                      float tolerance) {
    c_joint = &joint;

    if (!c_joint->canTrackPosition())
    {
        DEBUG_SERIAL.println(F("Cannot configure AccelerationCondition! The joint does not have a position encoder."));
    }
    c_compareType = compareType;
    c_acceleration = acceleration;
    c_tolerance = tolerance;
    c_prior_velocity = 0;
    c_millis_start = millis();
    setConfigured();
}

bool AccelerationCondition::evalCondition() {
    float currentVelocity = c_joint->getVelocity();
    unsigned long time_end = millis();

    float currentAcceleration = ((currentVelocity - c_prior_velocity)/(float(time_end-c_millis_start)/1000.f));

    switch (c_compareType) {
        case FASTER_THAN:
            return (c_acceleration - c_tolerance) < currentAcceleration;
        case SLOWER_THAN:
            return (c_acceleration + c_tolerance) > currentAcceleration;
        case WITHIN:
            return abs((currentAcceleration - c_acceleration)) < c_tolerance + 0.01f;
    }
    return false;
}

AccelerationCondition::AccelerationCondition():
        ICondition(true) {}

void AccelerationCondition::restore() {}


