
#include "event/concept/MotionStyle/JerkReaction.h"
#include "util/DebugSerial.h"

void JerkReaction::runLoop() {
    unsigned long currentTime = millis();
    unsigned long deltaLastRun = currentTime - lastLoopRun;
    lastLoopRun = currentTime;
    if(moveToReaction.isStarted()) {
        runLoopFinished = !moveToReaction.doRunLoop();
        return;
    }
    if(abs(joint->getVelocity()) < 5) {
        lastJerk += deltaLastRun;
        return;
    }
    if(!(currentTime > lastJerk + currentWaitDuration)) {
        return;
    }
    lastJerk = millis();
    currentWaitDuration = random(minJerkInterval, maxJerkInterval);

    bool valid;
    float jerkAngle;
    unsigned long startTime = millis();
    float newAccumulatedMoves = accumulatedMoves;

    do {
        if(startTime + 100 < millis()) {
            return;
        }
        newAccumulatedMoves = accumulatedMoves;
        bool movePositive = random(0, 100) > 50;
        jerkAngle = float(random(long(minJerkAngle * 10.f), long(maxJerkAngle * 10.f))) / 10.f;
        if(movePositive) {
            newAccumulatedMoves += jerkAngle;
            if(abs(maxAccumulatedMovementsRight) < 0.01) {
                valid = true;
            } else {
                valid = newAccumulatedMoves < maxAccumulatedMovementsRight;
            }
        } else {
            jerkAngle = -jerkAngle;
            newAccumulatedMoves += jerkAngle;
            if(abs(maxAccumulatedMovementsLeft) < 0.01) {
                valid = true;
            } else {
                valid = newAccumulatedMoves > -maxAccumulatedMovementsLeft;
            }
        }
        float newPos = joint->getPresentPosition() + jerkAngle;
        if(newPos > joint->getUpperRangeOfMotion() || newPos < -joint->getLowerRangeOfMotion()) {
            valid = false;
        }
    } while (!valid);

    moveToReaction.configure(*joint, jerkAngle, velocity, 2, RELATIVE_CURRENT_POS);
    runLoopFinished = !moveToReaction.doRunLoop();
    accumulatedMoves = newAccumulatedMoves;
    jerksPerformed++;
}

bool JerkReaction::finishCondition() {
    if(nr_jerks <= 0 || jerksPerformed <= 0) {
        return false;
    }
    if(jerksPerformed >= nr_jerks && isStarted() && runLoopFinished) {
        return true;
    }
    return false;
}

void JerkReaction::startup() {
    lastJerk = millis();
    lastLoopRun = millis();
    currentWaitDuration = random(minJerkInterval, maxJerkInterval);
}

void JerkReaction::prepare() {

}

JerkReaction::JerkReaction():
    IReaction(true) {}

void JerkReaction::shutdown(bool isCancel) {
    if(moveToReaction.isStarted()) {
        moveToReaction.shutdown(isCancel);
    }
    jerksPerformed = 0;
    runLoopFinished = false;
}

void
JerkReaction::configure(ExoskeletonJointActiveHandle &joint, float minJerkAngle, float maxJerkAngle, long minJerkInterval,
                        long maxJerkInterval, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight,
                        float velocity, unsigned long nr_jerks) {
    ReactionConfigurationGuard configurationGuard(*this);
    this->joint = &joint;
    this->minJerkAngle = abs(minJerkAngle);
    this->maxJerkAngle = abs(maxJerkAngle);
    this->minJerkInterval = abs(long(minJerkInterval));
    this->maxJerkInterval = abs(long(maxJerkInterval));
    this->maxAccumulatedMovementsLeft = abs(maxAccumulatedMovementsLeft);
    this->maxAccumulatedMovementsRight = abs(maxAccumulatedMovementsRight);
    this->nr_jerks = nr_jerks;
    this->velocity = velocity;
}
