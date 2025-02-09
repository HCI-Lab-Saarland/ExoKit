#include <EEPROM.h>
#include "ExoskeletonArmHandle.h"
#include "util/DebugSerial.h"

ExoskeletonArmHandle::ExoskeletonArmHandle(ExoskeletonJointHandle &shoulderBack, ExoskeletonJointHandle &shoulderSide,
                                           ExoskeletonJointHandle &elbow, ArmSide side) :
        shoulderBack(&shoulderBack), shoulderSide(&shoulderSide), elbow(&elbow), side(side) {
    shoulderBack.setExoskeletonArm(*this);
    shoulderSide.setExoskeletonArm(*this);
    elbow.setExoskeletonArm(*this);
}

void ExoskeletonArmHandle::setExoskeleton(ExoskeletonHandle &exo) {
    this->exoskeleton = &exo;
}

ExoskeletonJointHandle &ExoskeletonArmHandle::getShoulderBack() {
    return *shoulderBack;
}

ExoskeletonJointHandle &ExoskeletonArmHandle::getShoulderSide() {
    return *shoulderSide;
}

ExoskeletonJointHandle &ExoskeletonArmHandle::getElbow() {
    return *elbow;
}

ArmSide ExoskeletonArmHandle::getSide() {
    return side;
}

void ExoskeletonArmHandle::setDistanceBack2Shoulder(uint8_t distance) {
    dist_back_to_shoulder = distance;
}

void ExoskeletonArmHandle::setDistanceShoulder2Elbow(uint8_t distance) {
    dist_shoulder_to_elbow = distance;
}

void ExoskeletonArmHandle::setDistanceElbow2Hand(uint8_t distance) {
    dist_elbow_hand = distance;
}

void ExoskeletonArmHandle::printInfo() {
    if (side == LEFT) {
        DEBUG_SERIAL.println(F("LEFT side"));
    } else if (side == RIGHT) {
        DEBUG_SERIAL.println(F("RIGHT side"));
    }
    DEBUG_SERIAL.print(F("Elbow: "));
    if (elbow->isActive()) {
        DEBUG_SERIAL.println(F("elbow is active"));
    } else {
        DEBUG_SERIAL.println(F("elbow is passive"));
    }
    elbow->printInfo();

    DEBUG_SERIAL.println();
    DEBUG_SERIAL.print(F("Shoulder side: "));
    if (shoulderSide->isActive()) {
        DEBUG_SERIAL.println(F("shoulder side is active"));
    } else {
        DEBUG_SERIAL.println(F("shoulder side is passive"));
    }
    shoulderSide->printInfo();

    DEBUG_SERIAL.println();
    DEBUG_SERIAL.print(F("Shoulder back: "));
    if (shoulderBack->isActive()) {
        DEBUG_SERIAL.println(F("shoulder back is active"));
    } else {
        DEBUG_SERIAL.println(F("shoulder back is passive"));
    }
    shoulderBack->printInfo();
}

ExoArmAngles ExoskeletonArmHandle::getAngles() {
    ExoArmAngles pos;
    if (shoulderBack->canTrackPosition()) {
        pos.setShoulderBackAngle(shoulderBack->getPresentPosition());
    }
    if (shoulderSide->canTrackPosition()) {
        pos.setShoulderSideAngle(shoulderSide->getPresentPosition());
    }
    if (elbow->canTrackPosition()) {
        pos.setElbowAngle(elbow->getPresentPosition());
    }
    return pos;
}

ExoskeletonHandle &ExoskeletonArmHandle::getExoskeleton() {
    return *exoskeleton;
}

EepromId ExoskeletonArmHandle::getEepromId() {
    return EXO_ARM;
}

int16_t ExoskeletonArmHandle::loadConfigFromEEPROM(int16_t offset) {
    EepromId readID;
    EEPROM.get(offset, readID);
    if(readID != getEepromId()) {
        return -1;
    }
    offset += int16_t(sizeof(readID));
    EEPROM.get(offset, dist_back_to_shoulder);
    offset += int16_t(sizeof(dist_back_to_shoulder));
    EEPROM.get(offset, dist_shoulder_to_elbow);
    offset += int16_t(sizeof(dist_shoulder_to_elbow));
    EEPROM.get(offset, dist_elbow_hand);
    offset += int16_t(sizeof(dist_elbow_hand));

    offset = shoulderBack->loadConfigFromEEPROM(offset);
    if(offset < 0)
        return -1;
    offset = shoulderSide->loadConfigFromEEPROM(offset);
    if(offset < 0)
        return -1;
    offset = elbow->loadConfigFromEEPROM(offset);
    if(offset < 0)
        return -1;
    return offset;
}

int16_t ExoskeletonArmHandle::persistConfigToEEPROM(int16_t offset) {
    EEPROM.put(offset, getEepromId());
    offset +=  int16_t(sizeof(getEepromId()));
    EEPROM.put(offset, dist_back_to_shoulder);
    offset += int16_t(sizeof(dist_back_to_shoulder));
    EEPROM.put(offset, dist_shoulder_to_elbow);
    offset += int16_t(sizeof(dist_shoulder_to_elbow));
    EEPROM.put(offset, dist_elbow_hand);
    offset += int16_t(sizeof(dist_elbow_hand));

    offset = shoulderBack->persistConfigToEEPROM(offset);
    offset = shoulderSide->persistConfigToEEPROM(offset);
    offset = elbow->persistConfigToEEPROM(offset);

    return offset;
}
