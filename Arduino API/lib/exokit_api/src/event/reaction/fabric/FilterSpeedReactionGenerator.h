#ifndef CHI25_EXOSKELETON_API_FILTERSPEEDREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_FILTERSPEEDREACTIONGENERATOR_H


#include "event/condition/VelocityCondition.h"
#include "event/concept/EffortModulation/AmplifyReaction.h"
#include "event/concept/EffortModulation/ResistReaction.h"
#include "event/reaction/ComposedReaction.h"
#include "event/condition/OrCondition.h"
#include "event/condition/NotCondition.h"
#include "event/reaction/WaitForConditionReaction.h"
#include "event/condition/AndCondition.h"
#include "event/condition/TrueCondition.h"
#include "event/condition/FalseCondition.h"
#include "event/reaction/DelayReaction.h"

class FilterSpeedReactionGenerator {
public:
    TrueCondition* trueCondition{};

    VelocityCondition* minVelocityConditionFlex{};
    VelocityCondition* maxVelocityConditionFlex{};
    AndCondition* inVelocityRangeConditionFlexAccel{};
    NotCondition* notInVelocityRangeConditionFlex{};
    VelocityCondition* aboveMiddleVelocityConditionFlex{};

    VelocityCondition* minVelocityConditionExtend{};
    VelocityCondition* maxVelocityConditionExtend{};
    AndCondition* inVelocityRangeConditionExtendAccel{};
    NotCondition* notInVelocityRangeConditionExtend{};
    VelocityCondition* aboveMiddleVelocityConditionExtend{};
    OrCondition* amplifyBidirectionalFlexAbordCondition{};
    OrCondition* amplifyBidirectionalExtendAbordCondition{};

    VelocityCondition* zeroVelocityConditionUpper{};
    VelocityCondition* zeroVelocityConditionLower{};
    AndCondition* isStandStill{};
    OrCondition* inVelocityRangeConditionFlex{};
    OrCondition* inVelocityRangeConditionExtend{};


    DelayReaction* delayStartReaction{};

    OrCondition* inVelocityConditionAll{};
    NotCondition* notInVelocityRangeConditionAll{};
    VelocityCondition* isFlexingCondition{};
    NotCondition* isNotFlexingCondition{};

    WaitForConditionReaction* start{};
    WaitForConditionReaction* checkFlexAmplifyType{};
    WaitForConditionReaction* checkExtendAmplifyType{};
    AmplifyReaction* amplifyReactionExt{};
    ResistReaction* resistReactionExt{};
    AmplifyReaction* amplifyReactionFlex{};
    ResistReaction* resistReactionFlex{};
    ComposedReaction* result{};

public:
    virtual ~FilterSpeedReactionGenerator();
    void reset();
    ComposedReaction& init();

    void configure(ExoskeletonJointActiveHandle &joint, float minSpeed, float maxSpeed, ExoskeletonJointHandle::MovementDirection direction = ExoskeletonJointHandle::MovementDirection::BOTH,
                   float amplifyFlexPercentage = 0.05, float resistFlexPercentage = 0.05, float amplifyExtensionPercentage = 0.05, float resistExtensionPercentage = 0.05);

};


#endif //CHI25_EXOSKELETON_API_FILTERSPEEDREACTIONGENERATOR_H
