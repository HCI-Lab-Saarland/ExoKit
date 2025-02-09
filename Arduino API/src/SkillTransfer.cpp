//
// Created by Alexander on 03.09.2024.
//
/*
#include "event/simpleactionbuilder/ActionBuilder.h"
#include "exo/ConfiguredEncoder.h"
#include "DynamixelShield.h"
#include "exo/builder/ExoskeletonBuilder.h"
#include "event/simpleactionbuilder/Exoskeleton.h"

DynamixelShield dxl;
ExoskeletonHandle* exoHandle;
ConfiguredEncoder encoderElbow(A2, 300);
ConfiguredEncoder eEncoderShoulderBack(A0, 300);
ConfiguredEncoder encoderShoulderSide(A1, 300);
ActionBuilder ab;
Exoskeleton* exoskeleton; 
const float DXL_PROTOCOL_VERSION = 2.0;


void mirrorElbow2ShoulderSide(ActionBuilder& ab) {
    exoskeleton->getLeftArm().getShoulderSide().mirror(exoHandle->getRightArm().getElbow(), 1, nullptr);
}

void mirrorShoulderSide2Elbow(ActionBuilder& ab) {
    exoskeleton->getLeftArm().getElbow().mirror(exoHandle->getRightArm().getShoulderSide(), 1, nullptr);
}

void mirrorShoulderBack(ActionBuilder& ab)
{
    exoskeleton->getLeftArm().getShoulderBack().mirror(exoHandle->getRightArm().getShoulderBack(), 1, nullptr);
}
void mirrorOtherJoints(ActionBuilder& ab)
{
    ab.parallel(mirrorShoulderSide2Elbow,mirrorShoulderBack);
}

void setup() {
    Serial.begin(1000000);

    dxl.begin(1000000l);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    dxl.ping(1);

    DEBUG_SERIAL.begin(115200);

    exoHandle = &ExoskeletonBuilder()
            .addLeftArm()
            .addElbowJoint(dxl, 4, nullptr)
            .addShoulderSideJoint(dxl, 1, nullptr)
            .addShoulderBackJoint(dxl, 2, nullptr)
            .finishArm()
            .addRightArm()
            .addElbowJoint(&encoderElbow, nullptr)
            .addShoulderSideJoint(&encoderShoulderSide, nullptr)
            .addShoulderBackJoint(&eEncoderShoulderBack, nullptr)
            .finishArm()
            .build()
            .calibrate(ASK_CREATE);

    exoskeleton = new Exoskeleton{ab, *exoHandle};
    // collaborative body-actuated play - level 1
    //exoskeleton->getLeftArm().mirror(exo->getRightArm(), true, true, true);

    // collaborative body-actuated play - level 2
    //exoskeleton->getLeftArm().mirror(exo->getRightArm(), true, true, true, 2, 2, 2);

    // collaborative body-actuated play - level 3
    ab.parallel(mirrorElbow2ShoulderSide, mirrorOtherJoints);

    ab.dispatch(ab.trueCondition(), 100);
}

void loop() {
    taskManager.runLoop();
}
*/
