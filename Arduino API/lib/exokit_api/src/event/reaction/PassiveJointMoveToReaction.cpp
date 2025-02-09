#include "PassiveJointMoveToReaction.h"

void PassiveJointMoveToReaction::startup() {}

void PassiveJointMoveToReaction::shutdown(bool isCancel) {}

void PassiveJointMoveToReaction::runLoop() {
    if(positionProvider) {
        configuredTargetAngle = positionProvider->getPosition();
        targetAngle = configuredTargetAngle;
    }
}

void PassiveJointMoveToReaction::configure(ExoskeletonJointPassiveHandle &joint, float targetAngle, float tolerance, TargetType targetType) {
    ReactionConfigurationGuard configureGuard(*this);
    c_joint = &joint;
    if(targetType == ABSOLUTE) {
        this->configuredTargetAngle = targetAngle;
    } else if (targetType == RELATIVE_CURRENT_POS) {
        this->configuredTargetAngle = joint.getPresentPosition() + targetAngle;
    } else {
        this->configuredTargetAngle = targetAngle;
        this->targetType = targetType;
    }
    this->targetAngleTolerance = tolerance;
}

bool PassiveJointMoveToReaction::isActiveJoint() {
    return false;
}

void PassiveJointMoveToReaction::prepare() {
    if(positionProvider) {
        configuredTargetAngle = positionProvider->getPosition();
    }
    if(targetType == RELATIVE_STARTING_POS) {
        targetAngle = c_joint->getPresentPosition() + configuredTargetAngle;
    } else {
        targetAngle = configuredTargetAngle;
    }
}

bool PassiveJointMoveToReaction::finishCondition() {
    if(positionProvider) {
        return false;
    }
    if(c_joint->canTrackPosition()) {
        return abs(c_joint->getPresentPosition() - targetAngle) < targetAngleTolerance;
    }
    return true;
}
