
#ifndef CHI25_EXOSKELETON_API_GUIDETOWARDSREACTION_H
#define CHI25_EXOSKELETON_API_GUIDETOWARDSREACTION_H

#include "event/concept/ReactionGeneratorWrapper.h"
#include "event/reaction/fabric/GuideTowardsReactionGenerator.h"

class GuideTowardsReaction: public ReactionGeneratorWrapper<GuideTowardsReactionGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle &joint, float angle, float radius, float amplifyPercentage, float resistPercentage);

};

#endif //CHI25_EXOSKELETON_API_GUIDETOWARDSREACTION_H
