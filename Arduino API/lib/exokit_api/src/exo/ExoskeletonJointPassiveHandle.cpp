#include <EEPROM.h>
#include "ExoskeletonJointPassiveHandle.h"
#include "util/DebugSerial.h"

ExoskeletonJointPassiveHandle::ExoskeletonJointPassiveHandle(ArmSide side, JointType jointType, ConfiguredEncoder *encoder, HX711 *loadCell, uint8_t lower_mechanical_restriction, uint8_t upper_mechanical_restriction) :
        ExoskeletonJointHandle(side, jointType, lower_mechanical_restriction, upper_mechanical_restriction), encoder(encoder), loadCell(loadCell) {}

float ExoskeletonJointPassiveHandle::getPresentPosition() {
    if(!hasEncoder()) {
        return 0;
    }
    return (negateAngles() ? -1 : 1) * encoder->readAngle();
}

bool ExoskeletonJointPassiveHandle::hasEncoder() {
    return encoder != nullptr;
}

bool ExoskeletonJointPassiveHandle::hasLoadCell() {
    return loadCell != nullptr;
}

float ExoskeletonJointPassiveHandle::readLoadCell() {
    if (hasLoadCell())
    {
        return loadCell->get_units(1);
    }
    return 0;
}

void ExoskeletonJointPassiveHandle::printInfo() {
    if (hasEncoder()) {
        DEBUG_SERIAL.println("encoder present.");
    } else {
        DEBUG_SERIAL.println("no encoder present");
    }
    if (hasLoadCell()) {
        DEBUG_SERIAL.println("loadcell present.");
    } else {
        DEBUG_SERIAL.println("no loadcell present");
    }
}

bool ExoskeletonJointPassiveHandle::isActive() {
    return false;
}

bool ExoskeletonJointPassiveHandle::canTrackPosition() {
    return hasEncoder();
}

float ExoskeletonJointPassiveHandle::getVelocity() {
    if (canTrackPosition()) {
        return (negateAngles() ? -1 : 1) * encoder->getVelocity();
    }
    return ExoskeletonJointHandle::getVelocity();
}

void ExoskeletonJointPassiveHandle::tare(float currentAngle) {
    if(hasEncoder()) {
        encoder->tare((negateAngles() ? -1 : 1) * currentAngle);
    }
}

EepromId ExoskeletonJointPassiveHandle::getEepromId() {
    return EXO_JOINT_PASSIVE;
}

int16_t ExoskeletonJointPassiveHandle::loadConfigFromEEPROM(int16_t offset) {
    EepromId readId;
    EEPROM.get(offset, readId);
    offset += int16_t(sizeof(readId));
    if(readId != getEepromId()) {
        return -1;
    }
    bool encoderPersisted;
    EEPROM.get(offset, encoderPersisted);
    offset += int16_t(sizeof(bool));
    if(encoderPersisted != hasEncoder()) {
        return -1;
    }
    if(hasEncoder()) {
        offset = encoder->loadConfigFromEEPROM(offset);
        if(offset < 0)
            return -1;
    }
    return offset;
}

int16_t ExoskeletonJointPassiveHandle::persistConfigToEEPROM(int16_t offset) {
    EEPROM.put(offset, getEepromId());
    offset += int16_t(sizeof(getEepromId()));
    if(hasEncoder()) {
        EEPROM.put(offset, true);
        offset += int16_t(sizeof(bool));
        offset = encoder->persistConfigToEEPROM(offset);
    } else {
        EEPROM.put(offset, false);
        offset += int16_t(sizeof(bool));
    }
    return offset;
}
