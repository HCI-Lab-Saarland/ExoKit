#include <EEPROM.h>
#include "ExoskeletonJointActiveHandle.h"
#include "util/UnitConversions.h"
#include "util/DebugSerial.h"
#include "ExoskeletonArmHandle.h"
#include "TaskManagerIO.h"

ExoskeletonJointActiveHandle::ExoskeletonJointActiveHandle(ArmSide side, JointType jointType, DynamixelShield &dxl, uint8_t dxl_id, HX711 *loadCell, int16_t lower_range_of_motion, int16_t upper_range_of_motion) :
        ExoskeletonJointHandle(side, jointType, lower_range_of_motion, upper_range_of_motion), dxl(dxl), loadCell(loadCell),
        goalPosition(0), dxl_id(dxl_id), zeroPositionDegree(0), operating_mode(OP_CURRENT_BASED_POSITION)
{
    // initialize motor with a dummy op mode;
    uint16_t model_number = dxl.getModelNumber(dxl_id);

    // set max_no_load_speed depending on model of the dynamixel (in rpm)
    switch (model_number)
    {
    case XM430_W210:
        eepromRangeTable = {
                {0,77},
                {0, 1193},
                0.229
        };
        break;
    case XM430_W350:
        eepromRangeTable = {
                {0,46},
                {0, 1193},
                0.229
            };
        break;
    case XM540_W150:
        eepromRangeTable = {
                {0,53},
                {0, 2047},
                0.229
        };
        break;
    case XM540_W270:
        eepromRangeTable = {
                {0,30},
                {0, 2047},
                0.229
        };
        break;
    default:
        // set a dummy minimum value
        eepromRangeTable = {
                {0,30},
                {0, 1193},
                0.229
        };
        break;
    }
    setTorque(false);
    setJointMode(operating_mode);
    setGoalPosition(0);
}

void ExoskeletonJointActiveHandle::setJointMode(OperatingMode mode) {
    // first ensure that torque is disabled before reconfiguring the mode;
    bool torque = getIsTorque();
    if (torque) {
        setTorque(false);
    }
    dxl.setOperatingMode(dxl_id, mode);
    this->operating_mode = mode;
    if(torque) {
        setTorque(torque);
    }
}

void ExoskeletonJointActiveHandle::setCurrentLimit(float percentage) {
    dxl.writeControlTableItem(ControlTableItem::CURRENT_LIMIT, dxl_id, int32_t(float(eepromRangeTable.current_limit.max) * percentage));
}

float ExoskeletonJointActiveHandle::getCurrentLimit() const  {
    return float(dxl.readControlTableItem(ControlTableItem::CURRENT_LIMIT, dxl_id)) / float(eepromRangeTable.current_limit.max);
}

void ExoskeletonJointActiveHandle::setGoalCurrent(float percentage) {
    dxl.writeControlTableItem(ControlTableItem::GOAL_CURRENT, dxl_id, int32_t(float(eepromRangeTable.current_limit.max) * getCurrentLimit() * percentage));
}

float ExoskeletonJointActiveHandle::getGoalCurrent() const
{
    return float(dxl.readControlTableItem(ControlTableItem::GOAL_CURRENT, dxl_id)) / getCurrentLimit();
}

float ExoskeletonJointActiveHandle::getProfileVelocity() {
    return rpm2degsec(float(dxl.readControlTableItem(ControlTableItem::PROFILE_VELOCITY, dxl_id)) * 0.229f);
}

void ExoskeletonJointActiveHandle::setProfileVelocity(float degPerSec) {
    int32_t velocity;
    if(degPerSec < 0.01) {
        velocity = 0;
    } else {
        velocity = int32_t(degsec2rpm(degPerSec) / 0.229f);
    }
    dxl.writeControlTableItem(ControlTableItem::PROFILE_VELOCITY, dxl_id, velocity);
}

void ExoskeletonJointActiveHandle::setProfileAcceleration(float degPerSecPerSec) {
    dxl.writeControlTableItem(ControlTableItem::PROFILE_ACCELERATION, dxl_id, 0);
}

OperatingMode ExoskeletonJointActiveHandle::getJointMode() const {
    return operating_mode;
}

void ExoskeletonJointActiveHandle::setGoalPosition(float angle) {
    if(angle < -lower_range_of_motion) {
        angle = -lower_range_of_motion;
    } else if (angle > upper_range_of_motion) {
        angle = upper_range_of_motion;
    }
    goalPosition = angle;
    float dxlPosition = (negateAngles() ? -1 : 1) * angle;
    dxl.setGoalPosition(dxl_id, zeroPositionDegree + dxlPosition, UNIT_DEGREE);
}

float ExoskeletonJointActiveHandle::getGoalPosition() const {
    return goalPosition;
}

float ExoskeletonJointActiveHandle::getPresentPosition() {
    return (negateAngles() ? -1 : 1) * (dxl.getPresentPosition(dxl_id, UNIT_DEGREE) - zeroPositionDegree);
}

void ExoskeletonJointActiveHandle::setTorque(bool enable) {
    isTorque = enable;
    if (enable) {
        dxl.torqueOn(dxl_id);
    } else {
        dxl.torqueOff(dxl_id);
    }
}

bool ExoskeletonJointActiveHandle::isGoalPositionReached(float toleranceAngle = 5) {
    float present = getPresentPosition();
    return abs(goalPosition - present) < abs(toleranceAngle);
}

bool ExoskeletonJointActiveHandle::hasLoadCell() {
    return loadCell != nullptr;
}

float ExoskeletonJointActiveHandle::readLoadCell() {
    if (hasLoadCell())
    {
        return loadCell->get_units(1);
    }
    return 0;
}

bool ExoskeletonJointActiveHandle::getIsTorque() {
    return isTorque;
}

float ExoskeletonJointActiveHandle::getMaxNoLoadSpeed() const {
    // convert from internally set rpm to deg/sec
    return rpm2degsec(float(eepromRangeTable.no_load_speed.max));
}

void ExoskeletonJointActiveHandle::printInfo() {
    DEBUG_SERIAL.print(F("Shield port prototcol version ref: "));
    DEBUG_SERIAL.println(dxl.getPortProtocolVersion());
    DEBUG_SERIAL.print(F("DXL ID: "));
    DEBUG_SERIAL.println(dxl_id);
    if (hasLoadCell()) {
        DEBUG_SERIAL.println(F("loadcell present."));
    } else {
        DEBUG_SERIAL.println(F("no loadcell present"));
    }
}

bool ExoskeletonJointActiveHandle::isActive() {
    return true;
}

bool ExoskeletonJointActiveHandle::canTrackPosition() {
    return true;
}

float ExoskeletonJointActiveHandle::getVelocity() {
    //Convert to degree per second.
    return (negateAngles() ? -1 : 1) * rpm2degsec(dxl.getPresentVelocity(dxl_id, UNIT_RPM));
}

void ExoskeletonJointActiveHandle::setGoalVelocity(float degsec) {
    // TODO: command might be different depending on the present op mode -> to be added as consideration
    // convert to rpm
    degsec = (negateAngles() ? -1 : 1) * degsec;
    dxl.setGoalVelocity(dxl_id,degsec2rpm(degsec), UNIT_RPM);
}

void ExoskeletonJointActiveHandle::tare(float currentAngle) {
    float presentPosRelativeAngle = dxl.getPresentPosition(dxl_id, UNIT_DEGREE);
    zeroPositionDegree = presentPosRelativeAngle;
    if(negateAngles()) {
        zeroPositionDegree += currentAngle;
    } else {
        zeroPositionDegree -= currentAngle;
    }
    setGoalPosition(goalPosition);
}

EepromId ExoskeletonJointActiveHandle::getEepromId() {
    return EXO_JOINT_ACTIVE;
}

int16_t ExoskeletonJointActiveHandle::loadConfigFromEEPROM(int16_t offset) {
    EepromId readId;
    EEPROM.get(offset, readId);
    offset += int16_t(sizeof(readId));
    if(readId != getEepromId()) {
        return -1;
    }
    EEPROM.get(offset, zeroPositionDegree);
    offset += int16_t(sizeof(zeroPositionDegree));
    return offset;
}

int16_t ExoskeletonJointActiveHandle::persistConfigToEEPROM(int16_t offset) {
    EEPROM.put(offset, getEepromId());
    offset += int16_t(sizeof(getEepromId()));
    EEPROM.put(offset, zeroPositionDegree);
    offset += int16_t(sizeof(goalPosition));
    return offset;
}

float ExoskeletonJointActiveHandle::getTrajectory() {
    int32_t posTraj = dxl.readControlTableItem(ControlTableItem::POSITION_TRAJECTORY, dxl_id);
   /* int32_t presPos = dxl.readControlTableItem(ControlTableItem::PRESENT_POSITION, dxl_id);
    DEBUG_SERIAL.print("ExoskeletonJointActive::getTrajectory(): PT ");
    DEBUG_SERIAL.print(posTraj);
    DEBUG_SERIAL.print(" / PP ");
    DEBUG_SERIAL.print(presPos);
    DEBUG_SERIAL.print(" / GP ");
    DEBUG_SERIAL.print(getPresentPosition());*/
    return (negateAngles() ? -1 : 1) * (float(posTraj) * 0.0878f - zeroPositionDegree);
}
