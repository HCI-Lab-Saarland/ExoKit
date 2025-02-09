#include "JointMirrorCmd.h"
#include "CmdUtils.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_MIRROR "jointmirror " CMD_PARSE_JOINT_REGEX " " CMD_PARSE_JOINT_REGEX " [scaleFactor=1.0]"
String JointMirrorCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_MIRROR;
    return progmem2String(regex);
}

int8_t JointMirrorCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* targetJoint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &targetJoint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aTargetJoint{};
    if(tryCastActiveJoint(serial, *targetJoint, &aTargetJoint) < 0) {
        return -1;
    }

    ExoskeletonJointHandle* sourceJoint;
    if(tryParseJoint(serial, getArg(args, 3), getArg(args, 4), getArg(args, 5), &sourceJoint) < 0) {
        return -1;
    }

    float scaleFactor = 1.f;
    String scaleFactorString = getArg(args, 6);
    if(!scaleFactorString.equals(F(""))) {
        if(tryParseFloat(serial, scaleFactorString, &scaleFactor) < 0) {
            return -1;
        }
        scaleFactor = abs(scaleFactor);
    }

    scaler.configure(*sourceJoint, scaleFactor);
    CmdReactionRunner::getInstance().cancelReaction();
    auto* moveToReaction = new ActiveJointMoveToReaction();
    moveToReaction->configure(*aTargetJoint, scaler, 0);
    CmdReactionRunner::getInstance().launchReaction(*moveToReaction);
    return 0;
}
