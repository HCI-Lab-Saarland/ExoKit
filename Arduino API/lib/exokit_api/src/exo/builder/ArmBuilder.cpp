#include "ArmBuilder.h"
#include "JointBuilderPassive.h"
#include "exo/ExoskeletonHandle.h"
#include "ExoskeletonBuilder.h"
#include "JointBuilderActive.h"

ArmBuilder::ArmBuilder(ExoskeletonBuilder* exoskeleton_builder, ArmSide side): exoskeleton_builder(exoskeleton_builder), side(side) {}

ExoskeletonArmHandle* ArmBuilder::build() {
    if (elbow == nullptr)
    {
        this -> elbow = JointBuilderPassive(side, ELBOW).build();
    }
    if (shoulder_back == nullptr)
    {
        this -> shoulder_back = JointBuilderPassive(side, SHOULDER_BACK).build();
    }
    if (shoulder_side == nullptr)
    {
        this -> shoulder_side = JointBuilderPassive(side, SHOULDER_SIDE).build();
    }

    auto* result = new ExoskeletonArmHandle(*shoulder_back, *shoulder_side, *elbow, side);
    //this->reset();
    return result;
}

ExoskeletonBuilder& ArmBuilder::finishArm(){
    return *(this->exoskeleton_builder);
}

ArmBuilder& ArmBuilder::addElbowJoint(ConfiguredEncoder* encoder, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    this -> elbow = JointBuilderPassive(side, ELBOW)
            .addEncoder(encoder)
            .addLoadCell(loadCell)
            .addLowerRestriction(0 - lower_mechanical_restriction)
            .addUpperRestriction(115 - upper_mechanical_restriction)
            .build();
    return *this;
}

ArmBuilder& ArmBuilder::addElbowJoint(DynamixelShield& dxl, uint8_t dxl_id, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    //this -> elbow = JointBuilderActive().addShield(dxl).addMotor(dxl_id).addLoadCell(loadCell).build();
    this -> elbow = JointBuilderActive(side, ELBOW, dxl)
            .addMotor(dxl_id)
            .addLoadCell(loadCell)
            .addLowerRangeOfMotion(0 - lower_mechanical_restriction)
            .addUpperRangeOfMotion(115 - upper_mechanical_restriction)
            .build();

    return *this;
}

ArmBuilder& ArmBuilder::addShoulderSideJoint(ConfiguredEncoder* encoder, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    this -> shoulder_side = JointBuilderPassive(side, SHOULDER_SIDE)
            .addEncoder(encoder)
            .addLoadCell(loadCell)
            .addLowerRestriction(20 - lower_mechanical_restriction)
            .addUpperRestriction(115 - upper_mechanical_restriction)
            .build();
    return *this;
}

ArmBuilder& ArmBuilder::addShoulderSideJoint(DynamixelShield &dxl, uint8_t dxl_id, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    //this -> shoulder_side = JointBuilderActive().addShield(dxl).addMotor(dxl_id).addLoadCell(loadCell).build();
    this -> shoulder_side = JointBuilderActive(side, SHOULDER_SIDE, dxl)
            .addMotor(dxl_id)
            .addLoadCell(loadCell)
            .addLowerRangeOfMotion(20 - lower_mechanical_restriction)
            .addUpperRangeOfMotion(115 - upper_mechanical_restriction)
            .build();
    return *this;
}

ArmBuilder& ArmBuilder::addShoulderBackJoint(ConfiguredEncoder* encoder, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    this -> shoulder_back = JointBuilderPassive(side, SHOULDER_BACK)
            .addEncoder(encoder)
            .addLoadCell(loadCell)
            .addLowerRestriction(0 - lower_mechanical_restriction)
            .addUpperRestriction(90 - upper_mechanical_restriction)
            .build();
    return *this;
}

ArmBuilder& ArmBuilder::addShoulderBackJoint(DynamixelShield &dxl, uint8_t dxl_id, HX711* loadCell, uint8_t
        lower_mechanical_restriction, uint8_t upper_mechanical_restriction) {
    //this -> shoulder_back = JointBuilderActive().addShield(dxl).addMotor(dxl_id).addLoadCell(loadCell).build();
    this -> shoulder_back = JointBuilderActive(side, SHOULDER_BACK, dxl)
            .addMotor(dxl_id).addLoadCell(loadCell)
            .addLowerRangeOfMotion(0 - lower_mechanical_restriction)
            .addUpperRangeOfMotion(90 - upper_mechanical_restriction)
            .build();
    return *this;
}
