#ifndef JOINTBUILDERACTIVE_H
#define JOINTBUILDERACTIVE_H

#include "exo/ExoskeletonJointActiveHandle.h"

class JointBuilderActive {
    private:
    ArmSide armSide;
    JointType jointType;
    ExoskeletonJointActiveHandle* joint = nullptr;
    HX711* loadCell = nullptr;
    uint8_t dxl_id{};
    DynamixelShield& shield;
    uint8_t lower_range_of_motion = 0;
    uint8_t upper_range_of_motion = 0;

    public:

     /**
     * Creates a new JointBuilderActive instance that can be used to configure an exoskeleton joint.
     @param the side of the arm to which the joint belongs. Either LEFT or RIGHT
     @param the joint type. Either ELBOW, SHOULDER_SIDE, SHOULDER_BACK
     @param The DynamixelShield instance used to communicate with the servos.
     @return
     */
    JointBuilderActive(ArmSide side, JointType jointType, DynamixelShield& dxl);

    /**
     * Assigns a motor to the joint.
     * @param dxl_id The id of the servo that should be assigned to this shoulder back joint.
     * @return The current JointBuilderActive
     */
    JointBuilderActive& addMotor(uint8_t dxl_id);

    /**
     * Assigns a loadcell to the joint.
     * @param loadCell Optional (Nullable) parameter. The loadcell is used to measure force that is applied to the joint.
     * @return The current JointBuilderActive
     */
    JointBuilderActive& addLoadCell(HX711* loadcell);

    /**
     * Configures the joint's lower range of motion limit. 
     * @param lower_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's lower range of motion consists of 0 degrees counted from the default position.
     * @return The current JointBuilderActive
     */
    JointBuilderActive& addLowerRangeOfMotion(uint16_t lower_range_of_motion);

      /**
     * Configures the joint's upper range of motion limit. 
     * @param upper_mechanical_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's upper range of motion consists of 90 degrees counted from the default position.
     * @return The current JointBuilderActive
     */
    JointBuilderActive& addUpperRangeOfMotion(int16_t upper_range_of_motion);

    /**
     * Applies the created configuration and returns an ExoskeletonJointHandle
     * @return
     */
    ExoskeletonJointHandle* build() const;
};



#endif //JOINTBUILDERACTIVE_H
