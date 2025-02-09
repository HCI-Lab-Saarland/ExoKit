#include "ExoskeletonBuilder.h"
#include "util/DebugSerial.h"
#include "Arduino.h"
#include "exo/ExoskeletonStore.h"

void ExoskeletonBuilder::reset() {
    delete this->lArm;
    delete this->rArm;
}

ArmBuilder& ExoskeletonBuilder::addLeftArm() {
    this->lArm = new ArmBuilder(this, LEFT);
    return *lArm;
}

ArmBuilder& ExoskeletonBuilder::addRightArm() {
    this->rArm = new ArmBuilder(this, RIGHT);
    return *rArm;
}

ExoskeletonCalibrator ExoskeletonBuilder::build()
{
    if (this->lArm == nullptr) {
        this->lArm = new ArmBuilder(this, LEFT);
    }
    if (this->rArm == nullptr) {
        this->rArm = new ArmBuilder(this, RIGHT);
    }
    ExoskeletonHandle* exoskeleton = new ExoskeletonHandle(*(lArm->build()), *(rArm->build()));
    if(isEmergencyBtn) {
        exoskeleton->enableEmergencyBtn(emergencyBtnPin, emergencyBtnPullUp);
    }
    ExoskeletonStore::getInstance().add(*exoskeleton);

    this->reset();
    return ExoskeletonCalibrator(*exoskeleton);
}

ExoskeletonBuilder &ExoskeletonBuilder::addEmergencyShutdownButton(uint8_t buttonPin, bool isPullUp) {
    isEmergencyBtn = true;
    emergencyBtnPin = buttonPin;
    emergencyBtnPullUp = isPullUp;
    return *this;
}
