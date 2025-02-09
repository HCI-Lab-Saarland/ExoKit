#include "MovementScaler.h"

float MovementScaler::getPosition() {
    return scaleFactor * source->getPosition();
}

void MovementScaler::configure(PositionProvider &source, float scaleFactor) {
    this->source = &source;
    this->scaleFactor = scaleFactor;
}
