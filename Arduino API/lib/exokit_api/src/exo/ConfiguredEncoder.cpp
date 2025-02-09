#include "ConfiguredEncoder.h"
#include "ExoskeletonHandle.h"
#include <TaskManagerIO.h>
#include <EEPROM.h>

ConfiguredEncoder::ConfiguredEncoder(int analogPotiPin, int potiMaxRoM) :
        potiPin(analogPotiPin), potiMaxRoM(potiMaxRoM), zeroPos(0), executable(*this), velocityReferencePositionIdx(0) {
    enableVelocityTracking(true);
}

float ConfiguredEncoder::readAngle() {
    return convertRawToAngle(readRaw()) - zeroPos;
}

float ConfiguredEncoder::convertRawToAngle(int raw) const {
    return (raw / 1023.f) * potiMaxRoM;
}

void ConfiguredEncoder::tare(float currentAngleRelativeZero) {
    float newZeroPos = convertRawToAngle(readRaw()) - currentAngleRelativeZero;
    if (isVelocityTracking) {
        float tareDiff = newZeroPos - zeroPos;
        velocityPrevPosition[0] += tareDiff;
        velocityPrevPosition[1] += tareDiff;
    }
    zeroPos = newZeroPos;
}

int ConfiguredEncoder::readRaw() {
    return analogRead(potiPin);
}

void ConfiguredEncoder::enableVelocityTracking(bool isEnable) {
    if (isEnable == isVelocityTracking) {
        return;
    }
    if (isEnable) {
        //delay(maxVelocityReferenceAgeMs);
        sampleVelocityReference();
        velocityTrackingTaskId = taskManager.scheduleFixedRate(maxVelocityReferenceAgeMs / 4, &executable, TIME_MILLIS);
    } else {
        taskManager.cancelTask(velocityTrackingTaskId);
    }
    isVelocityTracking = isEnable;
}

float ConfiguredEncoder::getVelocity() {
    if(velocityPrevPositionTimestamp[velocityReferencePositionIdx] == 0) {
        return 0.f;
    }
    float currentPos = readAngle();
    float movement = currentPos - velocityPrevPosition[velocityReferencePositionIdx];
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - velocityPrevPositionTimestamp[velocityReferencePositionIdx];
    if (elapsedTime > maxVelocityReferenceAgeMs) {
        return 0.f;
    }
    //Convert into degree per second.
    float result = movement / (float(elapsedTime) / 1000);
    if(isinf(result) || isnan(result)) {
        return 0.f;
    }
    return result;
}

void ConfiguredEncoder::sampleVelocityReference() {
    size_t otherRefIdx = (velocityReferencePositionIdx + 1) % 2;
    unsigned long currentTime = millis();
    unsigned long timeElapsed = currentTime - velocityPrevPositionTimestamp[velocityReferencePositionIdx];
    unsigned long otherTimeElapsed = currentTime - velocityPrevPositionTimestamp[otherRefIdx];

    if (timeElapsed == 0) {
        return;
    }

    //take one datapoint every maxVelocityReferenceAgeMs / 2 ms. Note that the "other" datapoint is already active
    //since maxVelocityReferenceAgeMs / 4 ms.
    if (otherTimeElapsed >= (maxVelocityReferenceAgeMs / 2)) {
        velocityPrevPositionTimestamp[otherRefIdx] = currentTime;
        velocityPrevPosition[otherRefIdx] = readAngle();
        otherTimeElapsed = currentTime - velocityPrevPositionTimestamp[otherRefIdx];
    }

    //after datapoint is at least maxVelocityReferenceAgeMs / 2 ms old, activate it as reference
    if (otherTimeElapsed >= (maxVelocityReferenceAgeMs / 4)) {
        velocityReferencePositionIdx = otherRefIdx;
    }
}

ConfiguredEncoder::~ConfiguredEncoder() {
    enableVelocityTracking(false);
}

int16_t ConfiguredEncoder::loadConfigFromEEPROM(int16_t offset) {
    EepromId readId;
    EEPROM.get(offset, readId);
    offset += int16_t(sizeof(readId));
    if(readId != CONFIGURED_ENCODER) {
        return -1;
    }
    EEPROM.get(offset, zeroPos);
    offset += int16_t(sizeof(zeroPos));
    return offset;
}

int16_t ConfiguredEncoder::persistConfigToEEPROM(int16_t offset) {
    EEPROM.put(offset, CONFIGURED_ENCODER);
    offset += int16_t(sizeof(CONFIGURED_ENCODER));
    EEPROM.put(offset, zeroPos);
    offset += int16_t(sizeof(zeroPos));
    return offset;
}

ConfiguredEncoderVelocitySampleExecutable::ConfiguredEncoderVelocitySampleExecutable(ConfiguredEncoder &encoder) :
        encoder(encoder) {}

void ConfiguredEncoderVelocitySampleExecutable::exec() {
    encoder.sampleVelocityReference();
}
