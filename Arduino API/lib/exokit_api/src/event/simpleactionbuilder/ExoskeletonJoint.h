#ifndef CHI25_EXOSKELETON_API_EXOSKELETONJOINT_H
#define CHI25_EXOSKELETON_API_EXOSKELETONJOINT_H


#include "exo/ExoskeletonJointHandle.h"
#include "ActionBuilder.h"
#include "event/reaction/JointMoveToReaction.h"
#include "event/reaction/PassiveJointMoveToReaction.h"
#include "event/concept/GesturesNotifications/VibrationReaction.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/concept/Guidance/ConstrainToReaction.h"
#include "event/concept/Guidance/GuideAwayReaction.h"
#include "event/concept/Guidance/GuideTowardsReaction.h"
#include "event/concept/MotionStyle/JerkReaction.h"
#include "event/concept/MotionStyle/FilterSpeedReaction.h"
#include "event/condition/ForceCondition.h"
#include "event/condition/IsMovingTowardCondition.h"
#include "event/condition/IsMovingCondition.h"
#include "event/condition/IsAcceleratingCondition.h"
#include "event/condition/AccelerationCondition.h"

class ExoskeletonJoint {
    struct lock_reaction_entry_t {
        JointLockReaction* lr;
        unsigned long id;
    };

    ActionBuilder& ab;
    ExoskeletonJointHandle& joint;
    LinkedList<lock_reaction_entry_t> lockReactions;

    bool getLockReaction(unsigned long id, ExoskeletonJointActiveHandle& joint, JointLockReaction** outLockReaction);

public:
    ExoskeletonJoint(ActionBuilder &ab, ExoskeletonJointHandle& joint);

    /**
     * A joint is considered to be active if it can be moved by means of a servo.
     * @return True is the joint is active, False otherwise
     */
    bool isActive();

    /**
     * Returns the joint handle
     * @return The joint handle
     */
    ExoskeletonJointHandle& unwrap();

    /**
     * Waits till the joint is moved to the specified position.
     * @param targetAngle The angle to which the joint should be moved to.
     * @param tolerance The area around the goal angle that counts to the goal position.
     * @param targetType ABSOLUTE (to zero position), RELATIVE_STARTING_POS (relative to the position at which the action started), RELATIVE_CURRENT_POS (Relative to the position of the joint when the software is started.)
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void moveToPassive(float targetAngle, float tolerance = 5, TargetType targetType = ABSOLUTE,
                       ICondition* alternativeFinishCondition = nullptr);

    /**
     * Moves the joint to a specified angle.
     * @param goalAngle The angle to which the joint should be moved to.
     * @param velocity The speed with which the joint should be moved
     * @param goalAngleTolerance The area around the goal angle that counts to the goal position.
     * @param targetType ABSOLUTE (to zero position), RELATIVE_STARTING_POS (relative to the position at which the action started), RELATIVE_CURRENT_POS (Relative to the position of the joint when the software is started.)
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void moveToActive(float goalAngle, float velocity, float goalAngleTolerance = 5, TargetType targetType = ABSOLUTE,
                      ICondition* alternativeFinishCondition = nullptr);

    /**
     * Lets this joint mirror a different joint
     * @param sourceJoint The joint to mirror.
     * @param scaleFactor A multiplication factor that the position of the source joint gets multiplied with.
     * @param velocity The maximum velocity at which this joint performs movements.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void mirror(ExoskeletonJoint sourceJoint, float scaleFactor, float velocity, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Starts to vibrate the joint
     * @param frequency The frequency
     * @param amplitude The amplitude
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void vibrate(uint8_t frequency, float amplitude, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Amplifies movements toward the selected direction
     * @param amplifyPercentage The maximum percentage of torque that the servo should use to amplify the joint.
     * @param amplifyDirection ABDUCTION_OR_FLEXION, ADDUCTION_OR_EXTENSION, BOTH
     * @param startingVelocity The minimum movement speed in deg/sec at which amplification will be applied.
     * @param maxVelocity The maximum movement speed in deg/sec at which amplification will be applied.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void amplify(float amplifyPercentage, ExoskeletonJointHandle::MovementDirection amplifyDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                 float startingVelocity = 30, float maxVelocity = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Resists movements towards the selected direction.
     * @param resistancePercentage The maximum percentage of torque that the servo should use to resist the joint.
     * @param resistDirection ABDUCTION_OR_FLEXION, ADDUCTION_OR_EXTENSION, BOTH
     * @param minVelocity The minimum movement speed in deg/sec at which resistance will be applied.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void resist(float resistancePercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                float minVelocity = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Constraints the joint's movement radius to the area defined by "angle" as the center and "radius" as the area around the center.
     * @param angle The center of the allowed area.
     * @param radius The area around the center of the allowed area.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void constrainTo(float angle, float radius, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Guides the joint away from the provided area, defined by angle as the center and by radius as the area around the center.
     * @param angle The angle that defines the center of the area from witch the joint should be guided away from.
     * @param radius The radius that defines the area around the center from which the joint should be guided away from.
     * @param amplifyPercentage The maximum percentage of torque that the servo should use to guide the joint towards the given area.
     * @param resistPercentage The maximum percentage of torque that the servo should use to guide the joint away from the given area.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void guideAway(float angle, float radius, float amplifyPercentage = 0.05, float resistPercentage = 0.05,
                   ICondition* alternativeFinishCondition = nullptr);

    /**
     * Guides the joint towards the provided area, defined by angle as the center and by radius as the area around the center.
     * @param angle The angle that defines the center of the area towards which the joint should be guided to.
     * @param radius The radius that defines the area around the center towards which the joint should be guided to.
     * @param amplifyPercentage The maximum percentage of torque that the servo should use to guide the joint towards the given area.
     * @param resistPercentage The maximum percentage of torque that the servo should use to guide the joint away from the given area.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void guideTowards(float angle, float radius, float amplifyPercentage, float resistPercentage,
                      ICondition* alternativeFinishCondition = nullptr);

    /**
     * Adds configurable random jerks to movements, that the user makes with the current joint.
     * @param minJerkAngle Minimum jerk angle
     * @param maxJerkAngle Maximum jerk angle
     * @param minJerkInterval Minimum jerk interval. The only time in which the user actually moved the joint counts.
     * @param maxJerkInterval Maximum jerk interval. The only time in which the user actually moved the joint counts.
     * @param maxAccumulatedMovementsLeft Maximum degrees that the action is allowed to move the joint into one direction before it needs to move into the other direction again.
     * @param maxAccumulatedMovementsRight Maximum degrees that the action is allowed to move the joint into one direction before it needs to move into the other direction again.
     * @param velocity The velocity that the jerks should be made with.
     * @param nrJerks The number of jerks to perform, before the action ends.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void jerk(float minJerkAngle, float maxJerkAngle, long minJerkInterval, long maxJerkInterval,
              float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight, float velocity,
              long nrJerks = 0, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Holds the velocity of the joint within a provided range, by accelerating or decelerating the joint.
     * @param minVelocity The minimum velocity
     * @param maxVelocity The maximum velocity
     * @param direction The direction that the action should affect.
     * @param amplifyFlexPercentage The maximum torque percentage, that the servos should use to amplify joint movements for the flex direction.
     * @param resistFlexPercentage The maximum torque percentage, that the servos should use to resist joint movements for the flex direction.
     * @param amplifyExtensionPercentage The maximum torque percentage, that the servos should use to amplify joint movements for the extension direction.
     * @param resistExtensionPercentage The maximum torque percentage, that the servos should use to resist joint movements for the extension direction.
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void filterVelocity(float minVelocity, float maxVelocity,
                        ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                        float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05,
                        float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05,
                        ICondition* alternativeFinishCondition = nullptr);

  /**
     * Holds the velocity of the joint within a provided range, by accelerating or decelerating the joint.
     * @param streamPosition If true prints the absolute angle in degrees for the joint.
     * @param streamVelocity If true prints the velocity in degrees/second for the joint.
     * @param streamSpeed If true prints the speed in degrees/second for the joint.
     * @param streamLoadCell If true prints the force applied to the joint’s associated load cell.     
     * @param alternativeFinishCondition If this condition evaluates to true, the action will end.
     */
    void streamSensorData(bool streamPosition, bool streamVelocity, bool streamSpeed, bool streamLoadCell, ICondition* alternativeFinishCondition=nullptr);


    /**
     * Locks the current joint into its position.
     * @param lockId The ID of the lock. To unlock the joint again, the unlock(lockId)-function needs to be called.
     * @param alternativeFinishCondition If this condition evaluates to true, the lock will be unlocked.
     */
    void lock(unsigned long lockId, ICondition* alternativeFinishCondition = nullptr);

    /**
     * Unlocks the lock with the id lockId.
     * @param lockId The id of the lock
     */
    void unlock(unsigned long lockId);

    /**
     * Returns a Condition-Object that evaluates to true, if the joint's velocity speed is slower/faster/equal to the provided value.
     * @param compareType SLOWER_THAN (actualVelocity < thresholdDegreePerSecond + tolerance), FASTER_THAN (actualVelocity > thresholdDegreePerSecond - tolerance),
     * WITHIN (actualVelocity > thresholdDegreePerSecond - tolerance and actualVelocity < thresholdDegreePerSecond + tolerance)
     * @param thresholdDegreePerSecond The value to compare the joint's speed to.
     * @param tolerance The tolerance.
     * @return The condition object.
     */
    VelocityCondition& isVelocity(SpeedCompareType compare, float thresholdDegreePerSecond, float tolerance = 0);

    /**
     * Returns a Condition-Object that evaluates to true, if the joint's movement speed is slower/faster/equal to the provided value.
     * @param compareType SLOWER_THAN (actualSpeed < thresholdDegreePerSecond + tolerance), FASTER_THAN (actualSpeed > thresholdDegreePerSecond - tolerance),
     * WITHIN (actualSpeed > thresholdDegreePerSecond - tolerance and actualSpeed < thresholdDegreePerSecond + tolerance)
     * @param thresholdDegreePerSecond The value to compare the joint's speed to.
     * @param tolerance The tolerance.
     * @return The condition object.
     */
    SpeedCondition& isSpeed(SpeedCompareType compareType, float thresholdDegreePerSecond, float tolerance = 0);

    /**
     * Returns a Condition-Object that evaluates to true, if the joint is moving towards the provided direction.
     * @param direction The Direction. Can be ABDUCTION_OR_FLEXION, ADDUCTION_OR_EXTENSION, BOTH
     * @param thresholdVelocity The minimum velocity that the joint must have before the movement counts as an actual movement.
     * @return The condition object.
     */
    IsMovingTowardCondition& isMovingTowards(ExoskeletonJointHandle::MovementDirection direction, float thresholdVelocity = 5);

    /**
     * Returns a Condition-Object that evaluates to true, if the joint is currently moving.
     * @return The condition object.
     */
    IsMovingCondition& isMoving();

    /**
     * Returns a Condition-Object that evaluates to true, if the absolute acceleration is larger than the provided threshold.
     * Negative acceleration (breaking) multiplied by -1.
     * @param accelerationThreshold The threshold.
     * @return The condition object.
     */
    IsAcceleratingCondition& isAccelerating(float accelerationThreshold = 1);

    /**
     * Returns a Condition-Object that evaluates to true, if the load cell for the current joint measures a force below/above/within the specified value.
     * @param compareType WEAKER_THAN (actualPressure < force - tolerance), STRONGER_THAN (actualPressure > force + tolerance), WITHIN
     * @param force The force value to compare the load cells measured force against.
     * @param tolerance The tolerance
     * @return The condition object.
     */
    ForceCondition& isForce(ForceCondition::ForceCompareType compareType, float force, float tolerance = 0);

    /**
     * Returns a Condition-Object that evaluates to true, if a joint is below/above/at the specified angle.
     * @param compareType LOWER_THEN (actualAngle  < angle - tolerance), HIGHER_EQUAL_THAN (actualAngle >= angle + tolerance), EQUAL (around tolerance)
     * @param angle The angle to compare the joint's angle to.
     * @param tolerance The tolerance.
     * @return The condition object.
     */
    AtPositionCondition& isAtPosition(CompareType compareType, float angle, float tolerance);

    /**
     * Returns a Condition-Object that evaluates if the acceleration of the joint is smaller/larger/within a specified range.
     * The acceleration is negative when slowing down.
     * @param compareType If SLOWER_THAN/FASTER_THAN: Condition evals to true, if the joint acceleration is smaller/larger
     * than the acceleration parameter plus (smaller) / minus (larger) the tolerance parameter.
     * If WITHIN: Condition evaluates to true, if the acceleration is in the range of the acceleration-parameter
     * plus and minus the tolerance parameter.
     * @param acceleration The value that the joints acceleration gets compared with.
     * @param tolerance The tolerance. Gets added, if compareType=SLOWER_THAN and substracted if compareType=FASTER_THAN
     * @return The condition object.
     */
    AccelerationCondition& isAcceleration(SpeedCompareType compareType, float acceleration, float tolerance = 0);
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONJOINT_H
