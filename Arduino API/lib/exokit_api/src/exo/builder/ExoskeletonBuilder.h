#ifndef EXOSKELETONBUILDER_H
#define EXOSKELETONBUILDER_H

#include "exo/ExoskeletonHandle.h"
#include "ArmBuilder.h"
#include "ExoskeletonCalibrator.h"

class ArmBuilder;

class ExoskeletonBuilder
{
private:
    ArmBuilder* lArm = nullptr;
    ArmBuilder* rArm = nullptr;
    bool isEmergencyBtn{false};
    uint8_t emergencyBtnPin{};
    bool emergencyBtnPullUp = false;
    void reset();
public:
    /**
     * Creates a new ExoskeletonBuilder instance that can be used to configure the exoskeleton.
     */
    ExoskeletonBuilder() = default;
  
    /**
     * Applies the created configuration and returns an ExoskeletonCalibrator
     * @return
     */
    ExoskeletonCalibrator build();
  
    /**
     * Adds and starts the configuration of the left arm.
     * @return An ArmBuilder instance
     */
    ArmBuilder& addLeftArm();
  
    /**
     * Adds and starts the configuration of the right arm.
     * @return An ArmBuilder instance
     */
    ArmBuilder& addRightArm();
  
    /**
     * Adds an emergency shutdown button to the exoskeleton.
     * @param buttonPin GPIO-Pin number that the button is connected to.
     * @param isPullUp True if the pullUp should be enabled.
     * @return The current ExoskeletonBuilder instance.
     */
    ExoskeletonBuilder& addEmergencyShutdownButton(uint8_t buttonPin, bool isPullUp);
};

#endif //EXOSKELETONBUILDER_H

