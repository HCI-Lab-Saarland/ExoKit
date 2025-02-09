
#ifndef CHI25_EXOSKELETON_API_ARMRESISTREACTION_H
#define CHI25_EXOSKELETON_API_ARMRESISTREACTION_H


#include "event/concept/ArmReactionGeneratorWrapper.h"
#include "event/reaction/fabric/ArmResistReactionGenerator.h"

class ArmResistReaction: public ArmReactionGeneratorWrapper<ArmResistReactionGenerator> {

public:
    void configure(ExoskeletonArmHandle &exoArm, float resistPercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float minVelocity = 0);

};


#endif //CHI25_EXOSKELETON_API_ARMRESISTREACTION_H
