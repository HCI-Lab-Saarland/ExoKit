#include "ExoskeletonJoint.h"
#include "event/concept/EffortModulation/DirectionalAmplifyReaction.h"
#include "exo/MovementScaler.h"

ExoskeletonJoint::ExoskeletonJoint(ActionBuilder &ab, ExoskeletonJointHandle &joint):
    ab(ab), joint(joint) {}

bool ExoskeletonJoint::isActive() {
    return joint.isActive();
}

ExoskeletonJointHandle& ExoskeletonJoint::unwrap() {
    return joint;
}

void ExoskeletonJoint::moveToPassive(float targetAngle, float tolerance, TargetType targetType,
                                     ICondition* alternativeFinishCondition) {
    auto* action = new PassiveJointMoveToReaction();
    action->configure(static_cast<ExoskeletonJointPassiveHandle&>(joint), targetAngle, tolerance, targetType);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::moveToActive(float goalAngle, float velocity, float goalAngleTolerance,
                                    TargetType targetType, ICondition* alternativeFinishCondition) {
    auto* action = new ActiveJointMoveToReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), goalAngle, velocity, goalAngleTolerance, targetType);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::mirror(ExoskeletonJoint sourceJoint, float scaleFactor, float velocity, ICondition* alternativeFinishCondition) {
    auto* action = new ActiveJointMoveToReaction();
    auto* posProvider = new MovementScaler();
    posProvider->configure(sourceJoint.joint, scaleFactor);
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), *posProvider, velocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::vibrate(uint8_t frequency, float amplitude, ICondition* alternativeFinishCondition) {
    auto* action = new VibrationReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), frequency, amplitude);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::resist(float resistancePercentage, ExoskeletonJointHandle::MovementDirection resistDirection,
                              float minVelocity, ICondition* alternativeFinishCondition) {
    auto* action = new ResistReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), resistancePercentage, resistDirection, minVelocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::constrainTo(float angle, float radius, ICondition* alternativeFinishCondition) {
    auto* action = new ConstrainToReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), angle, radius);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::guideAway(float angle, float radius, float amplifyPercentage, float resistPercentage,
                                 ICondition* alternativeFinishCondition) {
    auto* action = new GuideAwayReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), angle, radius, amplifyPercentage, resistPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::guideTowards(float angle, float radius, float amplifyPercentage, float resistPercentage,
                                    ICondition* alternativeFinishCondition) {
    auto* action = new GuideTowardsReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), angle, radius, amplifyPercentage, resistPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::jerk(float minJerkAngle, float maxJerkAngle, long minJerkInterval, long maxJerkInterval,
                            float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight, float velocity,
                            long nrJerks, ICondition* alternativeFinishCondition) {
    auto* action = new JerkReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle &>(joint), minJerkAngle, maxJerkAngle, minJerkInterval,
                      maxJerkInterval, maxAccumulatedMovementsLeft, maxAccumulatedMovementsRight, velocity, nrJerks);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::filterVelocity(float minVelocity, float maxVelocity,
                                      ExoskeletonJointHandle::MovementDirection direction,
                                      float amplifyFlexPercentage, float resistFlexPercentage,
                                      float amplifyExtensionPercentage, float resistExtensionPercentage,
                                      ICondition* alternativeFinishCondition) {
    auto* action = new FilterSpeedReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), minVelocity, maxVelocity,
                      direction, amplifyFlexPercentage, resistFlexPercentage,
                      amplifyExtensionPercentage, resistExtensionPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::amplify(float amplifyPercentage, ExoskeletonJointHandle::MovementDirection amplifyDirection,
                               float startingVelocity, float maxVelocity, ICondition* alternativeFinishCondition) {
    auto* action = new AmplifyReaction();
    action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), amplifyPercentage, amplifyDirection,
                      startingVelocity, maxVelocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::streamSensorData(bool streamPosition, bool streamVelocity, bool streamSpeed, bool streamLoadCell, ICondition* alternativeFinishCondition)
{
    auto* action = new SenseReaction();
    if (joint.isActive())
    {
        action->configure(static_cast<ExoskeletonJointActiveHandle&>(joint), streamPosition, streamVelocity, streamSpeed, streamLoadCell);
    } else
    {
        action->configure(static_cast<ExoskeletonJointPassiveHandle&>(joint), streamPosition, streamVelocity, streamSpeed, streamLoadCell);
    }
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonJoint::lock(unsigned long lockId,
                            ICondition* alternativeFinishCondition) {
    JointLockReaction* lockReaction;
    bool isNew = getLockReaction(lockId, static_cast<ExoskeletonJointActiveHandle&>(joint), &lockReaction);
    lockReaction->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*lockReaction, isNew);
}

void ExoskeletonJoint::unlock(unsigned long lockId) {
    JointLockReaction* lockReaction;
    bool isNew = getLockReaction(lockId, static_cast<ExoskeletonJointActiveHandle&>(joint), &lockReaction);
    ab.nextReaction(lockReaction->getUnlockReaction(), false);
    if(isNew) {
        ab.bindOwnership(*lockReaction);
    }
}

bool
ExoskeletonJoint::getLockReaction(unsigned long id, ExoskeletonJointActiveHandle &joint, JointLockReaction **outLockReaction) {
    for(int i = 0; i < lockReactions.size(); i++) {
        lock_reaction_entry_t entry = lockReactions.get(i);
        if(entry.id == id) {
            *outLockReaction = &(*entry.lr);
            return false;
        }
    }
    auto* newLock = new JointLockReaction();
    newLock->configure(joint);
    lockReactions.add({
        newLock, id
    });
    *outLockReaction = newLock;
    return true;
}

VelocityCondition &ExoskeletonJoint::isVelocity(SpeedCompareType compare, float thresholdDegreePerSecond, float tolerance) {
    auto* condition = new VelocityCondition();
    condition->configure(joint, compare, thresholdDegreePerSecond, tolerance);
    ab.bindOwnership(*condition);
    return *condition;
}

SpeedCondition &ExoskeletonJoint::isSpeed(SpeedCompareType compareType, float thresholdDegreePerSecond, float tolerance) {
    auto* condition = new SpeedCondition();
    condition->configure(joint, compareType, thresholdDegreePerSecond, tolerance);
    ab.bindOwnership(*condition);
    return *condition;
}

IsMovingTowardCondition &
ExoskeletonJoint::isMovingTowards(ExoskeletonJointHandle::MovementDirection direction, float thresholdVelocity) {
    auto* condition = new IsMovingTowardCondition();
    condition->configure(joint, direction, thresholdVelocity);
    ab.bindOwnership(*condition);
    return *condition;
}

IsMovingCondition &ExoskeletonJoint::isMoving() {
    auto* condition = new IsMovingCondition();
    condition->configure(joint);
    ab.bindOwnership(*condition);
    return *condition;
}

IsAcceleratingCondition &ExoskeletonJoint::isAccelerating(float accelerationThreshold) {
    auto* condition = new IsAcceleratingCondition();
    condition->configure(joint, accelerationThreshold);
    ab.bindOwnership(*condition);
    return *condition;
}

ForceCondition &ExoskeletonJoint::isForce(ForceCondition::ForceCompareType compareType, float force, float tolerance) {
    auto* condition = new ForceCondition();
    condition->configure(joint, force, compareType, tolerance);
    ab.bindOwnership(*condition);
    return *condition;
}

AtPositionCondition &ExoskeletonJoint::isAtPosition(CompareType compareType, float angle, float tolerance) {
    auto* condition = new AtPositionCondition();
    condition->configure(joint, compareType, angle, tolerance);
    ab.bindOwnership(*condition);
    return *condition;
}

AccelerationCondition &ExoskeletonJoint::isAcceleration(SpeedCompareType compareType, float acceleration, float tolerance) {
    auto* condition = new AccelerationCondition();
    condition->configure(joint, compareType, acceleration, tolerance);
    ab.bindOwnership(*condition);
    return *condition;
}
