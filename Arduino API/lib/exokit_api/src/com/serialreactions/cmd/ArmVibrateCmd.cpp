#include "ArmVibrateCmd.h"

#include <event/concept/GesturesNotifications/ArmVibrationReaction.h>

#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_VIBRATE "armvibrate " CMD_PARSE_ARM_REGEX " (frequency) (amplitude)"
String ArmVibrateCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_VIBRATE;
    return progmem2String(regex);
}

int8_t ArmVibrateCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    long frequency;
    if(tryParseInt(serial, getArg(args, 2), &frequency) < 0) {
        return -1;
    }
    frequency = abs(frequency);

    float amplitude;
    if(tryParseFloat(serial, getArg(args, 3), &amplitude) < 0) {
        return -1;
    }
    amplitude = abs(amplitude);

    CmdReactionRunner::getInstance().cancelReaction();
    auto* vibrationReaction = new ArmVibrationReaction();
    vibrationReaction->configure(*arm, frequency, amplitude);
    CmdReactionRunner::getInstance().launchReaction(*vibrationReaction);
    return 0;
}
