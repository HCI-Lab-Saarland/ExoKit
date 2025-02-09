
#ifndef CHI25_EXOSKELETON_API_ARMJERKREACTION_H
#define CHI25_EXOSKELETON_API_ARMJERKREACTION_H


#include "event/reaction/fabric/ArmJerkReactionGenerator.h"

#include "event/concept/ArmReactionGeneratorWrapper.h"
class ArmJerkReaction: public ArmReactionGeneratorWrapper<ArmJerkReactionGenerator> {

public:
    void configure(ExoskeletonArmHandle &exoArm, float minJerkAngle, float maxJerkAngle, long minJerkInterval,
                   long maxJerkInterval, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight,
                   float velocity = 0, unsigned long nr_jerks = 0);
};



#endif //CHI25_EXOSKELETON_API_ARMJERKREACTION_H
