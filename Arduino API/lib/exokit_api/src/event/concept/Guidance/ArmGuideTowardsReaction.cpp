
#include "ArmGuideTowardsReaction.h"

void ArmGuideTowardsReaction::configure(ExoskeletonArmHandle &exoArm, ExoArmAngles pos, float radius, float amplifyPercentage,
                                        float resistPercentage) {
    this->newInitArm = &exoArm;
    this->init();
    generator->configure(pos, radius, amplifyPercentage, resistPercentage);

}

