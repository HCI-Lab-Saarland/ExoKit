#ifndef CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTIONGENERATOR_H


#include "event/reaction/ComposedReaction.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "model/ExoArmAngles.h"
#include "GuideTowardsReactionGenerator.h"
#include "event/reaction/ParallelReaction.h"
#include "ArmComposedReactionGenerator.h"

class ArmGuideTowardsReactionGenerator: public ArmComposedReactionGenerator<GuideTowardsReactionGenerator> {
private:
    ComposedReaction& initType(GuideTowardsReactionGenerator& type) override;
public:
    void configure(ExoArmAngles pos, float radius, float amplifyPercentage, float resistPercentage);
};


#endif //CHI25_EXOSKELETON_API_ARMGUIDETOWARDSREACTIONGENERATOR_H
