#include "JointFilterSpeedCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/concept/MotionStyle/FilterSpeedReaction.h"

#define CMD_JOINT_FILTER_VELOCITY "jointfilterspeed " CMD_PARSE_JOINT_REGEX " (minSpeed) (maxSpeed) [direction=BOTH|" CMD_PARSE_JOINT_DIRECTION "] [amplifyFlexTorquePercentage=0.05] [resistFlexTorquePercentage=0.05] [amplifyExtensionTorquePercentage=0.05] [resistExtensionTorquePercentage=0.05]"
String JointFilterSpeedCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_FILTER_VELOCITY;
    return progmem2String(regex);
}

int8_t JointFilterSpeedCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* targetJoint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &targetJoint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aTargetJoint{};
    if(tryCastActiveJoint(serial, *targetJoint, &aTargetJoint) < 0) {
        return -1;
    }

    float minSpeed;
    if(tryParseFloat(serial, getArg(args, 3), &minSpeed) < 0) {
        return -1;
    }
    minSpeed = abs(minSpeed);

    float maxSpeed;
    if(tryParseFloat(serial, getArg(args, 4), &maxSpeed) < 0) {
        return -1;
    }
    maxSpeed = abs(maxSpeed);

    ExoskeletonJointHandle::MovementDirection direction{ExoskeletonJointHandle::BOTH};
    String directionString = getArg(args, 5);
    if(!directionString.equals(F(""))) {
        if(tryParseMovementDirection(serial, directionString, &direction) < 0) {
            return -1;
        }
    }

    float amplifyFlexTorquePercentage = 0.05f;
    String amplifyFlexTorquePercentageString = getArg(args, 6);
    if(!amplifyFlexTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyFlexTorquePercentageString, &amplifyFlexTorquePercentage) < 0) {
            return -1;
        }
        amplifyFlexTorquePercentage = abs(amplifyFlexTorquePercentage);
    }

    float resistFlexTorquePercentage = 0.05f;
    String resistFlexTorquePercentageString = getArg(args, 7);
    if(!resistFlexTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistFlexTorquePercentageString, &resistFlexTorquePercentage) < 0) {
            return -1;
        }
        resistFlexTorquePercentage = abs(resistFlexTorquePercentage);
    }

    float amplifyExtensionTorquePercentage = 0.05f;
    String amplifyExtensionTorquePercentageString = getArg(args, 8);
    if(!amplifyExtensionTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyExtensionTorquePercentageString, &amplifyExtensionTorquePercentage) < 0) {
            return -1;
        }
        amplifyExtensionTorquePercentage = abs(amplifyExtensionTorquePercentage);
    }

    float resistExtensionTorquePercentage = 0.05f;
    String resistExtensionTorquePercentageString = getArg(args, 9);
    if(!resistExtensionTorquePercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistExtensionTorquePercentageString, &resistExtensionTorquePercentage) < 0) {
            return -1;
        }
        resistExtensionTorquePercentage = abs(resistExtensionTorquePercentage);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* filterVelocityReaction = new FilterSpeedReaction();
    filterVelocityReaction->configure(*aTargetJoint, minSpeed, maxSpeed, direction, amplifyFlexTorquePercentage,
                                      resistFlexTorquePercentage, amplifyExtensionTorquePercentage, resistExtensionTorquePercentage);
    CmdReactionRunner::getInstance().launchReaction(*filterVelocityReaction);
    return 0;
}
