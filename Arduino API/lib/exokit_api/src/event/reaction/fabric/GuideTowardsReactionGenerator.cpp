#include "GuideTowardsReactionGenerator.h"
#include "util/DebugSerial.h"

void GuideTowardsReactionGenerator::reset() {
    if(result) {
        result->shutdown(true);
    }
    generatorUpperBounds.reset();
    generatorLowerBounds.reset();
    delete surpassedUpperBound;
    surpassedUpperBound = nullptr;
    delete surpassedLowerBound;
    surpassedLowerBound = nullptr;
    delete surpassedBounds;
    surpassedBounds = nullptr;
    delete notOutOfLowerBoundsCondition;
    notOutOfLowerBoundsCondition = nullptr;
    delete notOutOfUpperBoundsCondition;
    notOutOfUpperBoundsCondition = nullptr;
    delete higherMiddleBound;
    higherMiddleBound = nullptr;
    arUpperBound = nullptr;
    arLowerBound = nullptr;

    delete waitForBoundSurpassReaction;
    waitForBoundSurpassReaction = nullptr;
    delete result;
    result = nullptr;
}

ComposedReaction& GuideTowardsReactionGenerator::init() {
    reset();
    surpassedUpperBound = new AtPositionCondition();
    surpassedLowerBound = new AtPositionCondition();
    surpassedBounds = new OrCondition();
    higherMiddleBound = new AtPositionCondition();
    notOutOfLowerBoundsCondition = new NotCondition();
    notOutOfUpperBoundsCondition = new NotCondition();
    result = new ComposedReaction();
    waitForBoundSurpassReaction = new WaitForConditionReaction();
    arUpperBound = &generatorUpperBounds.init();
    arLowerBound = &generatorLowerBounds.init();

    return *result;
}

void GuideTowardsReactionGenerator::configure(ExoskeletonJointActiveHandle &joint, float goalAngleLowerBound,
                                              float goalAngleUpperBound, float amplifyPercentage,
                                              float resistPercentage) {
    ReactionConfigurationGuard configurationGuard(*result);
    surpassedUpperBound->configure(joint, HIGHER_EQUAL_THEN, goalAngleUpperBound, 0);
    notOutOfUpperBoundsCondition->configure(*surpassedUpperBound);
    surpassedLowerBound->configure(joint, LOWER_THEN, goalAngleLowerBound, 0);
    notOutOfLowerBoundsCondition->configure(*surpassedLowerBound);
    surpassedBounds->configure(*surpassedUpperBound, *surpassedLowerBound);
    higherMiddleBound->configure(joint, HIGHER_EQUAL_THEN, (goalAngleUpperBound + goalAngleLowerBound) / 2, 0);

    generatorUpperBounds.configure(joint, DirectionalAmplifyResistReactionGenerator::Direction::EXTENSION,
                                   amplifyPercentage, resistPercentage, 0);
    generatorLowerBounds.configure(joint, DirectionalAmplifyResistReactionGenerator::Direction::FLEXION,
                                   amplifyPercentage, resistPercentage, 0);

    waitForBoundSurpassReaction->configure(*surpassedBounds);
    waitForBoundSurpassReaction->ifThenElse(*higherMiddleBound, *arUpperBound, *arLowerBound);
    arLowerBound->setAlternativeFinishCondition(notOutOfLowerBoundsCondition);
    arLowerBound->then(*waitForBoundSurpassReaction);
    arUpperBound->setAlternativeFinishCondition(notOutOfUpperBoundsCondition);
    arUpperBound->then(*waitForBoundSurpassReaction);
    result->configure(waitForBoundSurpassReaction);
}

GuideTowardsReactionGenerator::~GuideTowardsReactionGenerator() {
    reset();
}
