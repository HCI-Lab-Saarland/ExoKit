#ifndef CHI25_EXOSKELETON_API_EXOSKELETONCOMPONENT_H
#define CHI25_EXOSKELETON_API_EXOSKELETONCOMPONENT_H

#include <stdint.h>

enum JointType {
    NONE, SHOULDER_BACK, SHOULDER_SIDE, ELBOW
};

enum EepromId {
    EXO, EXO_ARM, EXO_JOINT_ACTIVE, EXO_JOINT_PASSIVE, CONFIGURED_ENCODER
};

class ExoskeletonComponentHandle {
protected:
    virtual EepromId getEepromId() = 0;
public:
    ~ExoskeletonComponentHandle() = default;

    virtual void printInfo() = 0;
    virtual int16_t loadConfigFromEEPROM(int16_t offset) = 0;
    virtual int16_t persistConfigToEEPROM(int16_t offset) = 0;
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONCOMPONENT_H
