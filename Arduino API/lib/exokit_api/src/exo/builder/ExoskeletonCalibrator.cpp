#include "ExoskeletonCalibrator.h"

#include <exo/ExoskeletonJointActiveHandle.h>

#include "EEPROM.h"
#include "util/DebugSerial.h"
#include "util/EepromCrc.h"

ExoskeletonCalibrator::ExoskeletonCalibrator(ExoskeletonHandle &exo):
    exoskeleton(exo)
{

    if (exoskeleton.getLeftArm().getShoulderSide().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getLeftArm().getShoulderSide())).setTorque(false);
    }
    if (exoskeleton.getLeftArm().getShoulderBack().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getLeftArm().getShoulderBack())).setTorque(false);
    }
    if (exoskeleton.getLeftArm().getElbow().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getLeftArm().getElbow())).setTorque(false);
    }

    if (exoskeleton.getRightArm().getShoulderSide().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getRightArm().getShoulderSide())).setTorque(false);
    }
    if (exoskeleton.getRightArm().getShoulderBack().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getRightArm().getShoulderBack())).setTorque(false);
    }
    if (exoskeleton.getRightArm().getElbow().isActive()) {
        (static_cast<ExoskeletonJointActiveHandle &> (exoskeleton.getRightArm().getElbow())).setTorque(false);
    }

}

ExoskeletonHandle &ExoskeletonCalibrator::calibrate(ConfigLoadBehaviour configLoadBehaviour) {
    bool preferEepromConfig = configLoadBehaviour == PREFER_LOAD;
    if(configLoadBehaviour == ASK_CREATE && isPersistedConfigAvailable()) {
        DEBUG_SERIAL.println(F("Persisted calibration available!"));
        DEBUG_SERIAL.println(F("Do you want to load and apply it? [y/n]"));
        bool valid = false;
        while(!valid) {
            while(DEBUG_SERIAL.available() == 0);
            char go = DEBUG_SERIAL.read();
            if(go == 'n' || go == 'y') {
                valid = true;
                preferEepromConfig = (go == 'y');
            }
        }
    }

    if(preferEepromConfig) {
        if(isPersistedConfigAvailable()) {
            if(applyConfigFromEEPROM() < 0) {
                DEBUG_SERIAL.println(F("Persisted calibration not valid for current exoskeleton!"));
            } else {
                DEBUG_SERIAL.println(F("Applyconfig succeded!"));
                return exoskeleton;
            }
        } else {
            DEBUG_SERIAL.println(F("No calibration persisted!"));
        }
    }

    // DO CALIBRATION FOR ALL ACTIVE JOINTS
    DEBUG_SERIAL.println(F("Exoskeleton must be calibrated!"));
    DEBUG_SERIAL.println(F("ExoKit will guide you through this process"));

    if (exoskeleton.getLeftArm().getElbow().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at left elbow."));
        DEBUG_SERIAL.println(F("Move your left elbow to the maximum possible extension. Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getLeftArm().getElbow().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }

    if (exoskeleton.getLeftArm().getShoulderBack().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at the back of the left shoulder."));
        DEBUG_SERIAL.println(F("Move your left shoulder as close to towards your body as close as possible (maximum shoulder adduction)."));
        DEBUG_SERIAL.println(F("Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getLeftArm().getShoulderBack().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }


    if (exoskeleton.getLeftArm().getShoulderSide().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at the side of the left shoulder."));
        DEBUG_SERIAL.println(F("Move your left shoulder as much back as possible (maximum shoulder extension)."));
        DEBUG_SERIAL.println(F("Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getLeftArm().getShoulderSide().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }


    if (exoskeleton.getRightArm().getElbow().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at right elbow."));
        DEBUG_SERIAL.println(F("Move your right elbow to the maximum possible extension. Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getRightArm().getElbow().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }

    if (exoskeleton.getRightArm().getShoulderBack().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at the back of the right shoulder."));
        DEBUG_SERIAL.println(F("Move your right shoulder as close to towards your body as close as possible (maximum shoulder adduction)."));
        DEBUG_SERIAL.println(F("Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getRightArm().getShoulderBack().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }


    if (exoskeleton.getRightArm().getShoulderSide().canTrackPosition()) {
        DEBUG_SERIAL.println(F("Calibrating motor at the side of the right shoulder."));
        DEBUG_SERIAL.println(F("Move your right shoulder as much back as possible (maximum shoulder extension)."));
        DEBUG_SERIAL.println(F("Then confirm with 'y'"));
        char go = 'n';
        while(go != 'y')
        {
            while(DEBUG_SERIAL.available() == 0); // Do nothing until there is data to read
            go = DEBUG_SERIAL.read();
        }
        exoskeleton.getRightArm().getShoulderSide().tare();
        DEBUG_SERIAL.println(F("Angle successfully calibrated."));
    }

    if(configLoadBehaviour != CREATE) {
        DEBUG_SERIAL.println(F("Do you want to persist your current calibration? [y/n]"));
        bool valid = false;
        while(!valid) {
            while(DEBUG_SERIAL.available() == 0);
            char go = DEBUG_SERIAL.read();
            if(go == 'n' || go == 'y') {
                valid = true;
            }
            if(go == 'y') {
                storeConfigInEEPROM();
            }
        }
    }

    return exoskeleton;
}

int16_t ExoskeletonCalibrator::storeConfigInEEPROM() {
    EEPROM.put(0, true);

    int16_t offset = sizeof(true) + sizeof(int16_t); //add configsize to offset
    int16_t sizeCrcVal =  (int16_t) sizeof(unsigned long);
    int16_t configSize = exoskeleton.persistConfigToEEPROM(offset) + sizeCrcVal;
    EEPROM.put(sizeof(true), configSize);

    //write crc after configSize
    unsigned long crcVal = eeprom_crc(0, configSize - sizeCrcVal);
    EEPROM.put(configSize - sizeCrcVal, crcVal);
    return configSize;
}

int16_t ExoskeletonCalibrator::applyConfigFromEEPROM() {
    if(!isPersistedConfigAvailable()) {
        return -1;
    }
    return exoskeleton.loadConfigFromEEPROM(sizeof(true) + sizeof(int16_t));
}

bool ExoskeletonCalibrator::isPersistedConfigAvailable() {
    int16_t configSize;
    EEPROM.get(sizeof(true), configSize);

    Serial.println(configSize);

    unsigned long storedCrc;
    int16_t sizeCrcVal =  (int16_t) sizeof(unsigned long);
    EEPROM.get(configSize - sizeCrcVal, storedCrc);
    unsigned long crcVal = eeprom_crc(0, configSize - sizeCrcVal);
    if(storedCrc == crcVal) {
        bool isAvailable;
        EEPROM.get(0, isAvailable);
        return isAvailable;
    }
    DEBUG_SERIAL.println(F("CRC mismatch!"));
    DEBUG_SERIAL.println(F("Stored/Computed: "));
    DEBUG_SERIAL.print(storedCrc);
    DEBUG_SERIAL.print(F("/"));
    DEBUG_SERIAL.print(crcVal);
    return false;
}
