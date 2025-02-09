
#include "VibrationReaction.h"

void VibrationReaction::configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude) {
    init();
    generator->configure(joint, frequency, amplitude);
}
