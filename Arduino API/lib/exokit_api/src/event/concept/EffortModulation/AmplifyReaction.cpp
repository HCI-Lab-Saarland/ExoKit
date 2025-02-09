
#include "AmplifyReaction.h"
#include "util/DebugSerial.h"

void AmplifyReaction::runLoop() {
    float velocity = c_joint->getVelocity();

    if(abs(velocity) > maxVelocity && maxVelocity > 0.01) {
        c_joint->setTorque(false);
    } else if((velocity > startingVelocity && (c_amplifyDirection == ExoskeletonJointHandle::MovementDirection::BOTH || c_amplifyDirection == ExoskeletonJointHandle::MovementDirection::ABDUCTION_OR_FLEXION))
           || (velocity < -startingVelocity && (c_amplifyDirection == ExoskeletonJointHandle::MovementDirection::BOTH || c_amplifyDirection == ExoskeletonJointHandle::MovementDirection::ADDUCTION_OR_EXTENSION))
       ) {
        bool isFlex = velocity > 0;
        if(currentDirFlex != isFlex) {
            currentDirFlex = isFlex;
            if(initialMovement) {
                initialMovement = false;
            } else {
                lastDirChange = millis();
            }
            c_joint->setTorque(false);
        }
        if((lastDirChange + dirChangeSuspensionTime) < millis()) {
            if(!c_joint->getIsTorque()) {
                c_joint->setTorque(true);
                c_joint->setGoalCurrent(c_amplifyPercentage);
                c_joint->setProfileVelocity(maxVelocity);
                c_joint->setGoalPosition(currentDirFlex ? c_joint->getUpperRangeOfMotion() : -c_joint->getLowerRangeOfMotion());
                lastTorqueEnable = millis();
            }
            float traJ = c_joint->getTrajectory();
            float cPos = c_joint->getPresentPosition();
            if(currentDirFlex ? (traJ > cPos + 5) : (traJ < cPos - 5)) {
                c_joint->setGoalPosition(currentDirFlex ? c_joint->getUpperRangeOfMotion() : -c_joint->getLowerRangeOfMotion());
            }
        }
    } else if (lastTorqueEnable + dirChangeSuspensionTime < millis()){
        c_joint->setTorque(false);
    }
}

bool AmplifyReaction::finishCondition() {
    return false;
}

void AmplifyReaction::startup() {
    initialTorqueState = c_joint->getIsTorque();
    initialOpMode = c_joint->getJointMode();
    initialCurrent = c_joint->getGoalCurrent();
    c_joint->setJointMode(OP_CURRENT_BASED_POSITION);
    c_joint->setTorque(false);
    c_joint->setProfileVelocity(maxVelocity);
    c_joint->setProfileAcceleration(0);
    c_joint->setGoalPosition(c_joint->getPresentPosition());
    c_joint->setGoalCurrent(0.f);
}

void AmplifyReaction::prepare() {

}

void AmplifyReaction::shutdown(bool isCancel) {
    if (!isConfigured() || !isStarted()) {
        return;
    }
    c_joint->setGoalPosition(c_joint->getPresentPosition());
    c_joint->setGoalCurrent(initialCurrent);
    c_joint->setTorque(initialTorqueState);
    c_joint->setJointMode(initialOpMode);
    lastDirChange = 0;
    initialMovement = true;
}

void AmplifyReaction::configure(ExoskeletonJointActiveHandle &joint, float amplifyPercentage, ExoskeletonJointHandle::MovementDirection amplifyDirection, float startingVelocity, float maxVelocity) {
    ReactionConfigurationGuard configureGuard(*this);
    this->c_joint = &joint;
    this->c_amplifyPercentage = max(0.001, min(amplifyPercentage, 0.999f));
    this->c_amplifyDirection = amplifyDirection;
    this->startingVelocity = abs(startingVelocity);
    this->maxVelocity = abs(maxVelocity);
}
