#include "FilterSpeedReactionGenerator.h"

void FilterSpeedReactionGenerator::reset() {
    if(result) {
        result->shutdown(true);
    }
    delete result;
    result = nullptr;
    delete minVelocityConditionFlex;
    minVelocityConditionFlex = nullptr;
    delete maxVelocityConditionFlex;
    maxVelocityConditionFlex = nullptr;
    delete aboveMiddleVelocityConditionFlex;
    aboveMiddleVelocityConditionFlex = nullptr;
    delete inVelocityRangeConditionFlexAccel;
    inVelocityRangeConditionFlexAccel = nullptr;
    delete minVelocityConditionExtend;
    minVelocityConditionExtend = nullptr;
    delete maxVelocityConditionExtend;
    maxVelocityConditionExtend = nullptr;
    delete aboveMiddleVelocityConditionExtend;
    aboveMiddleVelocityConditionExtend = nullptr;
    delete inVelocityRangeConditionExtendAccel;
    inVelocityRangeConditionExtendAccel = nullptr;
    delete amplifyReactionExt;
    amplifyReactionExt = nullptr;
    delete resistReactionExt;
    resistReactionExt = nullptr;
    delete resistReactionFlex;
    resistReactionFlex = nullptr;
    delete amplifyReactionFlex;
    amplifyReactionFlex = nullptr;
    delete checkExtendAmplifyType;
    checkExtendAmplifyType = nullptr;
    delete checkFlexAmplifyType;
    checkFlexAmplifyType = nullptr;
    delete delayStartReaction;
    delayStartReaction = nullptr;
    delete inVelocityConditionAll;
    inVelocityConditionAll = nullptr;
    delete notInVelocityRangeConditionAll;
    notInVelocityRangeConditionAll = nullptr;
    delete isFlexingCondition;
    isFlexingCondition = nullptr;
    delete isNotFlexingCondition;
    isNotFlexingCondition = nullptr;
    delete notInVelocityRangeConditionExtend;
    notInVelocityRangeConditionExtend = nullptr;
    delete notInVelocityRangeConditionFlex;
    notInVelocityRangeConditionFlex = nullptr;

    delete zeroVelocityConditionLower;
    zeroVelocityConditionLower = nullptr;
    delete zeroVelocityConditionUpper;
    zeroVelocityConditionUpper = nullptr;
    delete isStandStill;
    isStandStill = nullptr;

    delete trueCondition;
    trueCondition = nullptr;
    delete start;
    start = nullptr;
    delete amplifyBidirectionalFlexAbordCondition;
    amplifyBidirectionalFlexAbordCondition = nullptr;
    delete amplifyBidirectionalExtendAbordCondition;
    amplifyBidirectionalExtendAbordCondition = nullptr;
}

ComposedReaction&
FilterSpeedReactionGenerator::init() {
    reset();
    trueCondition = new TrueCondition();
    delayStartReaction = new DelayReaction();
    minVelocityConditionFlex = new VelocityCondition();
    maxVelocityConditionFlex = new VelocityCondition();
    aboveMiddleVelocityConditionFlex = new VelocityCondition();
    inVelocityRangeConditionFlexAccel = new AndCondition();
    notInVelocityRangeConditionFlex = new NotCondition();

    zeroVelocityConditionUpper = new VelocityCondition();
    zeroVelocityConditionLower = new VelocityCondition();
    isStandStill = new AndCondition();
    inVelocityRangeConditionFlex = new OrCondition();
    inVelocityRangeConditionExtend = new OrCondition();

    minVelocityConditionExtend = new VelocityCondition();
    maxVelocityConditionExtend = new VelocityCondition();
    aboveMiddleVelocityConditionExtend = new VelocityCondition();
    inVelocityRangeConditionExtendAccel = new AndCondition();
    notInVelocityRangeConditionExtend = new NotCondition();

    amplifyBidirectionalFlexAbordCondition = new OrCondition();
    amplifyBidirectionalExtendAbordCondition = new OrCondition();
    inVelocityConditionAll = new OrCondition();
    notInVelocityRangeConditionAll = new NotCondition();
    isFlexingCondition = new VelocityCondition();
    isNotFlexingCondition = new NotCondition();

    checkFlexAmplifyType = new WaitForConditionReaction();
    checkExtendAmplifyType = new WaitForConditionReaction();
    amplifyReactionExt = new AmplifyReaction();
    resistReactionExt = new ResistReaction();
    amplifyReactionFlex = new AmplifyReaction();
    resistReactionFlex = new ResistReaction();
    result = new ComposedReaction();
    start = new WaitForConditionReaction();


    return *result;
}

void FilterSpeedReactionGenerator::configure(ExoskeletonJointActiveHandle &joint, float minSpeed, float maxSpeed, ExoskeletonJointHandle::MovementDirection direction,
                                             float amplifyFlexPercentage, float resistFlexPercentage, float amplifyExtensionPercentage, float resistExtensionPercentage) {
    ReactionConfigurationGuard configurationGuard(*result);
    float minVelocityFlex = abs(minSpeed);
    float maxVelocityFlex = abs(maxSpeed);
    if(minVelocityFlex > maxVelocityFlex) {
        float tmp = minVelocityFlex;
        minVelocityFlex = maxVelocityFlex;
        maxVelocityFlex = tmp;
    }
    float maxVelocityExtend = -minVelocityFlex;
    float minVelocityExtend = -maxVelocityFlex;

    result->configure(start);


    isFlexingCondition->configure(joint, FASTER_THAN, 0, 0);
    isNotFlexingCondition->configure(*isFlexingCondition);

    notInVelocityRangeConditionFlex->configure(*inVelocityRangeConditionFlexAccel);
    inVelocityRangeConditionFlexAccel->configure(*minVelocityConditionFlex, *maxVelocityConditionFlex);
    minVelocityConditionFlex->configure(joint, FASTER_THAN, minSpeed, 0);
    maxVelocityConditionFlex->configure(joint, SLOWER_THAN, maxSpeed, 0);
    aboveMiddleVelocityConditionFlex->configure(joint, FASTER_THAN, (minSpeed + maxSpeed) / 2, 0);

    zeroVelocityConditionLower->configure(joint, FASTER_THAN, -10, 0);
    zeroVelocityConditionUpper->configure(joint, SLOWER_THAN, 10, 0);
    isStandStill->configure(*zeroVelocityConditionUpper, *zeroVelocityConditionLower);
    inVelocityRangeConditionFlex->configure(*isStandStill, * inVelocityRangeConditionFlexAccel);
    inVelocityRangeConditionExtend->configure(*isStandStill, * inVelocityRangeConditionExtendAccel);

    notInVelocityRangeConditionExtend->configure(*inVelocityRangeConditionExtendAccel);
    inVelocityRangeConditionExtendAccel->configure(*minVelocityConditionExtend, *maxVelocityConditionExtend);
    minVelocityConditionExtend->configure(joint, FASTER_THAN, minVelocityExtend, 0);
    maxVelocityConditionExtend->configure(joint, SLOWER_THAN, maxVelocityExtend, 0);
    aboveMiddleVelocityConditionExtend->configure(joint, SLOWER_THAN, (minVelocityExtend + maxVelocityExtend) / 2, 0);

    amplifyBidirectionalFlexAbordCondition->configure(*isNotFlexingCondition, *minVelocityConditionFlex);
    amplifyBidirectionalExtendAbordCondition->configure(*isFlexingCondition, *maxVelocityConditionExtend);
    inVelocityConditionAll->configure(*inVelocityRangeConditionFlex, *inVelocityRangeConditionExtend);
    notInVelocityRangeConditionAll->configure(*inVelocityConditionAll);

    delayStartReaction->configure(0);

    amplifyReactionFlex->configure(joint, amplifyFlexPercentage, ExoskeletonJointHandle::ABDUCTION_OR_FLEXION, 10, minSpeed);
    resistReactionFlex->configure(joint, resistFlexPercentage, ExoskeletonJointHandle::ABDUCTION_OR_FLEXION, maxSpeed);
    amplifyReactionExt->configure(joint, amplifyExtensionPercentage, ExoskeletonJointHandle::ADDUCTION_OR_EXTENSION, 10, minSpeed);
    resistReactionExt->configure(joint, resistExtensionPercentage, ExoskeletonJointHandle::ADDUCTION_OR_EXTENSION, maxSpeed);




    amplifyReactionFlex->then(*delayStartReaction);
    resistReactionFlex->then(*delayStartReaction);
    amplifyReactionExt->then(*delayStartReaction);
    resistReactionExt->then(*delayStartReaction);
    delayStartReaction->then(*start);

    checkFlexAmplifyType->configure(*trueCondition);
    checkFlexAmplifyType->ifThenElse(*aboveMiddleVelocityConditionFlex, *resistReactionFlex, *amplifyReactionFlex);
    checkExtendAmplifyType->configure(*trueCondition);
    checkExtendAmplifyType->ifThenElse(*aboveMiddleVelocityConditionExtend, *resistReactionExt, *amplifyReactionExt);

    if(direction == ExoskeletonJointHandle::BOTH) {
        amplifyReactionExt->setAlternativeFinishCondition(amplifyBidirectionalExtendAbordCondition);
        resistReactionExt->setAlternativeFinishCondition(minVelocityConditionExtend);
        amplifyReactionFlex->setAlternativeFinishCondition(amplifyBidirectionalFlexAbordCondition);
        resistReactionFlex->setAlternativeFinishCondition(maxVelocityConditionFlex);
        start->configure(*notInVelocityRangeConditionAll);
        start->ifThenElse(*isFlexingCondition, *checkFlexAmplifyType, *checkExtendAmplifyType);

    } else if (direction == ExoskeletonJointHandle::ADDUCTION_OR_EXTENSION) {
        amplifyReactionExt->setAlternativeFinishCondition(maxVelocityConditionExtend);
        resistReactionExt->setAlternativeFinishCondition(minVelocityConditionExtend);
        start->configure(*notInVelocityRangeConditionExtend);
        start->then(*checkExtendAmplifyType);

    } else {
        amplifyReactionFlex->setAlternativeFinishCondition(minVelocityConditionFlex);
        resistReactionFlex->setAlternativeFinishCondition(maxVelocityConditionFlex);
        start->configure(*notInVelocityRangeConditionFlex);
        start->then(*checkFlexAmplifyType);

    }
}

FilterSpeedReactionGenerator::~FilterSpeedReactionGenerator() {
    reset();
}
