#include "ArmJerkCmd.h"
#include "CmdUtils.h"
#include "event/concept/MotionStyle/ArmJerkReaction.h"
#include "com/serialreactions/CmdReactionRunner.h"

#define CMD_ARM_JERK "armjerk " CMD_PARSE_ARM_REGEX " (minJerkAngle) (maxJerkAngle) (minJerkIntervalMs) (maxJerkIntervalMs) (maxAccumulatedMovementsLeft) (maxAccumulatedMovementsRight) [velocity=0] [nrJerks=0]"
String ArmJerkCmd::getUsage() {
    static const char regex[] PROGMEM = CMD_ARM_JERK;
    return progmem2String(regex);
}

int8_t ArmJerkCmd::execute(HardwareSerial &serial, String args) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, getArg(args, 0), getArg(args, 1), &arm) < 0) {
        return -1;
    }

    float minJerkAngle;
    if(tryParseFloat(serial, getArg(args, 2), &minJerkAngle) < 0) {
        return -1;
    }
    minJerkAngle = abs(minJerkAngle);

    float maxJerkAngle;
    if(tryParseFloat(serial, getArg(args, 3), &maxJerkAngle) < 0) {
        return -1;
    }
    maxJerkAngle = abs(maxJerkAngle);

    long minJerkIntervalMs;
    if(tryParseInt(serial, getArg(args, 4), &minJerkIntervalMs) < 0) {
        return -1;
    }
    minJerkIntervalMs = abs(minJerkIntervalMs);

    long maxJerkIntervalMs;
    if(tryParseInt(serial, getArg(args, 5), &maxJerkIntervalMs) < 0) {
        return -1;
    }
    maxJerkIntervalMs = abs(maxJerkIntervalMs);

    float maxAccumulatedMovementsLeft;
    if(tryParseFloat(serial, getArg(args, 6), &maxAccumulatedMovementsLeft) < 0) {
        return -1;
    }
    maxAccumulatedMovementsLeft = abs(maxAccumulatedMovementsLeft);

    float maxAccumulatedMovementsRight;
    if(tryParseFloat(serial, getArg(args, 7), &maxAccumulatedMovementsRight) < 0) {
        return -1;
    }
    maxAccumulatedMovementsRight = abs(maxAccumulatedMovementsRight);

    float velocity = 0;
    String velocityString = getArg(args, 8);
    if(!velocityString.equals(F(""))) {
        if(tryParseFloat(serial, velocityString, &velocity) < 0) {
            return -1;
        }
        velocity = abs(velocity);
    }

    long nrJerks = 0;
    String nrJerksString = getArg(args, 9);
    if(!nrJerksString.equals(F(""))) {
        if(tryParseInt(serial, nrJerksString, &nrJerks) < 0) {
            return -1;
        }
        nrJerks = abs(nrJerks);
    }

    CmdReactionRunner::getInstance().cancelReaction();
    auto* jerkReaction = new ArmJerkReaction();
    jerkReaction->configure(*arm, minJerkAngle, maxJerkAngle, minJerkIntervalMs, maxJerkIntervalMs, maxAccumulatedMovementsLeft, maxAccumulatedMovementsRight, velocity, nrJerks);
    CmdReactionRunner::getInstance().launchReaction(*jerkReaction);
    return 0;
}
