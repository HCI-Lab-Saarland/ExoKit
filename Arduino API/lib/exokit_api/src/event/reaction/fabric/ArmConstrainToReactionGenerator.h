
#ifndef CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTIONGENERATOR_H


#include "exo/ExoskeletonArmHandle.h"
#include "event/reaction/ComposedReaction.h"
#include "event/reaction/ParallelReaction.h"
#include "ConstrainToReactionGenerator.h"
#include "ArmComposedReactionGenerator.h"

class ArmConstrainToReactionGenerator: public ArmComposedReactionGenerator<ConstrainToReactionGenerator> {
private:
    ComposedReaction& initType(ConstrainToReactionGenerator& type) override;

public:
    void configure(ExoArmAngles pos, float radius);
};


#endif //CHI25_EXOSKELETON_API_ARMCONSTRAINTOREACTIONGENERATOR_H
