
#include "ArmFilterSpeedReaction.h"

void ArmFilterSpeedReaction::configure(ExoskeletonArmHandle &exoArm, float minSpeed, float maxSpeed,
                                       ExoskeletonJointHandle::MovementDirection direction, float amplifyFlexPercentage,
                                       float resistFlexPercentage, float amplifyExtensionPercentage,
                                       float resistExtensionPercentage) {
    this->newInitArm = &exoArm;
    this->init();
    this->generator->configure(minSpeed, maxSpeed, direction, amplifyFlexPercentage,
                               resistFlexPercentage, amplifyExtensionPercentage, resistExtensionPercentage);

}
