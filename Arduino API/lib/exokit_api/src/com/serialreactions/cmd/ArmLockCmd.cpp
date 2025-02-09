#include "ArmLockCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/reaction/ArmLockReaction.h"

int8_t ArmLockCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* reaction = new ArmLockReaction();
    reaction->configure(*arm);
    CmdReactionRunner::getInstance().launchReaction(*reaction);
    return 0;
}

#define CMD_Arm_LOCK_REGEX "armlock " CMD_PARSE_ARM_REGEX
String ArmLockCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_Arm_LOCK_REGEX;
    return progmem2String(regex);
}
