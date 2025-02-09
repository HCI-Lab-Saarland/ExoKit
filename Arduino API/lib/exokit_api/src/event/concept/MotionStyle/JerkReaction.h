

#ifndef CHI25_EXOSKELETON_API_JERKREACTION_H
#define CHI25_EXOSKELETON_API_JERKREACTION_H


#include "event/reaction/IReaction.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/ActiveJointMoveToReaction.h"

class JerkReaction: public IReaction {

private:
    ActiveJointMoveToReaction moveToReaction;
    ExoskeletonJointActiveHandle* joint{};
    unsigned long lastJerk{0};
    unsigned long currentWaitDuration;
    bool runLoopFinished{false};
    float velocity;
    float minJerkAngle{};
    float maxJerkAngle{};
    float accumulatedMoves{};
    long minJerkInterval{};
    long maxJerkInterval{};
    unsigned long lastLoopRun{};
    float maxAccumulatedMovementsLeft{};
    float maxAccumulatedMovementsRight{};
    unsigned long jerksPerformed{0};
    unsigned long nr_jerks{};

    void runLoop() override;
protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    JerkReaction();
    void shutdown(bool isCancel) override;
    void configure(ExoskeletonJointActiveHandle &joint, float minJerkAngle, float maxJerkAngle, long minJerkInterval,
                   long maxJerkInterval, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight,
                   float velocity = 0, unsigned long nr_jerks = 0);
};


#endif //CHI25_EXOSKELETON_API_JERKREACTION_H
