
#include "IsMovingCondition.h"
#include "Arduino.h"
#include <util/DebugSerial.h>


void IsMovingCondition::configure(ExoskeletonJointHandle &joint) {
    c_joint = &joint;

    if (!c_joint->canTrackPosition())
    {
        DEBUG_SERIAL.println(F("Cannot configure IsMovingCondition! The joint does not have a position encoder."));
    }
    setConfigured();
}

bool IsMovingCondition::evalCondition() {
    return (abs(c_joint -> getVelocity())) >0;
}

IsMovingCondition::IsMovingCondition():
       ICondition(true) {}

void IsMovingCondition::restore() {}
