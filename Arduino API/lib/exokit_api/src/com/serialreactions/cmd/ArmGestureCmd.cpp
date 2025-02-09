#include "ArmGestureCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/concept/GesturesNotifications/GestureReaction.h"

int8_t ArmGestureCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    GestureType gestureType = WAVE;
    String gestureTypeString = getArg(args, 2);
    if(!gestureTypeString.equals(F(""))) {
        if(gestureTypeString.equals(F("wave"))) {
            gestureType = WAVE;
        } else {
            serial.print(F("Unknown gesture type: "));
            serial.println(gestureTypeString);
            return -1;
        }
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* reaction = new GestureReaction();
    reaction->configure(*arm, gestureType);
    CmdReactionRunner::getInstance().launchReaction(*reaction);
    return 0;
}

#define CMD_ARM_GESTURE_WAVE_REGEX "armgesture " CMD_PARSE_ARM_REGEX " [gesture=WAVE]"
String ArmGestureCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_GESTURE_WAVE_REGEX;
    return progmem2String(regex);
}

