
#include "ArmGuideAwayReactionGenerator.h"

void ArmGuideAwayReactionGenerator::configure(ExoArmAngles pos, float radius, float amplifyPercentage,
                                              float resistPercentage) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    int8_t jointCount = 0;
    if(jointGenerators[jointCount] && pos.isHasElbow() && arm->getElbow().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getElbow()),
                                               pos.getElbowAngle() - radius,
                                               pos.getElbowAngle() + radius,
                                               amplifyPercentage, resistPercentage);
        jointCount++;
    }
    if(jointGenerators[jointCount] && pos.isHasShoulderBack() && arm->getShoulderBack().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderBack()),
                                               pos.getShoulderBackAngle() - radius,
                                               pos.getShoulderBackAngle() + radius,
                                               amplifyPercentage, resistPercentage);
        jointCount++;
    }
    if(jointGenerators[jointCount] && pos.isHasShoulderSide() && arm->getShoulderSide().isActive()) {
        jointGenerators[jointCount]->configure(static_cast<ExoskeletonJointActiveHandle &>(arm->getShoulderSide()),
                                               pos.getShoulderSideAngle() - radius,
                                               pos.getShoulderSideAngle() + radius,
                                               amplifyPercentage, resistPercentage);
        jointCount++;
    }
    parallelize(jointCount);
}

ComposedReaction &ArmGuideAwayReactionGenerator::initType(GuideAwayReactionGenerator &type) {
    return type.init();
}
