#include "JointResistCmd.h"
#include "CmdUtils.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_RESIST "jointresist " CMD_PARSE_JOINT_REGEX " (torquePercentage) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [minVelocity=0]"
String JointResistCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_RESIST;
    return progmem2String(regex);
}

int8_t JointResistCmd::execute(HardwareSerial &serial, String args) {
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

    float minVelocity = 0.f;
    String minVelocityString = getArg(args, 5);
    if(!minVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, minVelocityString, &minVelocity) < 0) {
            return -1;
        }
        minVelocity = abs(minVelocity);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* resistReaction = new ResistReaction();
    resistReaction->configure(*aJoint, torquePercentage, direction, minVelocity);
    CmdReactionRunner::getInstance().launchReaction(*resistReaction);
    return 0;
}
