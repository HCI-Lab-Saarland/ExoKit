#include "ConstrainToReactionGenerator.h"

void ConstrainToReactionGenerator::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    delete atPositionLowerBound;
    atPositionLowerBound = nullptr;
    delete atPositionUpperBound;
    atPositionUpperBound = nullptr;
    delete isHigherMiddleAngle;
    isHigherMiddleAngle = nullptr;
    delete lowerBoundReaction;
    lowerBoundReaction = nullptr;
    delete upperBoundReaction;
    upperBoundReaction = nullptr;
    delete waitForLowerReaction;
    waitForLowerReaction = nullptr;
    delete waitForUpperReaction;
    waitForUpperReaction = nullptr;
    delete waitForPositionOrCondition;
    waitForPositionOrCondition = nullptr;
    delete waitForStartReaction;
    waitForStartReaction = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

ComposedReaction& ConstrainToReactionGenerator::init() {
    reset();
    lowerBoundReaction = new ActiveJointMoveToReaction();
    upperBoundReaction = new ActiveJointMoveToReaction();
    isHigherMiddleAngle = new AtPositionCondition();
    atPositionLowerBound = new AtPositionCondition();
    atPositionUpperBound = new AtPositionCondition();
    waitForLowerReaction = new WaitForConditionReaction();
    waitForUpperReaction = new WaitForConditionReaction();
    waitForStartReaction = new WaitForConditionReaction();
    waitForPositionOrCondition = new OrCondition();
    composedReaction = new ComposedReaction();

    return *composedReaction;
}

void ConstrainToReactionGenerator::configure(ExoskeletonJointActiveHandle &joint, float lowerBoundAngle, float upperBoundAngle) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    if(!atPositionLowerBound) {
        return;
    }
    float middleAngle = (lowerBoundAngle + upperBoundAngle) / 2.f;


    lowerBoundReaction->configure(joint, lowerBoundAngle + 0.55f, 0, 0.5, ABSOLUTE);
    upperBoundReaction->configure(joint, upperBoundAngle - 0.55f, 0, 0.5, ABSOLUTE);
    isHigherMiddleAngle->configure(joint, HIGHER_EQUAL_THEN, middleAngle, 0);
    atPositionLowerBound->configure(joint, LOWER_THEN, lowerBoundAngle, 0);
    atPositionUpperBound->configure(joint, HIGHER_EQUAL_THEN, upperBoundAngle, 0);
    waitForPositionOrCondition->configure(*atPositionUpperBound, *atPositionLowerBound);
    waitForUpperReaction->configure(*atPositionUpperBound);
    waitForLowerReaction->configure(*atPositionLowerBound);
    waitForStartReaction->configure(*waitForPositionOrCondition);

    waitForStartReaction->ifThenElse(*isHigherMiddleAngle, *upperBoundReaction, *lowerBoundReaction);
    upperBoundReaction->then(*waitForStartReaction);
    lowerBoundReaction->then(*waitForStartReaction);
    composedReaction->configure(waitForStartReaction);
}

ConstrainToReactionGenerator::~ConstrainToReactionGenerator() {
    reset();
}
