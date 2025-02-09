
#include "Arduino.h"
#include "IsMovingTowardCondition.h"

IsMovingTowardCondition::IsMovingTowardCondition():
        ICondition(true) {}

bool IsMovingTowardCondition::evalCondition() {
    if(c_direction == ExoskeletonJointHandle::MovementDirection::ABDUCTION_OR_FLEXION) {
        return c_joint->getVelocity() > c_thresholdVelocity;
    } else if (c_direction == ExoskeletonJointHandle::MovementDirection::ADDUCTION_OR_EXTENSION) {
        return c_joint->getVelocity() < -c_thresholdVelocity;
    } else {
        return abs(c_joint->getVelocity()) < c_thresholdVelocity;
    }
}

void IsMovingTowardCondition::configure(ExoskeletonJointHandle &joint, ExoskeletonJointHandle::MovementDirection direction, float thresholdVelocity) {
    c_joint = &joint;
    c_direction = direction;
    c_thresholdVelocity = abs(thresholdVelocity);
    setConfigured();
}

void IsMovingTowardCondition::restore() {}
