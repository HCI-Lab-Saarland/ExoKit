

#ifndef CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTION_H
#define CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTION_H


#include "exo/ExoskeletonArmHandle.h"
#include "event/reaction/fabric/ArmGuideAwayReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmGuideAwayReaction: public ArmReactionGeneratorWrapper<ArmGuideAwayReactionGenerator> {
public:
        void configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage);

};


#endif //CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTION_H
