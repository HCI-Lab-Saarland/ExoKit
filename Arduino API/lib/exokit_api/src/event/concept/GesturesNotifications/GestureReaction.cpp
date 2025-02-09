
#include "GestureReaction.h"

void GestureReaction::configure(ExoskeletonArmHandle &arm, GestureType gesture) {
    init();
    if (gesture == WAVE) {
        generator->configure(arm);
    }
}

