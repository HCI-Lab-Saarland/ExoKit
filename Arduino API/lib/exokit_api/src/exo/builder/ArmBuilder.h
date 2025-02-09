#ifndef ARMBUILDER_H
#define ARMBUILDER_H

#include "exo/ExoskeletonHandle.h"
#include "ExoskeletonBuilder.h"
#include "exo/ConfiguredEncoder.h"
#include "HX711.h"
#include "DynamixelShield.h"

class ExoskeletonBuilder;

class ArmBuilder
{
    friend class ExoskeletonBuilder;
private:
    ExoskeletonBuilder* exoskeleton_builder = nullptr;
    ArmSide side;
    ExoskeletonArmHandle* exoArm = nullptr;
    ExoskeletonJointHandle* elbow = nullptr;
    ExoskeletonJointHandle* shoulder_side = nullptr;
    ExoskeletonJointHandle* shoulder_back = nullptr;

    //void reset();
    ExoskeletonArmHandle* build();
public:
    ArmBuilder(ExoskeletonBuilder* exoskeleton_builder, enum ArmSide side);

    /**
     * Completes the arm configuration and returns to the ExoskeletonBuilder
     * @return The ExoskeletonBuilder
     */
    ExoskeletonBuilder& finishArm();

    /**
     * Adds a passive elbow joint to the arm.
     * @param encoder Optional (Nullable) parameter. The ConfiguredEncoder is used to measure the joint's position, velocity and acceleration.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The elbows lower range of motion consists of 0 degrees counted from the default position.
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The elbows upper range of motion consists of 115 degrees counted from the default position.
     * @return The current ArmBuilder
     */
    ArmBuilder& addElbowJoint(ConfiguredEncoder* encoder = nullptr, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);

    /**
     * Adds an active elbow joint to the arm.
     * @param dxl The DynamixelShield instance used to communicate with the servos.
     * @param dxl_id The id of the servo that should be assigned to this elbow joint.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The elbows lower range of motion consists of 0 degrees counted from the default position.
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The elbows upper range of motion consists of 115 degrees counted from the default position.
     * @return The current ArmBuilder
     */
    ArmBuilder& addElbowJoint(DynamixelShield& dxl, uint8_t dxl_id, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);

   /**
    * Adds a passive shoulder side joint to the arm.
    * @param encoder Optional (Nullable) parameter. The ConfiguredEncoder is used to measure the joint's position, velocity and acceleration.
    * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
    * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder side joint's lower range of motion consists of 20 degrees counted from the default position.
    * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder side joint's upper range of motion consists of 115 degrees counted from the default position.
    * @return The current ArmBuilder
    */
    ArmBuilder& addShoulderSideJoint(ConfiguredEncoder* encoder = nullptr, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);
    /**
     * Adds an active shoulder side joint to the arm.
     * @param dxl The DynamixelShield instance used to communicate with the servos.
     * @param dxl_id The id of the servo that should be assigned to this shoulder side joint.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder side joint's lower range of motion consists of 20 degrees counted from the default position.
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder side joint's upper range of motion consists of 115 degrees counted from the default position.
     * @return The current ArmBuilder
     */
    ArmBuilder& addShoulderSideJoint(DynamixelShield &dxl, uint8_t dxl_id, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);

    /**
     * Adds a passive shoulder back joint to the arm.
     * @param encoder Optional (Nullable) parameter. The ConfiguredEncoder is used to measure the joint's position, velocity and acceleration.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's lower range of motion consists of 0 degrees counted from the default position.
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's upper range of motion consists of 90 degrees counted from the default position.
     * @return The current ArmBuilder
     */
    ArmBuilder& addShoulderBackJoint(ConfiguredEncoder* encoder = nullptr, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);

    /**
     * Adds an active shoulder back joint to the arm.
     * @param dxl The DynamixelShield instance used to communicate with the servos.
     * @param dxl_id The id of the servo that should be assigned to this shoulder back joint.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's lower range of motion consists of 0 degrees counted from the default position.
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's upper range of motion consists of 90 degrees counted from the default position.
     * @return The current ArmBuilder
     */
    ArmBuilder& addShoulderBackJoint(DynamixelShield &dxl, uint8_t dxl_id, HX711* loadCell = nullptr, uint8_t
        lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);
};

#endif //ARMBUILDER_H
