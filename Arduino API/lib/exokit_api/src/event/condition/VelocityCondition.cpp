#include <Arduino.h>
#include "VelocityCondition.h"

#include "AtPositionCondition.h"
#include "util/DebugSerial.h"


void VelocityCondition::configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float thresholdDegreePerSecond,
                                  float tolerance) {
    c_joint = &joint;

    if (!c_joint->canTrackPosition())
    {
        DEBUG_SERIAL.println(F("Cannot configure VelocityCondition! The joint does not have a position encoder."));
    }
    c_compareType = compareType;
    c_thresholdDegreePerSecond = thresholdDegreePerSecond;
    c_tolerance = tolerance;
    setConfigured();
}

bool VelocityCondition::evalCondition() {

    switch (c_compareType) {
    case FASTER_THAN:
        return c_joint->getVelocity() > c_thresholdDegreePerSecond - c_tolerance;
    case SLOWER_THAN:
        return c_joint->getVelocity() < c_thresholdDegreePerSecond + c_tolerance;
    case WITHIN:
        return abs(c_joint->getVelocity() - c_thresholdDegreePerSecond) < c_tolerance;
    default:
        return false;
    }
}

VelocityCondition::VelocityCondition():
        ICondition(true) {}

void VelocityCondition::restore() {}


