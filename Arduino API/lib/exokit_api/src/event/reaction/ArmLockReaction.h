#ifndef CHI25_EXOSKELETON_API_ARMLOCKREACTION_H
#define CHI25_EXOSKELETON_API_ARMLOCKREACTION_H


#include "event/reaction/fabric/ArmLockReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmLockReaction: public ArmReactionGeneratorWrapper<ArmLockReactionGenerator> {
public:
    void configure(ExoskeletonArmHandle &exoArm);
};


#endif //CHI25_EXOSKELETON_API_ARMLOCKREACTION_H
