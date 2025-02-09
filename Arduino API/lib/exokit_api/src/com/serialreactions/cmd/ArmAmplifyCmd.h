#ifndef CHI25_EXOSKELETON_API_ARMAMPLIFYCMD_H
#define CHI25_EXOSKELETON_API_ARMAMPLIFYCMD_H


#include "com/ICmd.h"

class ArmAmplifyCmd: public ICmd {
public:
    String getUsage() override;

    /**
    * Parses the incoming string to decode and verify the function's parameters.
    * @return -1 if parsing was unsuccessful, 0 otherwise
    */
    int8_t execute(HardwareSerial &serial, String args) override;
};


#endif //CHI25_EXOSKELETON_API_ARMAMPLIFYCMD_H
