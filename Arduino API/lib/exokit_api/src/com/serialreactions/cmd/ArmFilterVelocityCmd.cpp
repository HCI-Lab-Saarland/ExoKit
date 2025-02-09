#include "ArmFilterSpeedCmd.h"
#include "CmdUtils.h"
#include "event/concept/MotionStyle/FilterSpeedReaction.h"
#include "event/concept/MotionStyle/ArmFilterSpeedReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_FILTER_VELOCITY "armfilterspeed " CMD_PARSE_ARM_REGEX " (minSpeed) (maxSpeed) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [amplifyFlexTorquePercentage=0.05] [resistFlexTorquePercentage=0.05] [amplifyExtensionTorquePercentage=0.05] [resistExtensionTorquePercentage=0.05]"
String ArmFilterSpeedCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_FILTER_VELOCITY;
    return progmem2String(regex);
}

int8_t ArmFilterSpeedCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    float minSpeed;
    if(tryParseFloat(serial, getArg(args, 2), &minSpeed) < 0) {
        return -1;
    }
    minSpeed = abs(minSpeed);

    float maxSpeed;
    if(tryParseFloat(serial, getArg(args, 3), &maxSpeed) < 0) {
        return -1;
    }
    maxSpeed = abs(maxSpeed);

    ExoskeletonJointHandle::MovementDirection direction{ExoskeletonJointHandle::BOTH};
    String directionString = getArg(args, 4);
    if(!directionString.equals(F(""))) {
        if(tryParseMovementDirection(serial, directionString, &direction) < 0) {
            return -1;
        }
    }

    float amplifyFlexTorquePercentage = 0.05f;
    String amplifyFlexTorquePercentageString = getArg(args, 5);
    if(!amplifyFlexTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyFlexTorquePercentageString, &amplifyFlexTorquePercentage) < 0) {
            return -1;
        }
        amplifyFlexTorquePercentage = abs(amplifyFlexTorquePercentage);
    }

    float resistFlexTorquePercentage = 0.05f;
    String resistFlexTorquePercentageString = getArg(args, 6);
    if(!resistFlexTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistFlexTorquePercentageString, &resistFlexTorquePercentage) < 0) {
            return -1;
        }
        resistFlexTorquePercentage = abs(resistFlexTorquePercentage);
    }

    float amplifyExtensionTorquePercentage = 0.05f;
    String amplifyExtensionTorquePercentageString = getArg(args, 7);
    if(!amplifyExtensionTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyExtensionTorquePercentageString, &amplifyExtensionTorquePercentage) < 0) {
            return -1;
        }
        amplifyExtensionTorquePercentage = abs(amplifyExtensionTorquePercentage);
    }

    float resistExtensionTorquePercentage = 0.05f;
    String resistExtensionTorquePercentageString = getArg(args, 8);
    if(!resistExtensionTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistExtensionTorquePercentageString, &resistExtensionTorquePercentage) < 0) {
            return -1;
        }
        resistExtensionTorquePercentage = abs(resistExtensionTorquePercentage);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* filterVelocityReaction = new ArmFilterSpeedReaction();
    filterVelocityReaction->configure(*arm, minSpeed, maxSpeed, direction, amplifyFlexTorquePercentage,
                                      resistFlexTorquePercentage, amplifyExtensionTorquePercentage, resistExtensionTorquePercentage);
    CmdReactionRunner::getInstance().launchReaction(*filterVelocityReaction);
    return 0;
}
