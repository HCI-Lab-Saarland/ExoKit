
#ifndef CHI25_EXOSKELETON_API_ARMMIRRORREACTION_H
#define CHI25_EXOSKELETON_API_ARMMIRRORREACTION_H


#include "event/concept/ArmReactionGeneratorWrapper.h"
#include "event/reaction/fabric/ArmMirrorReactionGenerator.h"

class ArmMirrorReaction: public ArmReactionGeneratorWrapper<ArmMirrorReactionGenerator> {

public:
    void configure(ExoskeletonArmHandle &exoArmTarget, ExoskeletonArmHandle &exoArmSource, bool mirrorElbow, bool mirrorShoulderSide,
                   bool mirrorShoulderBack, float scaleFactorElbow = 1.0, float scaleFactorShoulderSide = 1.0, float scaleFactorShoulderBack = 1.0);

};


#endif //CHI25_EXOSKELETON_API_ARMMIRRORREACTION_H
