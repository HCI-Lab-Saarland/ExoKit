

#ifndef CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTION_H
#define CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTION_H


#include "event/reaction/fabric/ArmConstrainToReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmConstrainToReaction: public ArmReactionGeneratorWrapper<ArmConstrainToReactionGenerator> {
public:
    void configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float radius);
};



#endif //CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTION_H
