#include "ArmAmplifyCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/concept/EffortModulation/ArmAmplifyReaction.h"


#define CMD_ARM_AMPLIFY_REGEX "armamplify " CMD_PARSE_ARM_REGEX " (torquePercentage) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [startingVelocity=30] [maxVelocity=0]"
String ArmAmplifyCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_AMPLIFY_REGEX;
    return progmem2String(regex);
}

/**
* Parses the incoming string to decode and verify the function's parameters.
* @return -1 if parsing was unsuccessful, 0 otherwise
*/
int8_t ArmAmplifyCmd::execute(HardwareSerial &serial, String args) {
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

    float sVelocity = 30.f;
    String sVelocityString = getArg(args, 4);
    if(!sVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, sVelocityString, &sVelocity) < 0) {
            return -1;
        }
        sVelocity = abs(sVelocity);
    }

    float maxVelocity = 0.f;
    String maxVelocityString = getArg(args, 5);
    if(!maxVelocityString.equals(F(""))) {
        if(tryParseFloat(serial, maxVelocityString, &maxVelocity) < 0) {
            return -1;
        }
        maxVelocity = abs(maxVelocity);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* amplifyReaction = new ArmAmplifyReaction();
    amplifyReaction->configure(*arm, torquePercentage, direction, sVelocity, maxVelocity);
    CmdReactionRunner::getInstance().launchReaction(*amplifyReaction);
    return 0;
}
