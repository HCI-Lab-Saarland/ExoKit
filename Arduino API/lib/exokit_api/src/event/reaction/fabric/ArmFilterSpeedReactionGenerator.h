
#ifndef CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTIONGENERATOR_H


#include "FilterSpeedReactionGenerator.h"
#include "event/reaction/ParallelReaction.h"
#include "ArmComposedReactionGenerator.h"

class ArmFilterSpeedReactionGenerator: public ArmComposedReactionGenerator<FilterSpeedReactionGenerator> {
private:
    ComposedReaction& initType(FilterSpeedReactionGenerator& type) override;

public:
    void configure(float minSpeed, float maxSpeed,
                   ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05,
                   float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05);
};


#endif //CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTIONGENERATOR_H
