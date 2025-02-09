#ifndef CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYRESISTREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYRESISTREACTIONGENERATOR_H


#include "event/reaction/WaitForConditionReaction.h"
#include "event/condition/VelocityCondition.h"
#include "event/condition/OrCondition.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/reaction/ComposedReaction.h"

class DirectionalAmplifyResistReactionGenerator {
public:
    enum Direction {
        FLEXION, EXTENSION
    };
private:

    AmplifyReaction* amplifyReaction;
    ResistReaction* resistReaction;
    WaitForConditionReaction* waitForMovementReaction;
    VelocityCondition* isStrongFlexCondition;
    VelocityCondition* isStrongExtendCondition;
    OrCondition* isStrongMovement;
    VelocityCondition* isFlexCondition;
    VelocityCondition* isExtendCondition;
    ComposedReaction* composedReaction;

public:
    virtual ~DirectionalAmplifyResistReactionGenerator();
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonJointActiveHandle &joint, DirectionalAmplifyResistReactionGenerator::Direction directionToAmplify,
                   float amplifyPercentage = 0.05, float resistPercentage = 0.05,
                   float startAmplify = 15, float maxVelocity = 0);
};


#endif //CHI25_EXOSKELETON_API_DIRECTIONALAMPLIFYRESISTREACTIONGENERATOR_H
