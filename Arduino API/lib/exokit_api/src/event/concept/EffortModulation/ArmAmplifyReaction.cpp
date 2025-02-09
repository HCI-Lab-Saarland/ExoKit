
#include "ArmAmplifyReaction.h"

void ArmAmplifyReaction::configure(ExoskeletonArmHandle &exoArm, float amplifyPercentage,
                                   ExoskeletonJointHandle::MovementDirection resistDirection,
                                   float startingVelocity, float maxVelocity) {
    this->newInitArm = &exoArm;
    this->init();
    this->generator->configure(amplifyPercentage, resistDirection,
                               startingVelocity, maxVelocity);
}
