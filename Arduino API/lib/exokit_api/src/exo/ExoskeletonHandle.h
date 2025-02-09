#ifndef EXOSKELETON_H
#define EXOSKELETON_H

#include "ExoskeletonComponent.h"
#include "ExoskeletonArmHandle.h"
#include "TaskTypes.h"

class ExoskeletonRomKillSwitchExecutable: public Executable {
private:
    ExoskeletonHandle& exo;
    const float EMERGENCY_SHUTDOWN_TOLERANCE_ANGLE = 10.f;

    /**
     * Recursively checks all joints in the given arm and disables torque if necessary.
     * @param arm The arm to check (LEFT or RIGHT).
     * @param disableTorque Whether to disable the torque in case of a problem.
     * @return True if one of the joints is out of bounds, false otherwise.
     */
    bool traverseArm(ExoskeletonArmHandle& arm, bool disableTorque);

    /**
     * Checks if the joint is out of bounds and disables torque if necessary.
     * @param joint The joint to check.
     * @param disableTorque Whether to disable the torque in case of a problem.
     * @return True if the joint was out of bounds.
     */
    bool checkJoint(ExoskeletonJointHandle& joint, bool disableTorque);
public:
    explicit ExoskeletonRomKillSwitchExecutable(ExoskeletonHandle& exo);
    void exec() override;
};

class ExoskeletonEmergencyBtnExecutable: public Executable {
private:
    ExoskeletonHandle& exo;
    uint8_t btnPin{};
public:
    ExoskeletonEmergencyBtnExecutable(ExoskeletonHandle& exo);
    void configure(uint8_t btnPin, bool isPullUp);

    /**
     * Executes the emergency shutdown check.
     * If emergency button is pressed, all joints are shut down.
     */
    void exec() override;

    /**
     * Executes the emergency shutdown for a joint, disabling the torque.
     * @param joint. The joint that is shut down.
     */
    void shutdownJoint(ExoskeletonJointHandle& joint);
};

class ExoskeletonHandle : public ExoskeletonComponentHandle {
    friend class ExoskeletonArmHandle;
    friend class ExoskeletonRomKillSwitchExecutable;

private:
    ExoskeletonArmHandle &leftArm;
    ExoskeletonArmHandle &rightArm;
    int8_t id{};
    bool isEnableRomKillSwitch{false};
    taskid_t romKillSwitchTaskId{};
    ExoskeletonRomKillSwitchExecutable romKillSwitchExecutable;
    taskid_t emergencyBtnTaskId{};
    ExoskeletonEmergencyBtnExecutable emergencyBtnExecutable;
    bool isEnableEmergencyBtn{false};

    void enableRomKillSwitch(bool enable);

protected:
    EepromId getEepromId() override;

public:

    /**
     * Constructs the exoskeleton handle with its left and right arm components.
     * @param left The ExoskeletonArmHandle of the left arm of the exoskeleton.
     * @param right The ExoskeletonArmHandle of the right arm of the exoskeleton.
     */
    ExoskeletonHandle(ExoskeletonArmHandle &left, ExoskeletonArmHandle &right);

    /**
     * Destructor of the exoskeleton handle.
     */
    ~ExoskeletonHandle();

     /**
     * Gets the left arm of the exoskeleton.
     * @return the ExoskeletonArmHandle of the left exoskeleton arm.
     */
    ExoskeletonArmHandle &getLeftArm();
        
     /**
     * Gets the right arm of the exoskeleton.
     * 
     * @return the ExoskeletonArmHandle of the right exoskeleton arm.
     */
    ExoskeletonArmHandle &getRightArm();

    /**
     * Prints detailed information about the exoskeleton.
     */
    void printInfo() override;

     /**
     * Loads configuration data from EEPROM.
     * 
     * @param offset The EEPROM memory address where data is stored.
     * @return The next available EEPROM address.
     */
    int16_t loadConfigFromEEPROM(int16_t offset) override;

     /**
     * Persists configuration data to EEPROM.
     * @param offset The EEPROM memory address where data should be stored.
     * @return The next available EEPROM address after storing data.
     */
    int16_t persistConfigToEEPROM(int16_t offset) override;

     /**
     * Enables or disables the emergency button monitoring system.
     * 
     * @param buttonPin The pin where the emergency button is connected.
     * @param isPullUp If true, enables the pull-up resistor.
     */       
    void enableEmergencyBtn(uint8_t buttonPin, bool isPullUp);

     /**
     * Sets the unique ID for this exoskeleton unit.
     * @param i The ID to assign.
     */
    void setId(int8_t i);

     /**
     * Gets the unique ID of this exoskeleton.
     * @return The exoskeleton's ID.
     */
    int8_t getId();
};


#endif //EXOSKELETON_H
