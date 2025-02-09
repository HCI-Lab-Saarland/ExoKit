#ifndef CHI25_EXOSKELETON_API_JOINTGUIDETOWARDSCMD_H
#define CHI25_EXOSKELETON_API_JOINTGUIDETOWARDSCMD_H


#include "com/ICmd.h"

class JointGuideTowardsCmd: public ICmd {
public:
    /**
    * Parses the incoming string to decode and verify the function's parameters. Launches the reaction.
    * @return -1 if parsing was unsuccessful, 0 otherwise
    */
    int8_t execute(HardwareSerial &serial, String args) override;
    String getUsage() override;
};


#endif //CHI25_EXOSKELETON_API_JOINTGUIDETOWARDSCMD_H
