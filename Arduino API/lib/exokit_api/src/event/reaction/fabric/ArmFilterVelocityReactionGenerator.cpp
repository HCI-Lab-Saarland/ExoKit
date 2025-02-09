
#include "ArmFilterSpeedReactionGenerator.h"

void ArmFilterSpeedReactionGenerator::configure(float minSpeed, float maxSpeed,
                                                ExoskeletonJointHandle::MovementDirection direction,
                                                float amplifyFlexPercentage, float resistFlexPercentage,
                                                float amplifyExtensionPercentage, float resistExtensionPercentage) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    int8_t jointCount = 0;
    if(jointGenerators[jointCount] && arm->getElbow().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getElbow()),
                                               minSpeed, maxSpeed, direction, amplifyFlexPercentage,
                                               resistFlexPercentage, amplifyExtensionPercentage,
                                               resistExtensionPercentage);
        jointCount++;
    }
    if(jointGenerators[jointCount] && arm->getShoulderBack().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderBack()),
                                               minSpeed, maxSpeed, direction, amplifyFlexPercentage,
                                               resistFlexPercentage, amplifyExtensionPercentage,
                                               resistExtensionPercentage);
        jointCount++;
    }
    if(jointGenerators[jointCount] && arm->getShoulderSide().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderSide()),
                                               minSpeed, maxSpeed, direction, amplifyFlexPercentage,
                                               resistFlexPercentage, amplifyExtensionPercentage,
                                               resistExtensionPercentage);
        jointCount++;
    }
    parallelize(jointCount);
}

ComposedReaction &ArmFilterSpeedReactionGenerator::initType(FilterSpeedReactionGenerator &type) {
    return type.init();
}
