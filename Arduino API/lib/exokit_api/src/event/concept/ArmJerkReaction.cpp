
#include "ArmJerkReaction.h"

void ArmJerkReaction::configure(ExoskeletonArmHandle &exoArm, float minJerkAngle, float maxJerkAngle, long minJerkInterval,
                                long maxJerkInterval, float maxAccumulatedMovementsLeft,
                                float maxAccumulatedMovementsRight,
                                float velocity, unsigned long nr_jerks) {
    this->newInitArm = &exoArm;
    this->init();
    generator->configure(minJerkAngle, maxJerkAngle, minJerkInterval,
                         maxJerkInterval, maxAccumulatedMovementsLeft,
                         maxAccumulatedMovementsRight, velocity, nr_jerks);
}

