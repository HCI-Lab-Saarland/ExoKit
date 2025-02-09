#include "ArmConstrainToCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/concept/Guidance/ArmConstrainToReaction.h"

#define CMD_ARM_CONSTRAINTO "armconstrainto " CMD_PARSE_ARM_REGEX " " CMD_PARSE_ARM_ANGLE " (radius)"
String ArmConstrainToCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_CONSTRAINTO;
    return progmem2String(regex);
}

int8_t ArmConstrainToCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    ExoArmAngles angles;
    if(tryParseArmAngle(serial, getArg(args, 2), getArg(args, 3), getArg(args, 4), &angles) < 0) {
        return -1;
    }

    float radius;
    if(tryParseFloat(serial, getArg(args, 5), &radius) < 0) {
        return -1;
    }
    radius = abs(radius);

    CmdReactionRunner::getInstance().cancelReaction();
    auto* constrainToReaction = new ArmConstrainToReaction();
    constrainToReaction->configure(*arm, angles, radius);
    CmdReactionRunner::getInstance().launchReaction(*constrainToReaction);
    return 0;
}
