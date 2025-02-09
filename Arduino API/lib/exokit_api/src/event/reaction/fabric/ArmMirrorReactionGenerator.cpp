#include "ArmMirrorReactionGenerator.h"

void ArmMirrorReactionGenerator::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    for (auto & generatedReaction : generatedReactions) {
        delete generatedReaction;
        generatedReaction = nullptr;
    }
    for (auto & scaler : scalers) {
        delete scaler;
        scaler = nullptr;
    }
    delete pr1;
    pr1 = nullptr;
    delete pr2;
    pr2 = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

ComposedReaction &ArmMirrorReactionGenerator::init(ExoskeletonArmHandle &exoArmTarget) {
    reset();
    arm = &exoArmTarget;
    int8_t jointCount = 0;
    if(arm->getElbow().isActive()) {
        generatedReactions[jointCount] = new ActiveJointMoveToReaction();
        scalers[jointCount] = new MovementScaler();
        jointCount++;
    }
    if(arm->getShoulderSide().isActive()) {
        generatedReactions[jointCount] = new ActiveJointMoveToReaction();
        scalers[jointCount] = new MovementScaler();
        jointCount++;
    }
    if(arm->getShoulderBack().isActive()) {
        generatedReactions[jointCount] = new ActiveJointMoveToReaction();
        scalers[jointCount] = new MovementScaler();
        jointCount++;
    }
    composedReaction = new ComposedReaction();
    pr1 = new ParallelReaction();
    pr2 = new ParallelReaction();
    return *composedReaction;
}

void ArmMirrorReactionGenerator::configure(ExoskeletonArmHandle &exoArmSource, bool mirrorElbow, bool mirrorShoulderSide,
                                           bool mirrorShoulderBack, float scaleFactorElbow, float scaleFactorShoulderSide, float scaleFactorShoulderBack) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    int8_t jointCount = 0;
    if(arm->getElbow().isActive() && exoArmSource.getElbow().canTrackPosition() && mirrorElbow) {
        scalers[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(exoArmSource.getElbow()), scaleFactorElbow);
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getElbow()), *scalers[jointCount], 0);
        jointCount++;
    }
    if(arm->getShoulderBack().isActive() && exoArmSource.getShoulderBack().canTrackPosition() && mirrorShoulderSide) {
        scalers[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(exoArmSource.getShoulderBack()), scaleFactorShoulderBack);
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderBack()),
                                                  *scalers[jointCount], 0);
        jointCount++;
    }
    if(arm->getShoulderSide().isActive() && exoArmSource.getShoulderSide().canTrackPosition() && mirrorShoulderBack) {
        scalers[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(exoArmSource.getShoulderSide()), scaleFactorShoulderSide);
        generatedReactions[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderSide()),
                                                  *scalers[jointCount], 0);
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

ArmMirrorReactionGenerator::~ArmMirrorReactionGenerator() {
    reset();
}
