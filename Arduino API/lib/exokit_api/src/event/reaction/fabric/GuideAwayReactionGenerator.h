#ifndef CHI25_EXOSKELETON_API_GUIDEAWAYREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_GUIDEAWAYREACTIONGENERATOR_H


#include "DirectionalAmplifyResistReactionGenerator.h"
#include "event/condition/AtPositionCondition.h"
#include "event/condition/AndCondition.h"
#include "event/condition/TrueCondition.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "event/condition/NotCondition.h"

class GuideAwayReactionGenerator {
    DirectionalAmplifyResistReactionGenerator generatorLowerSide;
    DirectionalAmplifyResistReactionGenerator generatorUpperSide;
    WaitForConditionReaction* start;
    WaitForConditionReaction* checkAboveMiddleInDeadZone;
    WaitForConditionReaction* checkAboveMiddleOutsideDeadZone;
    TrueCondition* trueCondition;
    AtPositionCondition* aboveDeadZoneLowerBoundCondition;
    AtPositionCondition* belowDeadZoneUpperBoundCondition;
    AndCondition* inDeadZoneStrictCondition;
    AtPositionCondition* aboveDeadZoneMiddle;
    ActiveJointMoveToReaction* deadZoneMoveUpReaction;
    ActiveJointMoveToReaction* deadZoneMoveDownReaction;
    ComposedReaction* amplifyLowerReaction;
    ComposedReaction* amplifyUpperReaction;
    ComposedReaction* result;

public:
    virtual ~GuideAwayReactionGenerator();
    void reset();
    ComposedReaction& init();
    void configure(ExoskeletonJointActiveHandle &joint, float deadZoneLowerBound, float deadZoneUpperBound, float amplifyPercentage = 0.05, float resistPercentage = 0.05);

};


#endif //CHI25_EXOSKELETON_API_GUIDEAWAYREACTIONGENERATOR_H
