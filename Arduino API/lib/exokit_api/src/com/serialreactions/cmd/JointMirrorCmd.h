#ifndef CHI25_EXOSKELETON_API_JOINTMIRRORCMD_H
#define CHI25_EXOSKELETON_API_JOINTMIRRORCMD_H


#include "com/ICmd.h"
#include "exo/MovementScaler.h"

class JointMirrorCmd: public ICmd {
    MovementScaler scaler;
public:
    
    /**
    * Parses the incoming string to decode and verify the function's parameters. Launches the reaction.
    * @return -1 if parsing was unsuccessful, 0 otherwise
    */
    int8_t execute(HardwareSerial &serial, String args) override;
    String getUsage() override;
};


#endif //CHI25_EXOSKELETON_API_JOINTMIRRORCMD_H
