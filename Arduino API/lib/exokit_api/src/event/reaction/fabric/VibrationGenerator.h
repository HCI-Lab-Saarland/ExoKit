#ifndef VIBRATIONGENERATOR_H
#define VIBRATIONGENERATOR_H

#include <event/reaction/ActiveJointMoveToReaction.h>
#include <event/reaction/JointLockReaction.h>

#include "ArmComposedReactionGenerator.h"
#include "ArmMoveToReactionGenerator.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/ComposedReaction.h"
#include "event/condition/TimeoutCondition.h"

class VibrationGenerator {
private:
    ActiveJointMoveToReaction* moves[2]={};
    TimeoutCondition* timeouts[2]={};
    ComposedReaction* result{};

public:
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude);
};

#endif //VIBRATIONGENERATOR_H
