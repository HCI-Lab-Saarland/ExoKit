
#include <event/concept/ArmReactionGeneratorWrapper.h>

#include "event/reaction/fabric/ArmVibrateGenerator.h"

#ifndef ARMVIBRATIONREACTION_H
#define ARMVIBRATIONREACTION_H

class ArmVibrationReaction: public ArmReactionGeneratorWrapper<ArmVibrateGenerator> {
public:
    void configure(ExoskeletonArmHandle& arm, uint8_t frequency, float amplitude);
};

#endif //ARMVIBRATIONREACTION_H
