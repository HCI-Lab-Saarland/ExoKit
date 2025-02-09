//
// Created by Marie Muehlhaus on 16.09.24.
//
/*
#include "event/simpleactionbuilder/ActionBuilder.h"
#include "exo/ConfiguredEncoder.h"
#include "DynamixelShield.h"
#include "exo/builder/ExoskeletonBuilder.h"
#include "event/simpleactionbuilder/Exoskeleton.h"

DynamixelShield dxl;
ExoskeletonHandle* exoHandle;
Exoskeleton* exoskeleton;
ExoskeletonArm* leftArm;
ExoskeletonArm* rightArm;
ActionBuilder ab;
const float DXL_PROTOCOL_VERSION = 2.0;

void rightResist(ActionBuilder& ab) {
    rightArm->resist(0.05);
}

void leftResist(ActionBuilder& ab) {
    leftArm->resist(0.05);
}

void parallelResist(ActionBuilder& ab) {
    ab.parallel(leftResist, rightResist);
}

 void setup() {
    Serial.begin(1000000);

    dxl.begin(1000000l);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    dxl.ping(1);

    DEBUG_SERIAL.begin(115200);

    // TODO correct the dynamixel IDs
     exoHandle = &ExoskeletonBuilder()
    .addLeftArm()
        .addElbowJoint(dxl, 4, nullptr)
        //.addShoulderSideJoint(dxl, 3, nullptr)
        .addShoulderBackJoint(dxl, 2, nullptr)
    .finishArm()
    .addRightArm()
        .addElbowJoint(dxl, 3, nullptr)
        //.addShoulderSideJoint(dxl, 3, nullptr)
        .addShoulderBackJoint(dxl, 1, nullptr)
    .finishArm()
    .build()
    .calibrate(PREFER_LOAD);

    exoskeleton = new Exoskeleton{ab, *exoHandle};
    leftArm = &(exoskeleton->getLeftArm());
    rightArm = &(exoskeleton->getRightArm());

    ab.loop(ab.trueCondition(), parallelResist);
    ab.dispatch(ab.trueCondition(), 100);
}

void loop() {
    taskManager.runLoop();
}
*/
