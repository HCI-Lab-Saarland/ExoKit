
#ifndef CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTION_H
#define CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTION_H


#include "exo/ExoskeletonArmHandle.h"
#include "event/reaction/fabric/ArmFilterSpeedReactionGenerator.h"
#include "event/concept/ArmReactionGeneratorWrapper.h"

class ArmFilterSpeedReaction: public ArmReactionGeneratorWrapper<ArmFilterSpeedReactionGenerator> {
public:
    void configure(ExoskeletonArmHandle &exoArm, float minSpeed, float maxSpeed,
                   ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05,
                   float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05);
};



#endif //CHI25_EXOSKELETON_API_ARMFILTERSPEEDREACTION_H
