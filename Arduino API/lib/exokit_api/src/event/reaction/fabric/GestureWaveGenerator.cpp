#include "GestureWaveGenerator.h"

#include <event/reaction/ActiveJointMoveToReaction.h>
#include <event/reaction/JointLockReaction.h>
#include <util/DebugSerial.h>

#include "ArmMoveToReactionGenerator.h"

void GestureWaveGenerator::reset()
{
    if(result) {
        result->shutdown(true);
    }
    delete moveElbowForth1;
    moveElbowForth1 = nullptr;
    delete moveElbowBack1;
    moveElbowBack1 = nullptr;
    delete moveElbowForth2;
    moveElbowForth2 = nullptr;
    delete moveElbowBack2;
    moveElbowBack2 = nullptr;
    delete moveElbowForth3;
    moveElbowForth3 = nullptr;
    delete moveElbowBack3;
    moveElbowBack3 = nullptr;

    delete parallelLock;
    parallelLock = nullptr;
    delete parallelWaveLock;
    parallelWaveLock = nullptr;

    delete moveToStartPosition;
    moveToStartPosition = nullptr;
    delete lockShoulderSide;
    lockShoulderSide = nullptr;
    delete lockShoulderBack;
    lockShoulderBack = nullptr;

    delete result;
    result = nullptr;

}

ComposedReaction& GestureWaveGenerator::init()
{
    reset();
    result = new ComposedReaction();

    moveElbowForth1 = new ActiveJointMoveToReaction();
    moveElbowBack1 = new ActiveJointMoveToReaction();
    moveElbowForth2 = new ActiveJointMoveToReaction();
    moveElbowBack2 = new ActiveJointMoveToReaction();
    moveElbowForth3 = new ActiveJointMoveToReaction();
    moveElbowBack3 = new ActiveJointMoveToReaction();

    parallelLock = new ParallelReaction();
    parallelWaveLock = new ParallelReaction();

    moveToStartPosition = new ArmMoveToReactionGenerator();
    lockShoulderSide = new JointLockReaction();
    lockShoulderBack = new JointLockReaction();

    result = new ComposedReaction();

    return *result;
}


// move all joints to the start position, then lock
// shoulder back at 70 degree
// shoulder side at 0 degree
// elbow at 90 degrees

// repeat waving motio 3 times
// move elbow joint to 90 degree
// move elbow joint to 45 degree

// then unlock all joints
void GestureWaveGenerator::configure(ExoskeletonArmHandle& arm)
{
    ReactionConfigurationGuard configurationGuard(*result);
    exoArm = &arm;

    if (exoArm->getElbow().isActive())
    {
        moveElbowForth1->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 90, 50);
        moveElbowBack1->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 45, 50);
        moveElbowForth2->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 90, 50);
        moveElbowBack2->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 45, 50);
        moveElbowForth3->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 90, 50);
        moveElbowBack3->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getElbow()), 45, 50);
    } else {
        DEBUG_SERIAL.println(F("Cannot wave with passive elbow!"));
    }
    // if active, lock shoulder side at 0 degree
    if (exoArm->getShoulderBack().isActive()) {
        lockShoulderBack->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getShoulderBack()));
    } else {
        DEBUG_SERIAL.println(F("Cannot wave with passive shoulder back joint!"));
    }

    if (exoArm->getShoulderSide().isActive()) {
        lockShoulderSide->configure(static_cast<ExoskeletonJointActiveHandle&>(exoArm->getShoulderSide()));
    } else {
        DEBUG_SERIAL.println(F("Cannot wave with passive shoulder side joint!"));
    }

    ExoArmAngles startPosition;
    startPosition.setElbowAngle(90);
    startPosition.setShoulderBackAngle(90);
    startPosition.setShoulderSideAngle(0);

    moveToStartPositionResult = &moveToStartPosition->init(*exoArm);
    moveToStartPosition->configure(startPosition,70);


    // parallel reaction for both locks
    parallelLock->configure(*lockShoulderBack, *lockShoulderSide);

    // parallel reaction for both locks
    parallelWaveLock->configure(*parallelLock, *moveElbowBack1);

    moveToStartPositionResult->then(*parallelWaveLock);
    moveElbowBack1->then(*moveElbowForth1);
    moveElbowForth1->then(*moveElbowBack2);
    moveElbowBack2->then(*moveElbowForth3);
    moveElbowForth3->then(*moveElbowBack3);
    moveElbowBack3->then(lockShoulderBack->getUnlockReaction());
    lockShoulderBack->getUnlockReaction().then(lockShoulderSide->getUnlockReaction());

    result->configure(moveToStartPositionResult);
    //result->configure(moveToStartPosition);
}

GestureWaveGenerator::~GestureWaveGenerator() {
    reset();
}
