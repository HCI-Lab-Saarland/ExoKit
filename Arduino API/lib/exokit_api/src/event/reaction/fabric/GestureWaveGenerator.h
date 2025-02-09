#ifndef GESTUREWAVEGENERATOR_H
#define GESTUREWAVEGENERATOR_H


#include <event/reaction/ActiveJointMoveToReaction.h>
#include <event/reaction/JointLockReaction.h>

#include "ArmMoveToReactionGenerator.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/ComposedReaction.h"

class GestureWaveGenerator {
private:
    ActiveJointMoveToReaction* moveElbowForth1;
    ActiveJointMoveToReaction* moveElbowBack1;
    ActiveJointMoveToReaction* moveElbowForth2;
    ActiveJointMoveToReaction* moveElbowBack2;
    ActiveJointMoveToReaction* moveElbowForth3;
    ActiveJointMoveToReaction* moveElbowBack3;

    ArmMoveToReactionGenerator* moveToStartPosition;
    JointLockReaction* lockShoulderSide;
    JointLockReaction* lockShoulderBack;

    ParallelReaction* parallelLock;
    ParallelReaction* parallelWaveLock;

    ComposedReaction* moveToStartPositionResult;
    ComposedReaction* result;

    ExoskeletonArmHandle* exoArm;

public:
    virtual ~GestureWaveGenerator();
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonArmHandle &exoArm);
};

#endif //GESTUREWAVEGENERATOR_H
