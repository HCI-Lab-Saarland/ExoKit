
#ifndef CHI25_EXOSKELETON_API_ARMAMPLIFYREACTION_H
#define CHI25_EXOSKELETON_API_ARMAMPLIFYREACTION_H


#include "event/reaction/fabric/ArmAmplifyReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmAmplifyReaction: public ArmReactionGeneratorWrapper<ArmAmplifyReactionGenerator> {

public:
    void configure(ExoskeletonArmHandle &exoArm, float amplifyPercentage,
                   ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float startingVelocity = 30, float maxVelocity = 0);
};


#endif //CHI25_EXOSKELETON_API_ARMAMPLIFYREACTION_H
