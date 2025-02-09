
#include "ConstrainToReaction.h"

void ConstrainToReaction::configure(ExoskeletonJointActiveHandle &joint, float angle, float radius) {
    init();
    generator->configure(joint, angle - radius, angle + radius);
}

