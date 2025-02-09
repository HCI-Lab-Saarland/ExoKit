#include "JointBuilderActive.h"
JointBuilderActive::JointBuilderActive(ArmSide side, JointType jointType, DynamixelShield& dxl):
        armSide(side), jointType(jointType), shield(dxl) {
   
}


JointBuilderActive& JointBuilderActive::addMotor(uint8_t dxl_id) {
    this->dxl_id = dxl_id;
    return *this;
}

JointBuilderActive& JointBuilderActive::addLoadCell(HX711* loadCell) {
    this->loadCell = loadCell;
    return *this;
}


JointBuilderActive& JointBuilderActive::addLowerRangeOfMotion(uint16_t lower_range_of_motion) {
    this->lower_range_of_motion = lower_range_of_motion;
    return *this;
}


JointBuilderActive& JointBuilderActive::addUpperRangeOfMotion(int16_t upper_range_of_motion) {
    this->upper_range_of_motion = upper_range_of_motion;
    return *this;
}

ExoskeletonJointHandle* JointBuilderActive::build() const {
    auto* result = new ExoskeletonJointActiveHandle(armSide, jointType, shield, dxl_id, loadCell, lower_range_of_motion, upper_range_of_motion);
    return result;
}
