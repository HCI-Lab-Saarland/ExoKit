
#include "AtExoArmAngleCondition.h"
#include <Arduino.h>
#include <exo/ExoskeletonArmHandle.h>

bool AtExoArmAngleCondition::evalCondition() {
    if ((!(arm->getElbow().canTrackPosition()) || !exoArmAngle.isHasElbow() || (arm->getElbow().canTrackPosition() &&
                                                                                   ((abs(arm->getElbow().getPresentPosition() -
                                                                                         exoArmAngle.getElbowAngle())) <
                                                                                    tolerance)))
           && (!(arm->getShoulderBack().canTrackPosition()) || !exoArmAngle.isHasShoulderBack() ||
               (arm->getShoulderBack().canTrackPosition() &&
                ((abs(arm->getShoulderBack().getPresentPosition() - exoArmAngle.getShoulderBackAngle())) < tolerance)))
           && (!(arm->getShoulderSide().canTrackPosition()) || !exoArmAngle.isHasShoulderSide() ||
               (arm->getShoulderSide().canTrackPosition() &&
                ((abs(arm->getShoulderSide().getPresentPosition() - exoArmAngle.getShoulderSideAngle())) <
                 tolerance)))) {
        if(startTime == 0) {
            startTime = millis();
        }
        if (startTime + duration < millis()) {
            return true;
        } else {
            return false;
        }
    } else {
        startTime = 0;
        return false;
    }
}

void AtExoArmAngleCondition::restore() {}

AtExoArmAngleCondition::AtExoArmAngleCondition() :
        ICondition(true) {}

void AtExoArmAngleCondition::configure(ExoskeletonArmHandle &arm, ExoArmAngles exoArmAngle, float tolerance,
                                       unsigned long duration) {
    this->arm = &arm;
    this->exoArmAngle = exoArmAngle;
    this->tolerance = tolerance;
    this->duration = duration;
    setConfigured();
}
