#ifndef CHI25_EXOSKELETON_API_ARMRESISTREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMRESISTREACTIONGENERATOR_H


#include "event/reaction/ComposedReaction.h"
#include "exo/ExoskeletonArmHandle.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/reaction/ParallelReaction.h"

class ArmResistReactionGenerator {
private:
    ResistReaction* generatedReactions[3]{};
    ComposedReaction* composedReaction{};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ExoskeletonArmHandle* arm{};

public:
    void reset();
    virtual ~ArmResistReactionGenerator();
    ComposedReaction& init(ExoskeletonArmHandle &exoArm);
    void configure(float resistPercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float minVelocity = 0);
};


#endif //CHI25_EXOSKELETON_API_ARMRESISTREACTIONGENERATOR_H
