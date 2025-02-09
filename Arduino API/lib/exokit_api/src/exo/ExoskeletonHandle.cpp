#include "ExoskeletonHandle.h"
#include "EEPROM.h"
#include "util/DebugSerial.h"
#include "TaskManager.h"
#include "ExoskeletonJointActiveHandle.h"

ExoskeletonHandle::ExoskeletonHandle(ExoskeletonArmHandle &left, ExoskeletonArmHandle &right) :
        leftArm(left), rightArm(right), romKillSwitchExecutable{*this}, emergencyBtnExecutable{*this} {
    leftArm.setExoskeleton(*this);
    rightArm.setExoskeleton(*this);
    enableRomKillSwitch(true);
}


ExoskeletonHandle::~ExoskeletonHandle() {
    enableRomKillSwitch(false);
}

void ExoskeletonHandle::enableRomKillSwitch(bool isEnable) {
    if(isEnable == isEnableRomKillSwitch) {
        return;
    }
    if(isEnable) {
        romKillSwitchTaskId = taskManager.scheduleFixedRate(50, &romKillSwitchExecutable, TIME_MILLIS);
    } else {
        taskManager.cancelTask(romKillSwitchTaskId);
    }
    isEnableRomKillSwitch = isEnable;
}

ExoskeletonArmHandle &ExoskeletonHandle::getLeftArm() {
    return leftArm;
}

ExoskeletonArmHandle &ExoskeletonHandle::getRightArm() {
    return rightArm;
}

void ExoskeletonHandle::printInfo() {
    DEBUG_SERIAL.println(F("---PRINTING EXO CONFIGURATION---"));
    DEBUG_SERIAL.print(F("LEFT ARM CONFIG: "));
    leftArm.printInfo();

    DEBUG_SERIAL.println("");

    DEBUG_SERIAL.print(F("RIGHT ARM CONFIG: "));
    rightArm.printInfo();

    DEBUG_SERIAL.println(F("---END OF EXO CONFIGURATION---"));
}

EepromId ExoskeletonHandle::getEepromId() {
    return EXO;
}

int16_t ExoskeletonHandle::loadConfigFromEEPROM(int16_t offset) {
    EepromId readID;
    EEPROM.get(offset, readID);
    if(readID != getEepromId()) {
        return -1;
    }
    offset += int16_t(sizeof(readID));
    offset = leftArm.loadConfigFromEEPROM(offset);
    if(offset < 0) {
        return -1;
    }
    offset = rightArm.loadConfigFromEEPROM(offset);
    if(offset < 0) {
        return -1;
    }
    return offset;
}

int16_t ExoskeletonHandle::persistConfigToEEPROM(int16_t offset) {
    EEPROM.put(offset, getEepromId());
    offset +=  int16_t(sizeof(getEepromId()));
    offset = leftArm.persistConfigToEEPROM(offset);
    offset = rightArm.persistConfigToEEPROM(offset);
    return offset;
}

void ExoskeletonHandle::enableEmergencyBtn(uint8_t buttonPin, bool isPullUp) {
    emergencyBtnExecutable.configure(buttonPin, isPullUp);
    if(!isEnableEmergencyBtn) {
        emergencyBtnTaskId = taskManager.scheduleFixedRate(50, &emergencyBtnExecutable, TIME_MILLIS);
        isEnableEmergencyBtn = true;
    }
}

void ExoskeletonHandle::setId(int8_t id) {
    this->id = id;
}

int8_t ExoskeletonHandle::getId() {
    return id;
}

ExoskeletonRomKillSwitchExecutable::ExoskeletonRomKillSwitchExecutable(
        ExoskeletonHandle &exo): exo(exo) {}

void ExoskeletonRomKillSwitchExecutable::exec() {
    bool kill = traverseArm(exo.getLeftArm(), false);
    kill |= traverseArm(exo.getRightArm(), false);

    if(!kill) {
        return;
    }
    traverseArm(exo.getLeftArm(), true);
    traverseArm(exo.getRightArm(), true);

    DEBUG_SERIAL.println(F("!!! --> Joint out of bounds <-- !!!"));
    DEBUG_SERIAL.println(F("Performing emergency shutdown."));
    DEBUG_SERIAL.flush();
    exit(1);
}

bool ExoskeletonRomKillSwitchExecutable::traverseArm(ExoskeletonArmHandle &arm, bool disableTorque) {
    bool outOfBounds = false;
    outOfBounds |= checkJoint(arm.getElbow(), disableTorque);
    outOfBounds |= checkJoint(arm.getShoulderSide(), disableTorque);
    outOfBounds |= checkJoint(arm.getShoulderBack(), disableTorque);
    return outOfBounds;
}

bool ExoskeletonRomKillSwitchExecutable::checkJoint(ExoskeletonJointHandle &joint, bool disableTorque) {
    if(!joint.isActive()) {
        return false;
    }
    auto& aJoint = static_cast<ExoskeletonJointActiveHandle &>(joint);
    if(disableTorque) {
        aJoint.setTorque(false);
    }
    float pPos = aJoint.getPresentPosition();
    return pPos < (-aJoint.getLowerRangeOfMotion() - EMERGENCY_SHUTDOWN_TOLERANCE_ANGLE)
       || pPos > (aJoint.getUpperRangeOfMotion() + EMERGENCY_SHUTDOWN_TOLERANCE_ANGLE);
}

ExoskeletonEmergencyBtnExecutable::ExoskeletonEmergencyBtnExecutable(ExoskeletonHandle &exo): exo(exo) {}

void ExoskeletonEmergencyBtnExecutable::exec() {
    if(digitalRead(btnPin) == HIGH) {
        return;
    }

    shutdownJoint(exo.getLeftArm().getElbow());
    shutdownJoint(exo.getLeftArm().getShoulderSide());
    shutdownJoint(exo.getLeftArm().getShoulderBack());
    shutdownJoint(exo.getRightArm().getElbow());
    shutdownJoint(exo.getRightArm().getShoulderSide());
    shutdownJoint(exo.getRightArm().getShoulderBack());

    DEBUG_SERIAL.println(F("!!! --> Emergency button pressed <-- !!!"));
    DEBUG_SERIAL.println(F("Performing emergency shutdown."));
    DEBUG_SERIAL.flush();
    exit(1);
}

void ExoskeletonEmergencyBtnExecutable::shutdownJoint(ExoskeletonJointHandle &joint) {
    if(joint.isActive()) {
        auto& aJoint = static_cast<ExoskeletonJointActiveHandle &>(joint);
        aJoint.setTorque(false);
    }
}

void ExoskeletonEmergencyBtnExecutable::configure(uint8_t btnPin, bool isPullUp) {
    this->btnPin = btnPin;
    if(isPullUp) {
        pinMode(btnPin, INPUT_PULLUP);
    } else {
        pinMode(btnPin, INPUT);
    }
}
