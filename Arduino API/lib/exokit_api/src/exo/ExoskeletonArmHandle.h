#ifndef CHI25_EXOSKELETON_API_EXOSKELETONARMHANDLE_H
#define CHI25_EXOSKELETON_API_EXOSKELETONARMHANDLE_H


#include "ExoskeletonComponent.h"
#include "ExoskeletonJointHandle.h"
#include "model/ExoArmAngles.h"
#include "ExoskeletonConstants.h"

class ExoskeletonHandle;


class ExoskeletonArmHandle : public ExoskeletonComponentHandle {
    friend class ExoskeletonHandle;

private:
    ExoskeletonJointHandle *shoulderBack;
    ExoskeletonJointHandle *shoulderSide;
    ExoskeletonJointHandle *elbow;
    ExoskeletonHandle *exoskeleton{};
    ArmSide side;
    uint16_t dist_back_to_shoulder{};
    uint16_t dist_shoulder_to_elbow{};
    uint16_t dist_elbow_hand{};

    void setExoskeleton(ExoskeletonHandle &exoskeleton);

protected:
    EepromId getEepromId() override;

public:
    /**
     * Constructs an ExoskeletonArmHandle with three joint handles.
     * 
     * @param shoulderBack The joint handle responsible for the shoulder back joint.
     * @param shoulderSide The joint handle responsible for the shoulder side joint.
     * @param elbow The joint handle responsible for the elbow joint.
     * @param side Specifies if this arm is the left or right side (LEFT or RIGHT).
     */
    ExoskeletonArmHandle(ExoskeletonJointHandle &shoulderBack, ExoskeletonJointHandle &shoulderSide, ExoskeletonJointHandle &elbow,
                         ArmSide side);

    /**
     * Gets the shoulder back/shoulder side/elbow joint handle.
     * @return The shoulder back/shoulder side/elbow joint handle.
     */
    ExoskeletonJointHandle &getShoulderBack();
    ExoskeletonJointHandle &getShoulderSide();
    ExoskeletonJointHandle &getElbow();

    /**
     * Gets the full exoskeleton handle.
     * @return The exoskeleton handle.
     */
    ExoskeletonHandle &getExoskeleton();

    /**
     * Gets the current angles of the arm's joints.
     * @return An `ExoArmAngles` object containing the joint angles.
     */
    ExoArmAngles getAngles();

    /**
     * Gets which side this arm belongs to.
     * @return The `ArmSide` enum value representing the arm's side (LEFT OR RIGHT).
     */
    ArmSide getSide();

    /**
     * Sets the distance from the back to the shoulder back joint.
     * @param distance.
     */
    void setDistanceBack2Shoulder(uint8_t distance);

    /**
     * Sets the distance from the shoulder side joint to the elbow joint.
     * @param distance.
     */
    void setDistanceShoulder2Elbow(uint8_t distance);

    /**
     * Sets the distance from the elbow joint to the hand.
     * @param distance.
     */
    void setDistanceElbow2Hand(uint8_t distance);

    /**
     * Prints information about this arm component.
     */
    void printInfo() override;
    
     /**
     * Loads stored configuration data from EEPROM.
     * @param offset The EEPROM address where the data is stored.
     * @return The next EEPROM address.
     */
    int16_t loadConfigFromEEPROM(int16_t offset) override;

     /**
     * Persists arm configuration data to EEPROM.
     * @param offset The EEPROM address where the data should be stored.
     * @return The next available EEPROM address after storing data.
     */
    int16_t persistConfigToEEPROM(int16_t offset) override;
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONARMHANDLE_H
