#ifndef CHI25_EXOSKELETON_API_ARMMIRRORREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMMIRRORREACTIONGENERATOR_H


#include "exo/ExoskeletonArmHandle.h"
#include "event/reaction/ParallelReaction.h"
#include "event/reaction/ComposedReaction.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "exo/MovementScaler.h"

class ArmMirrorReactionGenerator {
private:
    ActiveJointMoveToReaction* generatedReactions[3]{};
    MovementScaler* scalers[3]{};
    ComposedReaction* composedReaction{};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ExoskeletonArmHandle* arm{};

public:
    virtual ~ArmMirrorReactionGenerator();
    void reset();
    ComposedReaction& init(ExoskeletonArmHandle &exoArmTarget);
    void configure(ExoskeletonArmHandle &exoArmSource, bool mirrorElbow, bool mirrorShoulderSide,
                   bool mirrorShoulderBack, float scaleFactorElbow = 1.0, float scaleFactorShoulderSide = 1.0, float scaleFactorShoulderBack = 1.0);

};


#endif //CHI25_EXOSKELETON_API_ARMMIRRORREACTIONGENERATOR_H
