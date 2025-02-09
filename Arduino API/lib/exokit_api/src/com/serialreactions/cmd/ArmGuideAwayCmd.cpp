#include "ArmGuideAwayCmd.h"
#include "CmdUtils.h"
#include "event/concept/Guidance/ArmGuideAwayReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_GUIDETOWARDS "armguideaway " CMD_PARSE_ARM_REGEX " " CMD_PARSE_ARM_ANGLE " (radius) [amplifyTorquePercentage=0.05] [resistTorquePercentage=0.05]"
String ArmGuideAwayCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_GUIDETOWARDS;
    return progmem2String(regex);
}

int8_t ArmGuideAwayCmd::execute(HardwareSerial &serial, String args) {
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

    float amplifyPercentage = 0.05;
    String amplifyPercentageString = getArg(args, 6);
    if(!amplifyPercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyPercentageString, &amplifyPercentage) < 0) {
            return -1;
        }
        amplifyPercentage = abs(amplifyPercentage);
    }

    float resistPercentage = 0.05;
    String resistPercentageString = getArg(args, 7);
    if(!resistPercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistPercentageString, &resistPercentage) < 0) {
            return -1;
        }
        resistPercentage = abs(resistPercentage);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* armGuideAwayReaction = new ArmGuideAwayReaction();
    armGuideAwayReaction->configure(*arm, angles, radius, amplifyPercentage, resistPercentage);
    CmdReactionRunner::getInstance().launchReaction(*armGuideAwayReaction);
    return 0;
}
