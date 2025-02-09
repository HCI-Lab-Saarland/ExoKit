#ifndef CHI25_EXOSKELETON_API_EXOSKELETONARM_H
#define CHI25_EXOSKELETON_API_EXOSKELETONARM_H


#include "ExoskeletonJoint.h"
#include "model/ExoArmAngles.h"
#include "exo/ExoskeletonArmHandle.h"
#include "ActionBuilder.h"
#include "event/reaction/ArmMoveToReaction.h"
#include "event/concept/MotionTransfer/ArmMirrorReaction.h"
#include "event/condition/AtExoArmAngleCondition.h"
#include "event/concept/GesturesNotifications/GestureReaction.h"

class ExoskeletonArm {
    ActionBuilder& ab;
    ExoskeletonArmHandle& arm;
    ExoskeletonJoint elbow;
    ExoskeletonJoint shoulderSide;
    ExoskeletonJoint shoulderBack;

public:
    ExoskeletonArm(ActionBuilder &ab, ExoskeletonArmHandle& arm);
    ExoskeletonJoint& getElbow();
    ExoskeletonJoint& getShoulderBack();
    ExoskeletonJoint& getShoulderSide();

    /**
     * Moves the joint to a specified position.
     * @param pos The position described using angles for each joint of the arm.
     * @param maxVelocity The maximum speed (in deg/sec) with which the joint should be moved.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void moveTo(ExoArmAngles pos, float maxVelocity, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Performs a gesture with the arm.
     * @param gesture WAVE
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void gesture(GestureType gesture, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Lets this arm mirror movements made with a different arm.
     * @param exoArmSource The source arm to mirror.
     * @param mirrorElbow True if the elbow should be mirrored. False if not.
     * @param mirrorShoulderSide True if the shoulder-side-joint should be mirrored. False if not.
     * @param mirrorShoulderBack True if the shoulder-back-joint should be mirrored. False if not.
     * @param scaleFactorElbow A multiplication factor that the position of the elbow joint gets multiplied with.
     * @param scaleFactorShoulderSide A multiplication factor that the position of the shoulder-side joint gets multiplied with.
     * @param scaleFactorShoulderBack A multiplication factor that the position of the shoulder-back joint gets multiplied with.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void mirror(ExoskeletonArmHandle &exoArmSource, bool mirrorElbow, bool mirrorShoulderSide,
                bool mirrorShoulderBack, float scaleFactorElbow = 1.0, float scaleFactorShoulderSide = 1.0,
                float scaleFactorShoulderBack = 1.0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Amplifies movements towards the selected direction
     * @param amplifyPercentage The maximum percentage of torque that the servos should use to amplify the joint.
     * @param amplifyDirection ABDUCTION_OR_FLEXION, ADDUCTION_OR_EXTENSION, BOTH
     * @param startingVelocity The minimum movement speed in deg/sec at which amplification will be applied.
     * @param maxVelocity The maximum movement speed in deg/sec at which amplification will be applied.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void amplify(float amplifyPercentage,
                 ExoskeletonJointHandle::MovementDirection amplifyDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                 float startingVelocity = 30, float maxVelocity = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Resists movements towards the selected direction.
     * @param resistPercentage The maximum percentage of torque that the servos should use to resist the joint.
     * @param resistDirection ABDUCTION_OR_FLEXION, ADDUCTION_OR_EXTENSION, BOTH
     * @param minVelocity The minimum movement speed in deg/sec at which resistance will be applied.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void resist(float resistPercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                float minVelocity = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Constraints the arm's movements to the area defined by "pos" as the center for each joint and "radius" as the area around the center.
     * @param pos The center of the allowed area. Object holds information for each joint.
     * @param radius The area around the center of the allowed area.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void constrainTo(ExoArmAngles pos, float radius, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Guides the arm away from the provided area, defined by pos as the center for each joint and by radius as the area around the center.
     * @param angle The ExoArmAngles-object that defines the angle for each joint witch the joint should be guided away from.
     * @param radius The radius that defines the area around the center from which each joint should be guided away from.
     * @param amplifyPercentage The maximum percentage of torque that the servo should use to guide the joint towards the given area.
     * @param resistPercentage The maximum percentage of torque that the servo should use to guide the joint away from the given area.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void guideAway(ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Guides the arm towards the provided area, defined by pos as the center for each joint and by radius as the area around the center.
     * @param pos The ExoArmAngles-object that defines the angle for each joint that defines the center of the area towards which the joint should be guided to.
     * @param radius The radius that defines the area around the center towards which each joint should be guided to.
     * @param amplifyPercentage The maximum percentage of torque that the servo should use to guide the joint towards the given area.
     * @param resistPercentage The maximum percentage of torque that the servo should use to guide the joint away from the given area.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void guideTowards(ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Adds configurable random jerks to movements, that the user makes with the current arm.
     * @param minJerkAngle Minimum jerk angle
     * @param maxJerkAngle Maximum jerk angle
     * @param minJerkInterval Minimum jerk interval. Only time in which the user actually moved a joint counts.
     * @param maxJerkInterval Maximum jerk interval. Only time in which the user actually moved a joint counts.
     * @param maxAccumulatedMovementsLeft Maximum degrees that the action is allowed to move each joint into one direction before it needs to move into the other direction again.
     * @param maxAccumulatedMovementsRight Maximum degrees that the action is allowed to move each joint into one direction before it needs to move into the other direction again.
     * @param velocity The velocity that the jerks should be made with.
     * @param nrJerks The number of jerks to perform, before the action ends.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.

     */
    void jerk(float minJerkAngle, float maxJerkAngle, long minJerkInterval,
              long maxJerkInterval, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight, float velocity, long nrJerks = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Holds the velocity all active joints, that belong to the current arm, within a provided range, by accelerating or decelerating the joint.
     * @param minVelocity The minimum velocity
     * @param maxVelocity The maximum velocity
     * @param direction The direction that the action should affect.
     * @param amplifyFlexPercentage The maximum torque percentage, that the servos should use to amplify joint movements for the flex direction.
     * @param resistFlexPercentage The maximum torque percentage, that the servos should use to resist joint movements for the flex direction.
     * @param amplifyExtensionPercentage The maximum torque percentage, that the servos should use to amplify joint movements for the extension direction.
     * @param resistExtensionPercentage The maximum torque percentage, that the servos should use to resist joint movements for the extension direction.
     * @param alternativeFinishCondition If this conditions evaluates to true, the action will end.
     */
    void filterVelocity(float minVelocity, float maxVelocity,
                        ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                        float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05,
                        float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Returns an condition-object that evaluates if the arm is at the specified position.
     * @param exoArmAngle An ExoArmAngle-object that contains the target angles for each joint.
     * @param tolerance The tolerance around the joint angles that in which the joints are considered as "at their position".
     * @param duration The duration (in ms) after the condition automatically evaluates to true after being evaluated the first time.
     * @return The condition-object
     */
    ICondition& isAtExoArmAngle(ExoArmAngles exoArmAngle, float tolerance, unsigned long duration);
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONARM_H
