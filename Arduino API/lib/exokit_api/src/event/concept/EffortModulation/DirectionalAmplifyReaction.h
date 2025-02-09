
#ifndef CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYREACTION_H
#define CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYREACTION_H


#include "event/reaction/fabric/DirectionalAmplifyResistReactionGenerator.h"
#include "event/concept/ReactionGeneratorWrapper.h"

class DirectionalAmplifyReaction: public ReactionGeneratorWrapper<DirectionalAmplifyResistReactionGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle &joint, DirectionalAmplifyResistReactionGenerator::Direction directionToAmplify,
                   float amplifyPercentage = 0.05, float resistPercentage = 0.05,
                   float startAmplify = 15, float maxVelocity = 0) {
        init();
        generator->configure(joint, directionToAmplify, amplifyPercentage, resistPercentage, startAmplify, maxVelocity);
    }

};


#endif //CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYREACTION_H
