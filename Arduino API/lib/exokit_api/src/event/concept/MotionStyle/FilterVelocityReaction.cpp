
#include "FilterSpeedReaction.h"

void FilterSpeedReaction::configure(ExoskeletonJointActiveHandle &joint, float minSpeed, float maxSpeed,
                                    ExoskeletonJointHandle::MovementDirection direction, float amplifyFlexPercentage,
                                    float resistFlexPercentage, float amplifyExtensionPercentage,
                                    float resistExtensionPercentage) {
    init();
    generator->configure(joint, minSpeed, maxSpeed, direction, amplifyFlexPercentage,
                         resistFlexPercentage, amplifyExtensionPercentage, resistExtensionPercentage);
}
