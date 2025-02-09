
#include "VibrationTest.h"

#include <util/DebugSerial.h>


bool VibrationTest::finishCondition() {
    return false;
}

void VibrationTest::runLoop() {
    float position = c_joint->getPresentPosition();
    unsigned long start_time = millis();
    c_joint->setGoalPosition(position + c_amplitude);
    while(start_time + period * 0.25 * 1000 * 2 > millis()) {}

    start_time = millis();
    c_joint->setGoalPosition(position);
    while(start_time + period * 0.25 * 1000 > millis()) {}

    start_time = millis();
    c_joint->setGoalPosition(position - c_amplitude);
    while(start_time + period * 0.25 * 1000 > millis()) {}

    start_time = millis();
    c_joint->setGoalPosition(position);
    while(start_time + period * 0.25 * 1000 > millis()) {}
}

void VibrationTest::startup() {
    c_lockStateAtStartup = c_joint->getIsTorque();
    c_lockOPatStartup = c_joint->getJointMode();
    c_joint->setJointMode(OP_EXTENDED_POSITION);
    c_joint->setGoalVelocity(velocity_required);
    c_joint->setTorque(true);
}

void VibrationTest::shutdown(bool isCancel) {
    if(!isConfigured() || !isStarted()) {
        return;
    }
    c_joint->setJointMode(c_lockOPatStartup);
    c_joint->setTorque(c_lockStateAtStartup);
}

VibrationTest::VibrationTest():
    IReaction(true) {}

void VibrationTest::configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude) { //, int duration) {
    ReactionConfigurationGuard configureGuard(*this);
    c_joint = &joint;

    c_joint = &joint;
    if (!c_joint->isActive())
    {
        DEBUG_SERIAL.println(F("Cannot vibrate with passive joint!"));
    }

    c_frequency = frequency;
    c_amplitude = amplitude;

    period = 1.0/c_frequency;
    velocity_required = 4.0 * c_amplitude * c_frequency;


    int max_velocity_available = c_joint -> getMaxNoLoadSpeed(); // in deg/sec
    if (velocity_required >= max_velocity_available) {
        velocity_required = max_velocity_available -1; // -1  some buffer

        c_frequency = velocity_required / (4.0 * c_amplitude);
        period = 1.0/c_frequency;
    }
}

void VibrationTest::prepare() {}


