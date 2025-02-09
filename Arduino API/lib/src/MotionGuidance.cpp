///
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
Exoskeleton* exoskeleton;
ActionBuilder ab;
const float DXL_PROTOCOL_VERSION = 2.0;


void guideTowardsShoulderSide(ActionBuilder& ab) {
    exoskeleton->getRightArm().getShoulderSide().moveToActive(0,50,3);
    exoskeleton->getRightArm().getShoulderSide().guideTowards(0, 5, 0.03,0.03,nullptr);
}

void lockElbow(ActionBuilder& ab) {
    exoskeleton->getRightArm().getElbow().moveToActive(0,50,3);
    exoskeleton->getRightArm().getElbow().lock(1, nullptr);
}

void setup() {
    Serial.begin(1000000);

    dxl.begin(1000000l);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    dxl.ping(1);

    DEBUG_SERIAL.begin(115200);

    // TODO correct the dynamixel IDs
    exoHandle = &ExoskeletonBuilder()
            .addRightArm()
            .addElbowJoint(dxl, 4, nullptr)
                    //.addShoulderSideJoint(dxl, 3, nullptr)
            .addShoulderSideJoint(dxl, 1, nullptr)
            .finishArm()
            .build()
            .calibrate(PREFER_LOAD);


    exoskeleton = new Exoskeleton{ab, *exoHandle};

    ab.parallel(guideTowardsShoulderSide, lockElbow);
    ab.dispatch(ab.trueCondition(), 100);
}

void loop() {
    taskManager.runLoop();
}
*/