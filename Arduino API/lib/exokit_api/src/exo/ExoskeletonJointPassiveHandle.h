#ifndef CHI25_EXOSKELETON_API_EXOSKELETONJOINTPASSIVEHANDLE_H
#define CHI25_EXOSKELETON_API_EXOSKELETONJOINTPASSIVEHANDLE_H


#include "ExoskeletonJointHandle.h"
#include "ConfiguredEncoder.h"
#include "HX711.h"

class ExoskeletonJointPassiveHandle : public ExoskeletonJointHandle {
private:
    ConfiguredEncoder *encoder;
    HX711 *loadCell;

protected:
    EepromId getEepromId() override;

public:
    explicit ExoskeletonJointPassiveHandle(ArmSide armSide, JointType jointType, ConfiguredEncoder *encoder = nullptr, HX711 *loadcell = nullptr, uint8_t lower_mechanical_restriction = 0, uint8_t upper_mechanical_restriction = 0);

    /**
     * Indicates if the joint has an encoder assigned.
     * @return True if the joint has an encoder, false otherwise.
     */
    bool hasEncoder();

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
     * Calibrates the zero position of the joint.
     * @param currentAngle The current joint angle that should be set as the zero position.
     */
    void tare(float currentAngle) override;

     /**
     * Prints information about this component.
     */
    void printInfo() override;

    /**
     * Indicates if the joint is active or passive.
     * @return True if the joint is active, false otherwise.
     */
    bool isActive() override;

    /**
     * Gets the joint velocity. 
     * @return The current velocity in degrees per second.
     */
    float getVelocity() override;

    /**
     * Indicated if the joint can track position 
     * @return True if there is an encoder or motor, false otherwise
     */
    bool canTrackPosition() override;

    /**
     * Gets the joint's current position. 
     * @return The current position.
     */
    float getPresentPosition() override;

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
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONJOINTPASSIVEHANDLE_H
