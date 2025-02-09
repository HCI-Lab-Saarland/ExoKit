/*
#include "com/SerialCmdReader.h"
#include "event/simpleactionbuilder/ActionBuilder.h"
#include "exo/ConfiguredEncoder.h"
#include "DynamixelShield.h"
#include "exo/builder/ExoskeletonBuilder.h"
#include "com/ManualConditionTriggerCmd.h"
#include "event/simpleactionbuilder/Exoskeleton.h"

SerialCmdReader cmdReader(DEBUG_SERIAL, 10);
ActionBuilder ab;
DynamixelShield dxl;
ExoskeletonHandle* exoHandle;
Exoskeleton* exoskeleton;
ExoskeletonArm* leftArm;
ExoskeletonArm* rightArm;
ManualCondition moveCond;
ManualConditionTriggerCmd triggerMove("do1jerk", moveCond);

const float DXL_PROTOCOL_VERSION = 2.0;

void jerkLeftArm(ActionBuilder& ab)
{
   leftArm->jerk(20,20,1500,1500,100,100,0);
}

void jerkRightArm(ActionBuilder& ab) {
   rightArm->jerk(20,20,1500,1500,100,100,0);
}

void parallelJerk(ActionBuilder& ab)
{
   ab.parallel( jerkLeftArm, jerkRightArm);
}


ICondition& startPose()
{
   return (leftArm->getElbow().isAtPosition(EQUAL, 0, 20)
           && rightArm->getElbow().isAtPosition(EQUAL, 0, 20));
}

void setup() {
   Serial.begin(1000000);

   dxl.begin(1000000l);
   dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
   dxl.ping(1);

   DEBUG_SERIAL.begin(115200);
   cmdReader.registerCmd(triggerMove);
   moveCond.configure(true, false);

   // TODO correct the dynamixel IDs
   exoHandle = &ExoskeletonBuilder()
           .addLeftArm()
           .addElbowJoint(dxl, 4, nullptr)
            .addShoulderSideJoint(dxl, 5, nullptr)
           .addShoulderBackJoint(dxl, 2, nullptr)
           .finishArm()
           .addRightArm()
           .addElbowJoint(dxl, 3, nullptr)
            .addShoulderSideJoint(dxl, 6, nullptr)
           .addShoulderBackJoint(dxl, 1, nullptr)
           .finishArm()
           .build()
           .calibrate(PREFER_LOAD);

   exoskeleton = new Exoskeleton{ab, *exoHandle};
   leftArm = &(exoskeleton->getLeftArm());
   rightArm = &(exoskeleton->getRightArm());

   parallelJerk(ab);
   ab.dispatch(startPose(), 10);

}

void loop() {
   taskManager.runLoop();
}
*/
