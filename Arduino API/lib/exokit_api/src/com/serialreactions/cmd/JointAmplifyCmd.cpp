#include "JointAmplifyCmd.h"
#include "CmdUtils.h"
#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_AMPLIFY "jointamplify " CMD_PARSE_JOINT_REGEX " (torquePercentage) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [startingVelocity=30] [maxVelocity=0]"
String JointAmplifyCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_AMPLIFY;
    return progmem2String(regex);
}

int8_t JointAmplifyCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    float torquePercentage;
    if(tryParseFloat(serial, getArg(args, 3), &torquePercentage) < 0) {
        return -1;
    }
    torquePercentage = abs(torquePercentage);

    String dirString = getArg(args, 4);
    ExoskeletonJointHandle::MovementDirection direction{ExoskeletonJointHandle::BOTH};
    if(!dirString.equals(F(""))) {
        if(tryParseMovementDirection(serial, dirString, &direction) < 0) {
            return -1;
        }
    }

    float sVelocity = 30.f;
    String sVelocityString = getArg(args, 5);
    if(!sVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, sVelocityString, &sVelocity) < 0) {
            return -1;
        }
        sVelocity = abs(sVelocity);
    }

    float maxVelocity = 0.f;
    String maxVelocityString = getArg(args, 6);
    if(!maxVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, maxVelocityString, &maxVelocity) < 0) {
            return -1;
        }
        maxVelocity = abs(maxVelocity);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* amplifyReaction = new AmplifyReaction();
    amplifyReaction->configure(*aJoint, torquePercentage, direction, sVelocity, maxVelocity);
    CmdReactionRunner::getInstance().launchReaction(*amplifyReaction);
    return 0;
}
