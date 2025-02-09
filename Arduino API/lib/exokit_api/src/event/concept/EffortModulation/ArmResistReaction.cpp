
#include "ArmResistReaction.h"

void ArmResistReaction::configure(ExoskeletonArmHandle &exoArm, float resistPercentage,
                                  ExoskeletonJointHandle::MovementDirection resistDirection,
                                  float minVelocity) {
    this->newInitArm = &exoArm;
    this->init();
    generator->configure(resistPercentage, resistDirection, minVelocity);
}
