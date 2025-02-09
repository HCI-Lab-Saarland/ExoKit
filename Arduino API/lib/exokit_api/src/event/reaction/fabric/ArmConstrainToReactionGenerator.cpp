
#include "ArmConstrainToReactionGenerator.h"

ComposedReaction& ArmConstrainToReactionGenerator::initType(ConstrainToReactionGenerator &type) {
    return type.init();
}


void ArmConstrainToReactionGenerator::configure(ExoArmAngles pos, float radius) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    int8_t jointCount = 0;
    if(jointGenerators[jointCount] && pos.isHasElbow() && arm->getElbow().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getElbow()),
                                               pos.getElbowAngle() - radius,
                                               pos.getElbowAngle() + radius);
        jointCount++;
    }
    if(jointGenerators[jointCount] && pos.isHasShoulderBack() && arm->getShoulderBack().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderBack()),
                                               pos.getShoulderBackAngle() - radius,
                                               pos.getShoulderBackAngle() + radius);
        jointCount++;
    }
    if(jointGenerators[jointCount] && pos.isHasShoulderSide() && arm->getShoulderSide().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderSide()),
                                               pos.getShoulderSideAngle() - radius,
                                               pos.getShoulderSideAngle() + radius);
        jointCount++;
    }
    parallelize(jointCount);
}

