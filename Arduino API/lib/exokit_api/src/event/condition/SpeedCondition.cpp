#include "SpeedCondition.h"
#include <Arduino.h>

#include "AtPositionCondition.h"
#include "util/DebugSerial.h"


void SpeedCondition::configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float thresholdDegreePerSecond,
                               float tolerance) {
    c_joint = &joint;

    if (!c_joint->canTrackPosition())
    {
        DEBUG_SERIAL.println(F("Cannot configure SpeedCondition! The joint does not have a position encoder."));
    }
    c_compareType = compareType;
    c_thresholdDegreePerSecond = thresholdDegreePerSecond;
    c_tolerance = tolerance;
    setConfigured();
}

bool SpeedCondition::evalCondition() {

    switch (c_compareType) {
    case FASTER_THAN:
        return abs(c_joint->getVelocity()) > abs(c_thresholdDegreePerSecond) - c_tolerance;
    case SLOWER_THAN:
        return  abs(c_joint->getVelocity()) <  abs(c_thresholdDegreePerSecond) + c_tolerance;
    case WITHIN:
        return  abs(abs(c_joint->getVelocity()) - abs( c_thresholdDegreePerSecond)) < c_tolerance;
    default:
        return false;
    }
}

 SpeedCondition::SpeedCondition():
        ICondition(true) {}

void SpeedCondition::restore() {}
