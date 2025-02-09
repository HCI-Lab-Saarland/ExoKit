
#include <Arduino.h>
#include "AtPositionCondition.h"

bool AtPositionCondition::evalCondition() {
    switch (compareType) {
        case EQUAL:
            return abs(joint->getPresentPosition() - angle) < tolerance + 0.01f;
        case LOWER_THEN:
            return (joint->getPresentPosition() + tolerance) < angle;
        case HIGHER_EQUAL_THEN:
            return (joint->getPresentPosition() - tolerance) >= angle;
        default:
            return false;
    }
}

void AtPositionCondition::restore() {}

AtPositionCondition::AtPositionCondition():
        ICondition(true) {}

void AtPositionCondition::configure(ExoskeletonJointHandle &joint, CompareType compareType, float angle, float tolerance) {
    this->joint = &joint;
    this->angle = angle;
    this->tolerance = tolerance;
    this->compareType = compareType;
    setConfigured();
}
