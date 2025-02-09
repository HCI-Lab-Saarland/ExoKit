#include "JointGuideAwayCmd.h"
#include "CmdUtils.h"
#include "event/concept/Guidance/GuideAwayReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_GUIDEAWAY "jointguideaway " CMD_PARSE_JOINT_REGEX " (angle) (radius) [amplifyTorquePercentage=0.05] [resistTorquePercentage=0.05]"
String JointGuideAwayCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_GUIDEAWAY;
    return progmem2String(regex);
}

int8_t JointGuideAwayCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    float angle;
    if(tryParseFloat(serial, getArg(args, 3), &angle) < 0) {
        return -1;
    }
    angle = abs(angle);

    float radius;
    if(tryParseFloat(serial, getArg(args, 4), &radius) < 0) {
        return -1;
    }
    radius = abs(radius);

    float amplifyPercentage = 0.05;
    String amplifyPercentageString = getArg(args, 5);
    if(!amplifyPercentageString.equals(F(""))) {
        if(tryParseFloat(serial, amplifyPercentageString, &amplifyPercentage) < 0) {
            return -1;
        }
        amplifyPercentage = abs(amplifyPercentage);
    }

    float resistPercentage = 0.05;
    String resistPercentageString = getArg(args, 6);
    if(!resistPercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistPercentageString, &resistPercentage) < 0) {
            return -1;
        }
        resistPercentage = abs(resistPercentage);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* guideAwayReaction = new GuideAwayReaction();
    guideAwayReaction->configure(*aJoint, angle, radius, amplifyPercentage, resistPercentage);
    CmdReactionRunner::getInstance().launchReaction(*guideAwayReaction);
    return 0;
}
