#ifndef CHI25_EXOSKELETON_API_ARMMOVETOREACTION_H
#define CHI25_EXOSKELETON_API_ARMMOVETOREACTION_H


#include "event/concept/ArmReactionGeneratorWrapper.h"
#include "event/reaction/fabric/ArmMoveToReactionGenerator.h"

class ArmMoveToReaction: public ArmReactionGeneratorWrapper<ArmMoveToReactionGenerator> {

public:
    void configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float maxVelocity);

};


#endif //CHI25_EXOSKELETON_API_ARMMOVETOREACTION_H
