
#include "ArmConstrainToReaction.h"

void ArmConstrainToReaction::configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float radius) {
    this->newInitArm = &exoArm;
    this->init();
    this->generator->configure(pos, radius);
}
