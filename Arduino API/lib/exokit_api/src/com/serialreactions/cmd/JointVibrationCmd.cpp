
#include "JointVibrationCmd.h"

#include <event/concept/GesturesNotifications/VibrationTest.h>

#include "CmdUtils.h"
#include "event/concept/GesturesNotifications/VibrationReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"


#define CMD_JOINT_VIBRATE "jointvibrate " CMD_PARSE_JOINT_REGEX " (frequency) (amplitude)"
String JointVibrationCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_VIBRATE;
    return progmem2String(regex);
}

int8_t JointVibrationCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    long frequency;
    if(tryParseInt(serial, getArg(args, 3), &frequency) < 0) {
        return -1;
    }
    frequency = abs(frequency);

    float amplitude;
    if(tryParseFloat(serial, getArg(args, 4), &amplitude) < 0) {
        return -1;
    }
    amplitude = abs(amplitude);

    CmdReactionRunner::getInstance().cancelReaction();
    auto* vibrationReaction = new VibrationTest();
    vibrationReaction->configure(*aJoint, frequency, amplitude);
    CmdReactionRunner::getInstance().launchReaction(*vibrationReaction);
    return 0;
}
