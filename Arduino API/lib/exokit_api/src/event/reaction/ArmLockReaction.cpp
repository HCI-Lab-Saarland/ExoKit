#include "ArmLockReaction.h"

void ArmLockReaction::configure(ExoskeletonArmHandle &exoArm) {
    this->newInitArm = &exoArm;
    this->init();
    this->generator->configure();
}

