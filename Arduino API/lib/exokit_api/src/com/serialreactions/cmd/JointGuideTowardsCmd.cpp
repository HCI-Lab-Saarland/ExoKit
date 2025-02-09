#include "JointGuideTowardsCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"
#include "event/concept/Guidance/GuideTowardsReaction.h"

#define CMD_JOINT_GUIDETOWARDS "jointguidetowards " CMD_PARSE_JOINT_REGEX " (angle) (radius) [amplifyTorquePercentage=0.05] [resistTorquePercentage=0.05]"
String JointGuideTowardsCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_GUIDETOWARDS;
    return progmem2String(regex);
}

int8_t JointGuideTowardsCmd::execute(HardwareSerial &serial, String args) {
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
    String resistPercentageString = getArg(args, 5);
    if(!resistPercentageString.equals(F(""))) {
        if(tryParseFloat(serial, resistPercentageString, &resistPercentage) < 0) {
            return -1;
        }
        resistPercentage = abs(resistPercentage);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* guideTowardsReaction = new GuideTowardsReaction();
    guideTowardsReaction->configure(*aJoint, angle, radius, amplifyPercentage, resistPercentage);
    CmdReactionRunner::getInstance().launchReaction(*guideTowardsReaction);
    return 0;
}
