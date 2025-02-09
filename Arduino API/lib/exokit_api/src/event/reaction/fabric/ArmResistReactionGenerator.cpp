#include "ArmResistReactionGenerator.h"

void ArmResistReactionGenerator::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    for (auto & generatedReaction : generatedReactions) {
        delete generatedReaction;
        generatedReaction = nullptr;
    }
    delete pr1;
    pr1 = nullptr;
    delete pr2;
    pr2 = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

ComposedReaction &ArmResistReactionGenerator::init(ExoskeletonArmHandle &exoArm) {
    reset();
    arm = &exoArm;
    int8_t jointCount = 0;
    if(arm->getElbow().isActive()) {
        generatedReactions[jointCount] = new ResistReaction();
        jointCount++;
    }
    if(arm->getShoulderSide().isActive()) {
        generatedReactions[jointCount] = new ResistReaction();
        jointCount++;
    }
    if(arm->getShoulderBack().isActive()) {
        generatedReactions[jointCount] = new ResistReaction();
        jointCount++;
    }
    composedReaction = new ComposedReaction();
    pr1 = new ParallelReaction();
    pr2 = new ParallelReaction();
    return *composedReaction;
}

void ArmResistReactionGenerator::configure(float resistPercentage, ExoskeletonJointHandle::MovementDirection resistDirection,
                                           float minVelocity) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    int8_t jointCount = 0;
    if(generatedReactions[jointCount] && arm->getElbow().isActive()) {
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getElbow()),
                                                  resistPercentage,
                                                  resistDirection,
                                                  minVelocity);
        jointCount++;
    }
    if(generatedReactions[jointCount] && arm->getShoulderBack().isActive()) {
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderBack()),
                                                  resistPercentage,
                                                  resistDirection,
                                                  minVelocity);
        jointCount++;
    }
    if(generatedReactions[jointCount] && arm->getShoulderSide().isActive()) {
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderSide()),
                                                  resistPercentage,
                                                  resistDirection,
                                                  minVelocity);
        jointCount++;
    }
    switch (jointCount) {
        case 1:
            composedReaction->configure(generatedReactions[0]);
            break;
        case 2:
            pr1->configure(*generatedReactions[0], *generatedReactions[1]);
            composedReaction->configure(pr1);
            break;
        case 3:
            pr2->configure(*generatedReactions[1], *generatedReactions[2]);
            pr1->configure(*pr2, *generatedReactions[0]);
            composedReaction->configure(pr1);
            break;
        default:
            composedReaction->configure(nullptr);
            break;
    }
}

ArmResistReactionGenerator::~ArmResistReactionGenerator() {
    reset();
}

