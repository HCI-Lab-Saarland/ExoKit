
#include "ArmMirrorReaction.h"

void ArmMirrorReaction::configure(ExoskeletonArmHandle &exoArmTarget, ExoskeletonArmHandle &exoArmSource, bool mirrorElbow,
                                  bool mirrorShoulderSide, bool mirrorShoulderBack, float scaleFactorElbow,
                                  float scaleFactorShoulderSide, float scaleFactorShoulderBack) {
    this->newInitArm = &exoArmTarget;
    this->init();
    generator->configure(exoArmSource, mirrorElbow,
                         mirrorShoulderSide, mirrorShoulderBack, scaleFactorElbow,
                         scaleFactorShoulderSide, scaleFactorShoulderBack);

}
