
#ifndef CHI25_EXOSKELETON_API_GUIDEAWAYREACTION_H
#define CHI25_EXOSKELETON_API_GUIDEAWAYREACTION_H


#include "event/reaction/fabric/GuideAwayReactionGenerator.h"
#include "event/concept/ReactionGeneratorWrapper.h"

class GuideAwayReaction: public ReactionGeneratorWrapper<GuideAwayReactionGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle &joint, float angle, float radius, float amplifyPercentage = 0.05, float resistPercentage = 0.05);

};


#endif //CHI25_EXOSKELETON_API_GUIDEAWAYREACTION_H
