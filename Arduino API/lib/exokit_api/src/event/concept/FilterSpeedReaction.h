
#ifndef CHI25_EXOSKELETON_API_FILTERSPEEDREACTION_H
#define CHI25_EXOSKELETON_API_FILTERSPEEDREACTION_H


#include "event/concept/ArmReactionGeneratorWrapper.h"
#include "event/concept/ReactionGeneratorWrapper.h"
#include "event/reaction/fabric/FilterSpeedReactionGenerator.h"

class FilterSpeedReaction: public ReactionGeneratorWrapper<FilterSpeedReactionGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle &joint, float minSpeed, float maxSpeed,
                   ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05,
                   float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05);
};


#endif //CHI25_EXOSKELETON_API_FILTERSPEEDREACTION_H
