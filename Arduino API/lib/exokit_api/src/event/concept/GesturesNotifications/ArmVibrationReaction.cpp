
#include "ArmVibrationReaction.h"

void ArmVibrationReaction::configure(ExoskeletonArmHandle &exoarm, uint8_t frequency, float amplitude) {
    this->newInitArm = &exoarm;
    this->init();
    this->generator->configure(frequency, amplitude);
}
