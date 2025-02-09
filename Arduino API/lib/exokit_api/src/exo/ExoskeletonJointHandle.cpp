#include "ExoskeletonJointHandle.h"
#include "ExoskeletonArmHandle.h"

ExoskeletonJointHandle::ExoskeletonJointHandle(ArmSide side, JointType jointType, int16_t lower_range_of_motion, int16_t upper_range_of_motion):
        armSide(side), jointType(jointType), lower_range_of_motion(lower_range_of_motion), upper_range_of_motion(upper_range_of_motion) {}

void ExoskeletonJointHandle::setExoskeletonArm(ExoskeletonArmHandle &arm) {
    this->exoArm = &arm;
}

float ExoskeletonJointHandle::getPresentPosition() {
    return 0;
}

bool ExoskeletonJointHandle::hasLoadCell() {
    return false;
}

bool ExoskeletonJointHandle::canTrackPosition() {
    return false;
}

float ExoskeletonJointHandle::getVelocity() {
    return 0;
}

ExoskeletonArmHandle &ExoskeletonJointHandle::getExoskeletonArm() {
    return *exoArm;
}

ArmSide ExoskeletonJointHandle::getSide() const {
    return armSide;
}

float ExoskeletonJointHandle::getPosition() {
    return getPresentPosition();
}

float ExoskeletonJointHandle::getLowerRangeOfMotion() const {
    return lower_range_of_motion;
}

float ExoskeletonJointHandle::getUpperRangeOfMotion() const {
    return upper_range_of_motion;
}

JointType ExoskeletonJointHandle::getType() {
    return jointType;
}

bool ExoskeletonJointHandle::negateAngles() {
    return (getType() == SHOULDER_SIDE) != (getSide() != LEFT);
}


