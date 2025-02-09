#ifndef CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTIONGENERATOR_H


#include "GuideAwayReactionGenerator.h"
#include "event/reaction/ParallelReaction.h"
#include "ArmComposedReactionGenerator.h"

class ArmGuideAwayReactionGenerator: public ArmComposedReactionGenerator<GuideAwayReactionGenerator>  {
private:
    ComposedReaction& initType(GuideAwayReactionGenerator& type) override;
public:
    void configure(ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage);
};


#endif //CHI25_EXOSKELETON_API_ARMGUIDEAWAYREACTIONGENERATOR_H
