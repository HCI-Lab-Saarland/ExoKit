#include "ArmMirrorCmd.h"
#include "CmdUtils.h"
#include "event/reaction/ArmMoveToReaction.h"
#include "event/concept/MotionTransfer/ArmMirrorReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_MIRROR "armmirror " CMD_PARSE_ARM_REGEX " " CMD_PARSE_ARM_REGEX " [mirrorElbow=true|" CMD_PARSE_BOOL "] [mirrorShoulderSide=true|" CMD_PARSE_BOOL "] [mirrorShoulderBack=true|" CMD_PARSE_BOOL "] [scaleFactorElbow=1.0] [scaleFactorShoulderSide=1.0] [scaleFactorShoulderBack=1.0]"
String ArmMirrorCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_MIRROR;
    return progmem2String(regex);
}

int8_t ArmMirrorCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* targetArm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &targetArm) < 0) {
        return -1;
    }

    ExoskeletonArmHandle* sourceArm{};
    if(tryParseArm(serial, getArg(args, 2), getArg(args, 3), &sourceArm) < 0) {
        return -1;
    }

    bool mirrorElbow = true;
    String mirrorElbowString = getArg(args, 4);
    if(!mirrorElbowString.equals(F(""))) {
        if(tryParseBool(serial, mirrorElbowString, &mirrorElbow) < 0) {
            return -1;
        }
    }

    bool mirrorShoulderSide = true;
    String mirrorShoulderSideString = getArg(args, 5);
    if(!mirrorShoulderSideString.equals(F(""))) {
        if(tryParseBool(serial, mirrorShoulderSideString, &mirrorShoulderSide) < 0) {
            return -1;
        }
    }

    bool mirrorShoulderBack = true;
    String mirrorShoulderBackString = getArg(args, 6);
    if(!mirrorShoulderBackString.equals(F(""))) {
        if(tryParseBool(serial, mirrorShoulderBackString, &mirrorShoulderBack) < 0) {
            return -1;
        }
    }


    float scaleFactorElbow = 1.f;
    String scaleFactorElbowString = getArg(args, 7);
    if(!scaleFactorElbowString.equals(F(""))) {
        if(tryParseFloat(serial, scaleFactorElbowString, &scaleFactorElbow) < 0) {
            return -1;
        }
        scaleFactorElbow = abs(scaleFactorElbow);
    }

    float scaleFactorShoulderSide = 1.f;
    String scaleFactorShoulderSideString = getArg(args, 8);
    if(!scaleFactorShoulderSideString.equals(F(""))) {
        if(tryParseFloat(serial, scaleFactorShoulderSideString, &scaleFactorShoulderSide) < 0) {
            return -1;
        }
        scaleFactorShoulderSide = abs(scaleFactorShoulderSide);
    }

    float scaleFactorShoulderBack = 1.f;
    String scaleFactorShoulderBackString = getArg(args, 9);
    if(!scaleFactorShoulderBackString.equals(F(""))) {
        if(tryParseFloat(serial, scaleFactorShoulderBackString, &scaleFactorShoulderBack) < 0) {
            return -1;
        }
        scaleFactorShoulderBack = abs(scaleFactorShoulderBack);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* moveToReaction = new ArmMirrorReaction();
    moveToReaction->configure(*targetArm, *sourceArm, mirrorElbow, mirrorShoulderSide, mirrorShoulderBack, scaleFactorElbow, scaleFactorShoulderSide, scaleFactorShoulderBack);
    CmdReactionRunner::getInstance().launchReaction(*moveToReaction);
    return 0;
}
