#include "JointConstrainToCmd.h"
#include "CmdUtils.h"
#include "event/concept/Guidance/ConstrainToReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_CONSTRAINTO "jointconstrainto " CMD_PARSE_JOINT_REGEX " (angle) (radius)"
String JointConstrainToCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_CONSTRAINTO;
    return progmem2String(regex);
}

int8_t JointConstrainToCmd::execute(HardwareSerial &serial, String args) {
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

    CmdReactionRunner::getInstance().cancelReaction();
    auto* constrainToReaction = new ConstrainToReaction();
    constrainToReaction->configure(*aJoint, angle, radius);
    CmdReactionRunner::getInstance().launchReaction(*constrainToReaction);
    return 0;
}
