#ifndef CHI25_EXOSKELETON_API_ARMJERKREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMJERKREACTIONGENERATOR_H


#include "event/concept/MotionStyle/JerkReaction.h"
#include "exo/ExoskeletonArmHandle.h"
#include "event/reaction/ComposedReaction.h"
#include "event/reaction/ParallelReaction.h"

class ArmJerkReactionGenerator {
private:
    JerkReaction* generatedReactions[3]{};
    ComposedReaction* composedReaction{};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ExoskeletonArmHandle* arm{};

public:
    virtual ~ArmJerkReactionGenerator();
    void reset();
    ComposedReaction& init(ExoskeletonArmHandle &exoArm);
    void configure(float minJerkAngle, float maxJerkAngle, long minJerkInterval,
                   long maxJerkInterval, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight,
                   float velocity = 0, unsigned long nr_jerks = 0);
};


#endif //CHI25_EXOSKELETON_API_ARMJERKREACTIONGENERATOR_H
