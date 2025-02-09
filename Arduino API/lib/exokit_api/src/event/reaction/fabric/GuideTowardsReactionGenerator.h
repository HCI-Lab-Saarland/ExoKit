#ifndef CHI25_EXOSKELETON_API_GUIDETOWARDSREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_GUIDETOWARDSREACTIONGENERATOR_H


#include "event/condition/AtPositionCondition.h"
#include "event/reaction/WaitForConditionReaction.h"
#include "event/condition/OrCondition.h"
#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/condition/VelocityCondition.h"
#include "event/condition/TrueCondition.h"
#include "DirectionalAmplifyResistReactionGenerator.h"
#include "event/condition/NotCondition.h"

class GuideTowardsReactionGenerator {
private:
    DirectionalAmplifyResistReactionGenerator generatorLowerBounds;
    DirectionalAmplifyResistReactionGenerator generatorUpperBounds;

    AtPositionCondition* surpassedUpperBound;
    AtPositionCondition* surpassedLowerBound;
    OrCondition* surpassedBounds;
    NotCondition* notOutOfLowerBoundsCondition;
    NotCondition* notOutOfUpperBoundsCondition;
    AtPositionCondition* higherMiddleBound;

    WaitForConditionReaction* waitForBoundSurpassReaction;
    ComposedReaction* arLowerBound;
    ComposedReaction* arUpperBound;
    ComposedReaction* result;

public:
    virtual ~GuideTowardsReactionGenerator();
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonJointActiveHandle &joint, float goalAngleLowerBound, float goalAngleUpperBound, float amplifyPercentage, float resistPercentage);
};


#endif //CHI25_EXOSKELETON_API_GUIDETOWARDSREACTIONGENERATOR_H
