#ifndef CHI25_EXOSKELETON_API_EXOSKELETONJOINTHANDLE_H
#define CHI25_EXOSKELETON_API_EXOSKELETONJOINTHANDLE_H


#include "ExoskeletonComponent.h"
#include "ExoskeletonConstants.h"
#include "PositionProvider.h"

class ExoskeletonArmHandle;

class ExoskeletonJointHandle : public ExoskeletonComponentHandle, public PositionProvider {
    friend class ExoskeletonArmHandle;

public:
    enum MovementDirection {
        ABDUCTION_OR_FLEXION,
        ADDUCTION_OR_EXTENSION,
        BOTH
    };

private:
    ExoskeletonArmHandle *exoArm;
    ArmSide armSide;
    JointType jointType;

    virtual void setExoskeletonArm(ExoskeletonArmHandle &arm);

protected:
    int16_t lower_range_of_motion;
    int16_t upper_range_of_motion;
    bool negateAngles();

public:
    /**
     * Constructs an ExoskeletonJointHandle with specific joint parameters.
     * 
     * @param side The arm side (LEFT or RIGHT) to which this joint belongs.
     * @param jointType The type of joint (SHOULDER_SIDE, SHOULDER_BACK, ELBOW).
     * @param lower_range_of_motion The lower range of motion for this joint.
     * @param upper_range_of_motion The upper range of motion for this joint.
     */
    explicit ExoskeletonJointHandle(ArmSide side, JointType jointType, int16_t lower_range_of_motion = 0, int16_t upper_range_of_motion = 0);

    virtual bool isActive() = 0;

    /**
     * Gets the lower range of motion limit.
     * @return The lower range of motion limit of the joint.
     */
    float getLowerRangeOfMotion() const;

    /**
     * Gets the upper range of motion limit.
     * @return The upper range of motion limit of the joint.
     */
    float getUpperRangeOfMotion() const;

    virtual void tare(float currentAngle = 0.f) = 0;

    virtual bool hasLoadCell();

    virtual float readLoadCell() = 0;

    /**
     * Gets the matching ExoskeletonArmHandle.
     * @return The ExoskeletonArmHandle.
     */
    ExoskeletonArmHandle &getExoskeletonArm();

    virtual bool canTrackPosition();

    virtual float getPresentPosition();

    /**
     * Gets the current position of the joint.
     * 
     * @return The current position.
     */
    float getPosition() override;

    virtual float getVelocity();

    /**
     * Gets the joint type.
     * 
     * @return The joint type (ELBOW, SHOULDER_SIDE, SHOULDER_BACK).
     */
    JointType getType();

    /**
     * Gets the arm side.
     * 
     * @return The arm side (LEFT, RIGHT).
     */
    ArmSide getSide() const;
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONJOINTHANDLE_H
