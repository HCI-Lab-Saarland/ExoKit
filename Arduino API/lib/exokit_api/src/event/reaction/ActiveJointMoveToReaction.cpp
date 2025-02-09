#include "ActiveJointMoveToReaction.h"
#include "util/DebugSerial.h"

void ActiveJointMoveToReaction::runLoop() {
    if(positionProvider) {
        configuredTargetAngle = positionProvider->getPosition();
        targetAngle = configuredTargetAngle;
        static_cast<ExoskeletonJointActiveHandle *>(c_joint)->setGoalPosition(targetAngle);
    }
}

void ActiveJointMoveToReaction::shutdown(bool isCancel) {
    if (!isConfigured() || !isStarted()) {
        return;
    }
    ExoskeletonJointActiveHandle* joint = static_cast<ExoskeletonJointActiveHandle*>(c_joint);
    joint->setGoalPosition(joint->getPresentPosition());
    joint->setTorque(c_initialTorqueState);
    joint->setProfileVelocity(c_initialVelocityProfile);
    joint->setJointMode(c_initialJointMode);
}

void ActiveJointMoveToReaction::startup() {
    ExoskeletonJointActiveHandle* joint = static_cast<ExoskeletonJointActiveHandle*>(c_joint);
    c_initialTorqueState = joint->getIsTorque();
    c_initialVelocityProfile = joint->getProfileVelocity();
    c_initialJointMode = joint->getJointMode();
    joint->setJointMode(OP_EXTENDED_POSITION);
    joint->setTorque(true);
    joint->setProfileVelocity(velocity);
    joint->setGoalPosition(targetAngle);

}

/**
 *
 * @param joint
 * @param goalAngle The angle that the joint should approach. Must be positive!
 * @param goalTolerance
 */
void ActiveJointMoveToReaction::configure(ExoskeletonJointActiveHandle &joint, float goalAngle, float velocity,
                                          float goalAngleTolerance, TargetType targetType) {
    ReactionConfigurationGuard guard(*this);
    c_joint = &joint;
    this->positionProvider = nullptr;
    if(targetType == ABSOLUTE) {
        this->configuredTargetAngle = goalAngle;
    } else if (targetType == RELATIVE_CURRENT_POS) {
        this->configuredTargetAngle = joint.getPresentPosition() + goalAngle;
    } else {
        this->configuredTargetAngle = goalAngle;
        this->targetType = targetType;
    }
    this->targetAngleTolerance = abs(goalAngleTolerance);
    this->velocity = abs(velocity);
    setConfigured();
}

bool ActiveJointMoveToReaction::isActiveJoint() {
    return true;
}

void ActiveJointMoveToReaction::prepare() {
    if(positionProvider) {
        configuredTargetAngle = positionProvider->getPosition();
    }
    if(targetType == RELATIVE_STARTING_POS) {
        targetAngle = c_joint->getPresentPosition() + configuredTargetAngle;
    } else {
        targetAngle = configuredTargetAngle;
    }
}

void
ActiveJointMoveToReaction::configure(ExoskeletonJointActiveHandle &joint, PositionProvider& followPosition, float velocity) {
    ReactionConfigurationGuard configureGuard(*this);
    c_joint = &joint;
    this->configuredTargetAngle = 0;
    this->positionProvider = &followPosition;
    this->targetType = ABSOLUTE;
    this->targetAngleTolerance = 0;
    this->velocity = abs(velocity);
}

bool ActiveJointMoveToReaction::finishCondition() {
    if(positionProvider) {
        return false;
    }
    auto* aJoint = static_cast<ExoskeletonJointActiveHandle*>(c_joint);
    if(!isStarted()) {
        return abs(aJoint->getPresentPosition() - targetAngle) < targetAngleTolerance;
    }

    return aJoint->isGoalPositionReached(targetAngleTolerance);
}
