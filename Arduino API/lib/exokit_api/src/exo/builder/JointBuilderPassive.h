#ifndef JOINTBUILDERPASSIVE_H
#define JOINTBUILDERPASSIVE_H


#include "exo/ExoskeletonJointPassiveHandle.h"

class JointBuilderPassive {
    private:
    ArmSide armSide;
    JointType jointType;
    ExoskeletonJointPassiveHandle* joint = nullptr;
    ConfiguredEncoder* encoder = nullptr;
    HX711* loadCell = nullptr;
    uint8_t lower_restriction = 0;
    uint8_t upper_restriction = 0;

    public:
     /**
     * Creates a new JointBuilderPassive instance that can be used to configure an exoskeleton joint.
     @param the side of the arm to which the joint belongs. Either LEFT or RIGHT
     @param the joint type. Either ELBOW, SHOULDER_SIDE, SHOULDER_BACK
     @return
     */
    explicit JointBuilderPassive(ArmSide side, JointType jointType);

    /**
     * Assigns an encoder to the joint.
     * @param encoder object. The encoder is used to measure the position of the joint.
     * @return The current JointBuilderPassive
     */
    JointBuilderPassive& addEncoder(ConfiguredEncoder* encoder);

    /**
     * Assigns a loadcell to the joint.
     * @param loadCell object. The loadcell is used to measure force that is applied to the joint.
     * @return The current JointBuilderPassive
     */
    JointBuilderPassive& addLoadCell(HX711* loadCell);

    /**
     * Configures the joint's lower range of motion limit. 
     * @param lower_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's upper range of motion consists of 90 degrees counted from the default position.
     * @return The current JointBuilderPassive
     */
    JointBuilderPassive& addLowerRestriction(uint8_t lower_restriction);

    /**
     * Configures the joint's upper range of motion limit. 
     * @param upper_restriction Subtracts the given number of degrees from the joints allowed range of motion. The shoulder back joint's upper range of motion consists of 90 degrees counted from the default position.
     * @return The current JointBuilderPassive
     */
    JointBuilderPassive& addUpperRestriction(uint8_t upper_restriction);

    /**
     * Applies the created configuration and returns an ExoskeletonJointHandle
     * @return
     */
    ExoskeletonJointHandle* build() const;
};

#endif //JOINTBUILDERPASSIVE_H
