#include "JointLockCmd.h"
#include "CmdUtils.h"
#include "event/reaction/JointLockReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

int8_t JointLockCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint{};
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }

    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* reaction = new JointLockReaction();
    reaction->configure(*aJoint);
    CmdReactionRunner::getInstance().launchReaction(*reaction);
    return 0;
}

#define CMD_JOINT_LOCK_REGEX "jointlock " CMD_PARSE_JOINT_REGEX
String JointLockCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_LOCK_REGEX;
    return progmem2String(regex);
}
