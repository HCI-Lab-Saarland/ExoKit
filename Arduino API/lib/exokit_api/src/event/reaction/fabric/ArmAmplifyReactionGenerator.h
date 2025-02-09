
#ifndef CHI25_EXOSKELETON_API_ARMAMPLIFYREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMAMPLIFYREACTIONGENERATOR_H


#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "ArmComposedReactionGenerator.h"

class ArmAmplifyReactionGenerator {
private:
    AmplifyReaction* generatedReactions[3]{};
    ComposedReaction* composedReaction{};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ExoskeletonArmHandle* arm{};

public:
    void reset();
    ComposedReaction& init(ExoskeletonArmHandle &exoArm);
    virtual ~ArmAmplifyReactionGenerator();
    void configure(float amplifyPercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float startingVelocity = 30, float maxVelocity = 0);
};


#endif //CHI25_EXOSKELETON_API_ARMAMPLIFYREACTIONGENERATOR_H
