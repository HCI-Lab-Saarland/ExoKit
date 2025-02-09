#include "DirectionalAmplifyResistReactionGenerator.h"
#include "exo/ExoskeletonJointActiveHandle.h"

ComposedReaction& DirectionalAmplifyResistReactionGenerator::init() {
    reset();
    amplifyReaction = new AmplifyReaction();
    resistReaction = new ResistReaction();
    waitForMovementReaction = new WaitForConditionReaction();
    isStrongFlexCondition = new VelocityCondition();
    isStrongExtendCondition = new VelocityCondition();
    isStrongMovement = new OrCondition();
    isFlexCondition = new VelocityCondition();
    isExtendCondition = new VelocityCondition();
    composedReaction = new ComposedReaction();

    return *composedReaction;

}

void DirectionalAmplifyResistReactionGenerator::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    delete amplifyReaction;
    amplifyReaction = nullptr;
    delete resistReaction;
    resistReaction = nullptr;
    delete waitForMovementReaction;
    waitForMovementReaction = nullptr;
    delete isStrongFlexCondition;
    isStrongFlexCondition = nullptr;
    delete isStrongExtendCondition;
    isStrongExtendCondition = nullptr;
    delete isStrongMovement;
    isStrongMovement = nullptr;
    delete isFlexCondition;
    isFlexCondition = nullptr;
    delete isExtendCondition;
    isExtendCondition = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

void DirectionalAmplifyResistReactionGenerator::configure(ExoskeletonJointActiveHandle &joint,
                                                          DirectionalAmplifyResistReactionGenerator::Direction directionToAmplify,
                                                          float amplifyPercentage, float resistPercentage,
                                                          float startAmplify,
                                                          float maxVelocity) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    waitForMovementReaction->configure(*isStrongMovement);
    isStrongMovement->configure(*isStrongExtendCondition, *isStrongFlexCondition);
    isStrongFlexCondition->configure(joint, SpeedCompareType::FASTER_THAN, startAmplify);
    isStrongExtendCondition->configure(joint, SpeedCompareType::SLOWER_THAN, -startAmplify);

    isFlexCondition->configure(joint, SpeedCompareType::FASTER_THAN, 0);
    isExtendCondition->configure(joint, SpeedCompareType::SLOWER_THAN, -0);

    amplifyReaction->configure(joint, amplifyPercentage, ExoskeletonJointHandle::MovementDirection::BOTH,
                               startAmplify, maxVelocity);
    resistReaction->configure(joint, resistPercentage, ExoskeletonJointHandle::MovementDirection::BOTH,
                              0);

    if(directionToAmplify == FLEXION) {
        waitForMovementReaction->ifThenElse(*isFlexCondition, *amplifyReaction, *resistReaction);
        amplifyReaction->setAlternativeFinishCondition(isExtendCondition);
        resistReaction->setAlternativeFinishCondition(isFlexCondition);
    } else {
        waitForMovementReaction->ifThenElse(*isFlexCondition, *resistReaction, *amplifyReaction);
        amplifyReaction->setAlternativeFinishCondition(isFlexCondition);
        resistReaction->setAlternativeFinishCondition(isExtendCondition);
    }
    amplifyReaction->then(*waitForMovementReaction);
    resistReaction->then(*waitForMovementReaction);

    composedReaction->configure(waitForMovementReaction);
}

DirectionalAmplifyResistReactionGenerator::~DirectionalAmplifyResistReactionGenerator() {
    reset();
}
