#include "JointJerkCmd.h"
#include "CmdUtils.h"
#include "event/concept/MotionStyle/JerkReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_JOINT_JERK "jointjerk " CMD_PARSE_JOINT_REGEX " (minJerkAngle) (maxJerkAngle) (minJerkIntervalMs) (maxJerkIntervalMs) (maxAccumulatedMovementsLeft) (maxAccumulatedMovementsRight) [velocity=0] [nrJerks=0]"
String JointJerkCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_JOINT_JERK;
    return progmem2String(regex);
}

int8_t JointJerkCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonJointHandle* joint;
    if(tryParseJoint(serial, getArg(args, 0), getArg(args, 1), getArg(args, 2), &joint) < 0) {
        return -1;
    }
    ExoskeletonJointActiveHandle* aJoint{};
    if(tryCastActiveJoint(serial, *joint, &aJoint) < 0) {
        return -1;
    }

    float minJerkAngle;
    if(tryParseFloat(serial, getArg(args, 3), &minJerkAngle) < 0) {
        return -1;
    }
    minJerkAngle = abs(minJerkAngle);

    float maxJerkAngle;
    if(tryParseFloat(serial, getArg(args, 4), &maxJerkAngle) < 0) {
        return -1;
    }
    maxJerkAngle = abs(maxJerkAngle);

    long minJerkIntervalMs;
    if(tryParseInt(serial, getArg(args, 5), &minJerkIntervalMs) < 0) {
        return -1;
    }
    minJerkIntervalMs = abs(minJerkIntervalMs);

    long maxJerkIntervalMs;
    if(tryParseInt(serial, getArg(args, 6), &maxJerkIntervalMs) < 0) {
        return -1;
    }
    maxJerkIntervalMs = abs(maxJerkIntervalMs);

    float maxAccumulatedMovementsLeft;
    if(tryParseFloat(serial, getArg(args, 7), &maxAccumulatedMovementsLeft) < 0) {
        return -1;
    }
    maxAccumulatedMovementsLeft = abs(maxAccumulatedMovementsLeft);

    float maxAccumulatedMovementsRight;
    if(tryParseFloat(serial, getArg(args, 8), &maxAccumulatedMovementsRight) < 0) {
        return -1;
    }
    maxAccumulatedMovementsRight = abs(maxAccumulatedMovementsRight);

    float velocity = 0;
    String velocityString = getArg(args, 9);
    if(!velocityString.equals(F(""))) {
        if(tryParseFloat(serial, velocityString, &velocity) < 0) {
            return -1;
        }
        velocity = abs(velocity);
    }

    long nrJerks = 0;
    String nrJerksString = getArg(args, 10);
    if(!nrJerksString.equals(F(""))) {
        if(tryParseInt(serial, nrJerksString, &nrJerks) < 0) {
            return -1;
        }
        nrJerks = abs(nrJerks);
    }


    CmdReactionRunner::getInstance().cancelReaction();
    auto* jerkReaction = new JerkReaction();
    jerkReaction->configure(*aJoint, minJerkAngle, maxJerkAngle, minJerkIntervalMs, maxJerkIntervalMs,
                            maxAccumulatedMovementsLeft, maxAccumulatedMovementsRight, velocity, nrJerks);
    CmdReactionRunner::getInstance().launchReaction(*jerkReaction);
    return 0;
}
