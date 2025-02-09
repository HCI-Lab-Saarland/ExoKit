
#include "ResistReaction.h"

void ResistReaction::runLoop() {
    float velocity = joint->getVelocity();

    float percentagePercentage = min(1, max(0, abs(velocity)-minVelocity)/max(1, minVelocity + resistPercentageLinearGrowthLength));
    float percentage = resistancePercentage * percentagePercentage;


    if(abs(velocity) < minVelocity && minVelocity > 0.01) {
        joint->setTorque(false);
    } else if((velocity > 1 && (resistDirection == ExoskeletonJointHandle::MovementDirection::BOTH || resistDirection == ExoskeletonJointHandle::MovementDirection::ABDUCTION_OR_FLEXION))
        || (velocity < -1 && (resistDirection == ExoskeletonJointHandle::MovementDirection::BOTH || resistDirection == ExoskeletonJointHandle::MovementDirection::ADDUCTION_OR_EXTENSION))
    ) {
        bool isFlex = velocity > 0;
        if(!joint->getIsTorque()) {
            joint->setTorque(true);
            joint->setProfileVelocity(minVelocity);
            joint->setGoalPosition(joint->getPresentPosition());
        } else if(currentDirFlex != isFlex) {
            currentDirFlex = isFlex;
            if(initialMovement) {
                initialMovement = false;
            } else {
                joint->setGoalPosition(joint->getPresentPosition());
            }
        }
        joint->setGoalCurrent(percentage);
    } else {
        joint->setTorque(false);
    }
}

bool ResistReaction::finishCondition() {
    return false;
}

void ResistReaction::startup() {
    initialTorqueState = joint->getIsTorque();
    initialOpMode = joint->getJointMode();
    initialCurrent = joint->getGoalCurrent();
    joint->setJointMode(OP_CURRENT_BASED_POSITION);
    joint->setTorque(false);
    joint->setProfileVelocity(minVelocity);
    joint->setProfileAcceleration(0);
    joint->setGoalPosition(joint->getPresentPosition());
    joint->setGoalCurrent(0.f);
    initialMovement = true;
}

void ResistReaction::prepare() {

}

void ResistReaction::shutdown(bool isCancel) {
    if (!isConfigured() || !isStarted()) {
        return;
    }
    joint->setTorque(initialTorqueState);
    joint->setJointMode(initialOpMode);
    joint->setGoalCurrent(initialCurrent);
}

void ResistReaction::configure(ExoskeletonJointActiveHandle &joint, float resistancePercentage, ExoskeletonJointHandle::MovementDirection resistDirection, float minVelocity) {
    ReactionConfigurationGuard configureGuard(*this);
    this->joint = &joint;
    this->resistancePercentage = resistancePercentage;
    this->resistDirection = resistDirection;
    this->minVelocity = minVelocity;
}
