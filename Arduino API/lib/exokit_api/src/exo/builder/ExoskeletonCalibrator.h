#ifndef CHI25_EXOSKELETON_API_EXOSKELETONCALIBRATOR_H
#define CHI25_EXOSKELETON_API_EXOSKELETONCALIBRATOR_H


#include "exo/ExoskeletonHandle.h"

enum ConfigLoadBehaviour {
    ASK_CREATE, PREFER_LOAD, CREATE
};

class ExoskeletonCalibrator {
private:
    ExoskeletonHandle& exoskeleton;

private:
    int16_t applyConfigFromEEPROM();
    int16_t storeConfigInEEPROM();

public:
    explicit ExoskeletonCalibrator(ExoskeletonHandle& exo);

    /**
     * Starts to calibrate the exoskeleton. Sends output and accepts inputs from DEBUG_SERIAL.
     * @param configLoadBehaviour ASK_CREATE (Asks the user if he wants to re-calibrate his exoskeleton), PREFER_LOAD (Automatically loads the persists configuration if available.), CREATE (Always recalibrates the exoskeleton.)
     * @return An ExoskeletonHandle instance that can be used with an Exoskeleton object in combination with an ActionBuilder.
     */
    ExoskeletonHandle& calibrate(ConfigLoadBehaviour configLoadBehaviour = ASK_CREATE);

    /**
     * Returns true, if a persisted configuration is available.
     * @return
     */
    bool isPersistedConfigAvailable();
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONCALIBRATOR_H
