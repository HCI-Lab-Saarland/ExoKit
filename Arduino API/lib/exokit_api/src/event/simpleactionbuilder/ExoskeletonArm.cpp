#include "ExoskeletonArm.h"
#include "event/concept/EffortModulation/ArmAmplifyReaction.h"
#include "event/concept/EffortModulation/ArmResistReaction.h"
#include "event/concept/Guidance/ArmConstrainToReaction.h"
#include "event/concept/Guidance/ArmGuideTowardsReaction.h"
#include "event/concept/MotionStyle/ArmJerkReaction.h"
#include "event/concept/MotionStyle/ArmFilterSpeedReaction.h"
#include "event/concept/Guidance/ArmGuideAwayReaction.h"
#include "event/concept/GesturesNotifications/GestureReaction.h"

ExoskeletonArm::ExoskeletonArm(ActionBuilder &ab, ExoskeletonArmHandle &arm):
    ab(ab), arm(arm), elbow(ab, arm.getElbow()), shoulderSide(ab, arm.getShoulderSide()),
    shoulderBack(ab, arm.getShoulderBack()) {}

ExoskeletonJoint &ExoskeletonArm::getShoulderBack() {
    return shoulderBack;
}

ExoskeletonJoint &ExoskeletonArm::getElbow() {
    return elbow;
}

ExoskeletonJoint &ExoskeletonArm::getShoulderSide() {
    return shoulderSide;
}

void ExoskeletonArm::moveTo(ExoArmAngles pos, float maxVelocity, ICondition* alternativeFinishCondition) {
    auto* action = new ArmMoveToReaction();
    action->configure(arm, pos, maxVelocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::gesture(GestureType gesture, ICondition* alternativeFinishCondition) {
    auto* action = new GestureReaction();
    action->configure(arm, gesture);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::mirror(ExoskeletonArmHandle &exoArmSource, bool mirrorElbow, bool mirrorShoulderSide,
                            bool mirrorShoulderBack, float scaleFactorElbow, float scaleFactorShoulderSide,
                            float scaleFactorShoulderBack, ICondition* alternativeFinishCondition) {
    auto* action = new ArmMirrorReaction();
    action->configure(arm, exoArmSource, mirrorElbow, mirrorShoulderSide,
                      mirrorShoulderBack, scaleFactorElbow, scaleFactorShoulderSide, scaleFactorShoulderBack);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void
ExoskeletonArm::amplify(float amplifyPercentage, ExoskeletonJointHandle::MovementDirection resistDirection, float startingVelocity,
                        float maxVelocity, ICondition* alternativeFinishCondition) {
    auto* action = new ArmAmplifyReaction();
    action->configure(arm, amplifyPercentage, resistDirection, startingVelocity, maxVelocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::resist(float resistPercentage, ExoskeletonJointHandle::MovementDirection resistDirection,
                            float minVelocity, ICondition* alternativeFinishCondition) {
    auto* action = new ArmResistReaction();
    action->configure(arm, resistPercentage, resistDirection, minVelocity);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::constrainTo(ExoArmAngles pos, float radius, ICondition* alternativeFinishCondition) {
    auto* action = new ArmConstrainToReaction();
    action->configure(arm, pos, radius);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::guideAway(ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage,
                               ICondition* alternativeFinishCondition) {
    auto* action = new ArmGuideAwayReaction();
    action->configure(arm, pos, radius, amplifyPercentage, resistPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::guideTowards(ExoArmAngles pos, float radius, float amplifyPercentage,
                                  float resistPercentage, ICondition* alternativeFinishCondition) {
    auto* action = new ArmGuideTowardsReaction();
    action->configure(arm, pos, radius, amplifyPercentage, resistPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::jerk(float minJerkAngle, float maxJerkAngle, long minJerkInterval, long maxJerkInterval,
                          float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight, float velocity, long nrJerks,
                          ICondition* alternativeFinishCondition) {
    auto* action = new ArmJerkReaction();
    action->configure(arm, minJerkAngle, maxJerkAngle, minJerkInterval, maxJerkInterval,
            maxAccumulatedMovementsLeft, maxAccumulatedMovementsRight, velocity, nrJerks);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

void ExoskeletonArm::filterVelocity(float minVelocity, float maxVelocity, ExoskeletonJointHandle::MovementDirection direction,
                                    float amplifyFlexPercentage, float resistFlexPercentage,
                                    float amplifyExtensionPercentage, float resistExtensionPercentage,
                                    ICondition* alternativeFinishCondition) {
    auto* action = new ArmFilterSpeedReaction();
    action->configure(arm, minVelocity, maxVelocity, direction, amplifyFlexPercentage, resistFlexPercentage,
            amplifyExtensionPercentage, resistExtensionPercentage);
    action->setAlternativeFinishCondition(alternativeFinishCondition);
    ab.nextReaction(*action);
}

ICondition &ExoskeletonArm::isAtExoArmAngle(ExoArmAngles exoArmAngle, float tolerance, unsigned long duration) {
    auto* condition = new AtExoArmAngleCondition();
    condition->configure(arm, exoArmAngle, tolerance, duration);
    ab.bindOwnership(*condition);
    return *condition;
}
