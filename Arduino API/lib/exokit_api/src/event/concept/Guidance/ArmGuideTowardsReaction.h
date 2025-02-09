
#ifndef CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTION_H
#define CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTION_H


#include "event/reaction/fabric/ArmGuideTowardsReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmGuideTowardsReaction: public ArmReactionGeneratorWrapper<ArmGuideTowardsReactionGenerator> {
public:
    void configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage);

};




#endif //CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTION_H
