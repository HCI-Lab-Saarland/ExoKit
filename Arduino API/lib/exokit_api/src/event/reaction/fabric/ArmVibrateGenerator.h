#ifndef ARMVIBRATEGENERATOR_H
#define ARMVIBRATEGENERATOR_H
#include <event/concept/GesturesNotifications/VibrationTest.h>
#include <event/reaction/ComposedReaction.h>
#include <event/reaction/ParallelReaction.h>
#include <exo/ExoskeletonArmHandle.h>

#include "../../../../../../../../.platformio/packages/toolchain-atmelavr/avr/include/stdint.h"

class ArmVibrateGenerator {
private:
    uint8_t c_frequency;
    float c_amplitude;

    VibrationTest* generatedReactions[3]={};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ComposedReaction* composedReaction{};
    ExoskeletonJointHandle* joints[3] = {};
    uint8_t jointCount{};
    ExoskeletonArmHandle* arm{};
public:
    virtual ~ArmVibrateGenerator();
    ComposedReaction &init(ExoskeletonArmHandle &exoArm);
    void configure(uint8_t frequency, float amplitude);
    void reset();

};

#endif //ARMVIBRATEGENERATOR_H
