#include "ArmResistCmd.h"
#include "CmdUtils.h"
#include "event/concept/EffortModulation/ArmResistReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_RESIST_REGEX "armresist " CMD_PARSE_ARM_REGEX " (torquePercentage) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [minVelocity=0]"
String ArmResistCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_RESIST_REGEX;
    return progmem2String(regex);
}

int8_t ArmResistCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    float torquePercentage;
    if(tryParseFloat(serial, getArg(args, 2), &torquePercentage) < 0) {
        return -1;
    }
    torquePercentage = abs(torquePercentage);

    String dirString = getArg(args, 3);
    ExoskeletonJointHandle::MovementDirection direction{ExoskeletonJointHandle::BOTH};
    if(!dirString.equals(F(""))) {
        if(tryParseMovementDirection(serial, dirString, &direction) < 0) {
            return -1;
        }
    }

    float minVelocity = 0.f;
    String minVelocityString = getArg(args, 4);
    if(!minVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, minVelocityString, &minVelocity) < 0) {
            return -1;
        }
        minVelocity = abs(minVelocity);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* resistReaction = new ArmResistReaction();
    resistReaction->configure(*arm, torquePercentage, direction, minVelocity);
    CmdReactionRunner::getInstance().launchReaction(*resistReaction);
    return 0;
}
