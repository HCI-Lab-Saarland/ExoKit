#ifndef CHI25_EXOSKELETON_API_CONSTRAINTOREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_CONSTRAINTOREACTIONGENERATOR_H


#include "event/reaction/IReaction.h"
#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "event/condition/AtPositionCondition.h"
#include "event/reaction/WaitForConditionReaction.h"
#include "event/condition/OrCondition.h"
#include "event/reaction/ComposedReaction.h"

class ConstrainToReactionGenerator {
private:
    ActiveJointMoveToReaction* upperBoundReaction{};
    ActiveJointMoveToReaction* lowerBoundReaction{};
    AtPositionCondition* atPositionUpperBound{};
    AtPositionCondition* atPositionLowerBound{};
    AtPositionCondition* isHigherMiddleAngle{};
    WaitForConditionReaction* waitForLowerReaction{};
    WaitForConditionReaction* waitForUpperReaction{};
    OrCondition* waitForPositionOrCondition{};
    WaitForConditionReaction* waitForStartReaction{};
    ComposedReaction* composedReaction{};

public:
    virtual ~ConstrainToReactionGenerator();
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonJointActiveHandle& joint, float lowerBoundAngle, float upperBoundAngle);
};


#endif //CHI25_EXOSKELETON_API_CONSTRAINTOREACTIONGENERATOR_H
