
#ifndef CHI25_EXOSKELETON_API_CONSTRAINTOREACTION_H
#define CHI25_EXOSKELETON_API_CONSTRAINTOREACTION_H


#include "event/reaction/fabric/ConstrainToReactionGenerator.h"
#include "event/concept/ReactionGeneratorWrapper.h"

class ConstrainToReaction: public ReactionGeneratorWrapper<ConstrainToReactionGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle& joint, float angle, float radius);

};


#endif //CHI25_EXOSKELETON_API_CONSTRAINTOREACTION_H
