#include "JointMoveToCmd.h"
#include "CmdUtils.h"
#include "event/reaction/JointMoveToReaction.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

int8_t JointMoveToCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    float angle;
    if(tryParseFloat(serial, getArg(args, 3), &angle) < 0) {
        return -1;
    }
    float velocity;
    if(tryParseFloat(serial, getArg(args, 4), &velocity) < 0) {
        return -1;
    }
    TargetType type;
    if(tryParseMoveToTargetType(serial, getArg(args, 5), &type) < 0) {
        return -1;
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* moveToReaction = new ActiveJointMoveToReaction();
    moveToReaction->configure(*aJoint, angle, velocity, 1, type);
    CmdReactionRunner::getInstance().launchReaction(*moveToReaction);
    return 0;
}

#define CMD_JOINT_MOVETO "jointmoveto " CMD_PARSE_JOINT_REGEX " (angle) (velocity) " CMD_PARSE_MOVETO_TARGET_TYPE
String JointMoveToCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_MOVETO;
    return progmem2String(regex);
}
