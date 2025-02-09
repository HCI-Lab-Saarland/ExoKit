#include "GuideAwayReactionGenerator.h"

void GuideAwayReactionGenerator::reset() {
    generatorLowerSide.reset();
    generatorUpperSide.reset();
    delete start;
    start = nullptr;
    delete checkAboveMiddleInDeadZone;
    checkAboveMiddleInDeadZone = nullptr;
    delete checkAboveMiddleOutsideDeadZone;
    checkAboveMiddleOutsideDeadZone = nullptr;
    delete trueCondition;
    trueCondition = nullptr;
    delete aboveDeadZoneLowerBoundCondition;
    aboveDeadZoneLowerBoundCondition = nullptr;
    delete belowDeadZoneUpperBoundCondition;
    belowDeadZoneUpperBoundCondition = nullptr;
    delete inDeadZoneStrictCondition;
    inDeadZoneStrictCondition = nullptr;
    delete aboveDeadZoneMiddle;
    aboveDeadZoneMiddle = nullptr;
    delete deadZoneMoveUpReaction;
    deadZoneMoveUpReaction = nullptr;
    delete deadZoneMoveDownReaction;
    deadZoneMoveDownReaction = nullptr;
    amplifyLowerReaction = nullptr;
    amplifyUpperReaction = nullptr;
    delete result;
    result = nullptr;
}

ComposedReaction &GuideAwayReactionGenerator::init() {
    if(result) {
        result->shutdown(true);
    }
    reset();
    start = new WaitForConditionReaction();
    checkAboveMiddleInDeadZone = new WaitForConditionReaction();
    checkAboveMiddleOutsideDeadZone = new WaitForConditionReaction();
    trueCondition = new TrueCondition();
    aboveDeadZoneLowerBoundCondition = new AtPositionCondition();
    belowDeadZoneUpperBoundCondition = new AtPositionCondition();
    inDeadZoneStrictCondition = new AndCondition();

    aboveDeadZoneMiddle = new AtPositionCondition();
    deadZoneMoveUpReaction = new ActiveJointMoveToReaction();
    deadZoneMoveDownReaction = new ActiveJointMoveToReaction();
    amplifyLowerReaction = &generatorLowerSide.init();
    amplifyUpperReaction = &generatorUpperSide.init();
    result = new ComposedReaction();

    return *result;
}

void GuideAwayReactionGenerator::configure(ExoskeletonJointActiveHandle &joint, float deadZoneLowerBound,
                                           float deadZoneUpperBound, float amplifyPercentage,
                                           float resistPercentage) {
    ReactionConfigurationGuard configurationGuard(*result);
    generatorLowerSide.configure(joint, DirectionalAmplifyResistReactionGenerator::EXTENSION, amplifyPercentage,
                                 resistPercentage);
    generatorUpperSide.configure(joint, DirectionalAmplifyResistReactionGenerator::FLEXION, amplifyPercentage,
                                 resistPercentage);
    start->configure(*trueCondition);
    aboveDeadZoneLowerBoundCondition->configure(joint, CompareType::HIGHER_EQUAL_THEN, deadZoneLowerBound, 0);
    belowDeadZoneUpperBoundCondition->configure(joint, CompareType::LOWER_THEN, deadZoneUpperBound, 0);
    inDeadZoneStrictCondition->configure(*aboveDeadZoneLowerBoundCondition, *belowDeadZoneUpperBoundCondition);
    aboveDeadZoneMiddle->configure(joint, CompareType::HIGHER_EQUAL_THEN, (deadZoneLowerBound + deadZoneUpperBound) / 2, 0);

    checkAboveMiddleInDeadZone->configure(*trueCondition);
    deadZoneMoveUpReaction->configure(joint, deadZoneUpperBound + 1.f, 0, 0.5, ABSOLUTE);
    deadZoneMoveDownReaction->configure(joint, deadZoneLowerBound - 1.f, 0, 0.5, ABSOLUTE);

    checkAboveMiddleOutsideDeadZone->configure(*trueCondition);

    start->ifThenElse(*inDeadZoneStrictCondition, *checkAboveMiddleInDeadZone, *checkAboveMiddleOutsideDeadZone);
    checkAboveMiddleInDeadZone->ifThenElse(*aboveDeadZoneMiddle, *deadZoneMoveUpReaction, *deadZoneMoveDownReaction);
    deadZoneMoveUpReaction->then(*start);
    deadZoneMoveDownReaction->then(*start);

    checkAboveMiddleOutsideDeadZone->ifThenElse(*aboveDeadZoneMiddle, *amplifyUpperReaction, *amplifyLowerReaction);
    amplifyLowerReaction->setAlternativeFinishCondition(aboveDeadZoneLowerBoundCondition);
    amplifyUpperReaction->setAlternativeFinishCondition(belowDeadZoneUpperBoundCondition);
    amplifyLowerReaction->then(*checkAboveMiddleInDeadZone);
    amplifyUpperReaction->then(*checkAboveMiddleInDeadZone);
    result->configure(start);
}

GuideAwayReactionGenerator::~GuideAwayReactionGenerator() {
    reset();
}

