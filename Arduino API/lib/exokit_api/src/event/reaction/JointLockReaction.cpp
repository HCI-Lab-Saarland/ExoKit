#include "JointLockReaction.h"
#include "util/DebugSerial.h"


bool JointLockReaction::finishCondition() {
    return unlockCondition.getFulfilled();
}

void JointLockReaction::runLoop() {}

void JointLockReaction::startup() {
    c_lockStateAtStartup = c_joint->getIsTorque();
    c_lockOPatStartup = c_joint->getJointMode();
    c_joint->setJointMode(OP_EXTENDED_POSITION);
    c_joint->setTorque(true);
    c_joint->setGoalPosition(c_joint->getPresentPosition());
}

void JointLockReaction::shutdown(bool isCancel) {
    if(!isConfigured() || !isStarted()) {
        return;
    }
    c_joint->setTorque(c_lockStateAtStartup);
    c_joint->setJointMode(c_lockOPatStartup);
    unlockCondition.restore();
}

JointLockReaction::JointLockReaction():
    IReaction(true) {
    unlockCondition.configure(true, false);
    unlockReaction.configure(unlockCondition);
}

void JointLockReaction::configure(ExoskeletonJointActiveHandle &joint) {
    ReactionConfigurationGuard configureGuard(*this);
    c_joint = &joint;
}

void JointLockReaction::prepare() {}

ManualConditionSwitchReaction &JointLockReaction::getUnlockReaction() {
    return unlockReaction;
}

ManualCondition &JointLockReaction::getUnlockCondition() {
    return unlockCondition;
}


