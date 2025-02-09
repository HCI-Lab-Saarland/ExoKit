#include "Exoskeleton.h"

Exoskeleton::Exoskeleton(ActionBuilder &ab, ExoskeletonHandle &exo):
    leftArm(ab, exo.getLeftArm()), rightArm(ab, exo.getRightArm()) {}

ExoskeletonArm &Exoskeleton::getLeftArm() {
    return leftArm;
}

ExoskeletonArm &Exoskeleton::getRightArm() {
    return rightArm;
}
