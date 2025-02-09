#include "ArmMoveToReaction.h"

void ArmMoveToReaction::configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float maxVelocity) {
    this->newInitArm = &exoArm;
    this->init();
    generator->configure(pos, maxVelocity);
}
