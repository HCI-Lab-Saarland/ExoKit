
#include "ForceCondition.h"
#include <Arduino.h>
#include "AtPositionCondition.h"
#include "util/DebugSerial.h"

void ForceCondition::configure(ExoskeletonJointHandle& joint, float force, ForceCompareType compareType, float tolerance) {
    c_joint = &joint;
    if (!c_joint->hasLoadCell())
    {
        DEBUG_SERIAL.println(F("Cannot configure ForceCondition! The joint does not have a load cell."));
    }
    c_compareType = compareType;
    c_force = force;
    c_tolerance = tolerance;
    last_print = millis();
    prior_measurement = 0;
    setConfigured();
}

bool ForceCondition::evalCondition() {
    if(millis() - last_print >= 12.5)
    {
        prior_measurement = c_joint->readLoadCell();
    }
    last_print = millis();
    switch (c_compareType) {
        case STRONGER_THAN:
            return prior_measurement > c_force - c_tolerance;
        case WEAKER_THAN:
            return prior_measurement < c_force + c_tolerance;
        case WITHIN:
            return abs(prior_measurement - c_force) < c_tolerance;
        default:
            return false;
    }
}

ForceCondition::ForceCondition():
        ICondition(true) {}

void ForceCondition::restore() {}
