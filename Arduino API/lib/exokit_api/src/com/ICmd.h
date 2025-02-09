#ifndef CHI25_EXOSKELETON_API_ICMD_H
#define CHI25_EXOSKELETON_API_ICMD_H


#include <WString.h>
#include <HardwareSerial.h>

class ICmd {
public:
    virtual ~ICmd() = default;
    virtual String getIdentifier();
    virtual int8_t execute(HardwareSerial &serial, String args) = 0;
    virtual String getUsage() = 0;
};


#endif //CHI25_EXOSKELETON_API_ICMD_H
