#include "JointBuilderPassive.h"

JointBuilderPassive& JointBuilderPassive::addEncoder(ConfiguredEncoder* encoder) {
    this->encoder = encoder;
    return *this;
}


JointBuilderPassive& JointBuilderPassive::addLoadCell(HX711* loadCell) {
    this->loadCell = loadCell;
    return *this;
}

JointBuilderPassive& JointBuilderPassive::addLowerRestriction(uint8_t lower_restriction) {
    this->lower_restriction = lower_restriction;
    return *this;
}


JointBuilderPassive& JointBuilderPassive::addUpperRestriction(uint8_t upper_restriction) {
    this->upper_restriction = upper_restriction;
    return *this;
}

ExoskeletonJointHandle* JointBuilderPassive::build() const {
    auto* result = new ExoskeletonJointPassiveHandle(armSide, jointType, encoder, loadCell, lower_restriction, upper_restriction);
    return result;
}

JointBuilderPassive::JointBuilderPassive(ArmSide side, JointType jointType):
    armSide(side), jointType(jointType) {}
