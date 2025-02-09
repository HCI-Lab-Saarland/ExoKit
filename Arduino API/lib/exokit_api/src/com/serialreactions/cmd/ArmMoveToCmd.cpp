#include "ArmMoveToCmd.h"
#include "CmdUtils.h"
#include "event/reaction/ArmMoveToReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_MOVETO "armmoveto " CMD_PARSE_ARM_REGEX " " CMD_PARSE_ARM_ANGLE " (velocity)"
String ArmMoveToCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_MOVETO;
    return progmem2String(regex);
}


int8_t ArmMoveToCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    ExoArmAngles angles;
    if(tryParseArmAngle(serial, getArg(args, 2), getArg(args, 3), getArg(args, 4), &angles) < 0) {
        return -1;
    }

    float velocity;
    if(tryParseFloat(serial, getArg(args, 5), &velocity) < 0) {
        return -1;
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* moveToReaction = new ArmMoveToReaction();
    moveToReaction->configure(*arm, angles, velocity);
    CmdReactionRunner::getInstance().launchReaction(*moveToReaction);
    return 0;
}
