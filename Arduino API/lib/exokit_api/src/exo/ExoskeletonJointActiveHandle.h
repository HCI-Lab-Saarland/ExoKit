#ifndef CHI25_EXOSKELETON_API_EXOSKELETONJOINTACTIVEHANDLE_H
#define CHI25_EXOSKELETON_API_EXOSKELETONJOINTACTIVEHANDLE_H


#include "ExoskeletonJointHandle.h"
#include "DynamixelShield.h"
#include "HX711.h"
#include "TaskTypes.h"
#include "event/reaction/IReaction.h"

class ExoskeletonJointActiveHandle;

class ExoskeletonJointActiveHandle : public ExoskeletonJointHandle {
    friend class ExoskeletonArmHandle;

public:
    struct dxl_eeprom_range_item {
        int32_t min;
        int32_t max;
    };
    struct dxl_eeprom_range_table {
        dxl_eeprom_range_item no_load_speed;
        dxl_eeprom_range_item current_limit;
        float rpm_per_velocity_unit;
    };

private:
    DynamixelShield &dxl;
    HX711 *loadCell;
    float goalPosition;
    uint8_t dxl_id;
    float zeroPositionDegree;
    bool isTorque;
    OperatingMode operating_mode{OP_CURRENT_BASED_POSITION};

    // all of the supported dynamixels have a different no load speed
    // this must be known for several functionalities that manipulate the motor's velocity
    dxl_eeprom_range_table eepromRangeTable;

protected:
    EepromId getEepromId() override;

public:
    ExoskeletonJointActiveHandle(ArmSide side, JointType jointType, DynamixelShield &dxl, uint8_t dxl_id, HX711 *loadCell = nullptr, int16_t lower_range_of_motion = 0, int16_t upper_range_of_motion = 0);
    ~ExoskeletonJointActiveHandle() = default;

     /**
     * Sets the joint motor's operating mode. 
     * 
     * @param operating_mode The operating mode of the Dynamixel motor.
     */
    void setJointMode(OperatingMode operating_mode);

     /**
     * Gets the joint motor's operating mode. 
     * @return operating_mode The operating mode of the Dynamixel motor.
     */
    OperatingMode getJointMode() const;

     /**
     * Sets the joint goal position to which it shall move. If the goal position 
     * is outside of the configured range of motion, the goal position is set to the configured limit.
     * @param angle the goal position in degree.
     */
    void setGoalPosition(float angle);
    
    /**
     * Gets the joint goal position to which it shall move. 
     * @return The goal position in degree.
     */
    float getGoalPosition() const;

    /**
     * Gets the joint trajectory. 
     * @return The trajectory.
     */
    float getTrajectory();

    /**
     * Indicated if the joint can track position 
     * @return True if there is an encoder or motor, false otherwise
     */
    bool canTrackPosition() override;

    /**
     * Gets the joint velocity. 
     * @return The current velocity in degrees per second.
     */
    float getVelocity() override;

    /**
     * Sets the joint velocity. 
     * @param The target velocity in degrees per second.
     */
    void setGoalVelocity(float velocity); 
     
    /**
     * Gets the joint's current position. 
     * @return The current position.
     */
    float getPresentPosition() override;

    /**
     * Sets the joint torque. 
     * @param enable. If true, enable the torque, if false disable the torque.
     */
    void setTorque(bool enable);

    /**
     * Sets the joint torque. 
     * @return True if torque is enabled, false otherwise.
     */
    bool getIsTorque();

    /**
     * Sets the motor's goal current. 
     * @param percentage. The current in percentage, depends on the current available in the motor.
     */
    void setGoalCurrent(float percentage);

    /**
     * Gets the goal current. 
     * @return goal current.
     */
    float getGoalCurrent() const;

    /**
     * Calibrates the zero position of the joint.
     * @param currentAngle The current joint angle that should be set as the zero position.
     */
    void tare(float currentAngle) override;

    /**
     * Indicates if the goal position is reached.
     * @param toleranceAngle. If the joint is closer than toleranceAngle to the goal position, the function turns true. 
     * @return True if the joint is within the defined area, false otherwise.
     */
    bool isGoalPositionReached(float toleranceAngle);

    /**
     * Indicates if the joint has a load cell assigned.
     * @return True if the joint has a load cell, false otherwise.
     */
    bool hasLoadCell() override;

    /**
     * Gets the current load cell measurement.
     * @return the load cell measurement
     */
    float readLoadCell() override;

    /**
     * Gets the motor's max no load speed. Specific to the motor. 
     * @return the max no load speed of the motor in deg/sec
     */
    float getMaxNoLoadSpeed() const; 

     /**
     * Prints information about this component.
     */
    void printInfo() override;

    /**
     * Loads configuration data from EEPROM.
     * @param offset The EEPROM address where the data is stored.
     * @return The next available EEPROM address.
     */
    int16_t loadConfigFromEEPROM(int16_t offset) override;

    /**
     * Persists configuration data to EEPROM.
     * @param offset The EEPROM address where the data should be stored.
     * @return The next available EEPROM address after storing data.
     */
    int16_t persistConfigToEEPROM(int16_t offset) override;

    /**
     * Indicates if the joint is active or passive.
     * @return True if the joint is active, false otherwise.
     */
    bool isActive() override;

    /**
     * Sets the motor's velocity profile in the ControlTableItem.
     * @param degPerSec. Velocity profile in deg/sec
     */
    void setProfileVelocity(float degPerSec);

    /**
     * Gets the profile velocity from the ControlTableItem. 
     * @return the profile velocity
     */
    float getProfileVelocity();

    /**
     * Gets the motor's current limit from the ControlTableItem. 
     * @return the set current limit
     */
    float getCurrentLimit() const;

    /**
     * Sets the motor's current limit. 
     * @param percentage. The percentage of the limit of available current. 
     */
    void setCurrentLimit(float percentage);

    /**
     * Sets the motor's acceleration profile in the ControlTableItem.. 
     * @param degPerSecPerSec. acceleration profile in deg/sec^2
     */
    void setProfileAcceleration(float degPerSecPerSec);
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONJOINTACTIVEHANDLE_H
