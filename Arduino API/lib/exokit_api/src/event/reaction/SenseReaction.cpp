#include "SenseReaction.h"

#include <util/DebugSerial.h>


bool SenseReaction::finishCondition() {
   return false;
}

void SenseReaction::runLoop()
{
    if(streamPosition)
    {
        DEBUG_SERIAL.print(this->c_joint->getPosition());
        DEBUG_SERIAL.print(F(" "));
    }

    if(streamVelocity)
    {
        DEBUG_SERIAL.print(this->c_joint->getVelocity());
        DEBUG_SERIAL.print(F(" "));
    }
    if(streamSpeed)
    {
        DEBUG_SERIAL.print(abs(this->c_joint->getVelocity()));
        DEBUG_SERIAL.print(F(" "));
    }

    if(streamLoadCell)
    {
        DEBUG_SERIAL.print(this->c_joint->readLoadCell());
    }
    DEBUG_SERIAL.println(F(""));
   
}

void SenseReaction::startup() {
   
}

void SenseReaction::shutdown(bool isCancel) {
    if(!isConfigured() || !isStarted()) {
        return;
    }
    /*c_joint->setTorque(c_lockStateAtStartup, this);*/
}

SenseReaction::SenseReaction(): IReaction(true) {}

void SenseReaction::prepare() {}

void SenseReaction::configure(ExoskeletonJointHandle& joint, bool streamPosition, bool streamVelocity, bool streamSpeed, bool streamLoadCell) {
    ExoskeletonJointHandle* c_joint{};
    ReactionConfigurationGuard configureGuard(*this);
    this->c_joint = &joint;
    this->streamPosition = streamPosition;
    this->streamVelocity = streamVelocity;
    this->streamSpeed = streamSpeed;
    this->streamLoadCell = streamLoadCell;
}
