
#include "GuideTowardsReaction.h"

void GuideTowardsReaction::configure(ExoskeletonJointActiveHandle &joint, float angle, float radius, float amplifyPercentage,
                                     float resistPercentage) {
    init();
    generator->configure(joint, angle - radius, angle + radius, amplifyPercentage, resistPercentage);
}
