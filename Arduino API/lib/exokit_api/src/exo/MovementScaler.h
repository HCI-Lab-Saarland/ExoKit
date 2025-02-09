#ifndef CHI25_EXOSKELETON_API_MOVEMENTSCALER_H
#define CHI25_EXOSKELETON_API_MOVEMENTSCALER_H


#include "PositionProvider.h"

class MovementScaler: public PositionProvider {
private:
    PositionProvider* source;
    float scaleFactor;
public:
    virtual ~MovementScaler() = default;

    /**
     * Configures the MovementScaler with a source position provider and a scale factor.
     * @param source The position provider from which the angle position will be fetched.
     * @param scaleFactor The factor by which to scale the position.
     */
    void configure(PositionProvider& source, float scaleFactor);

    /**
     * Retrieves the scaled position from the source position provider.
     * Multiplies the source's position by the scale factor.
     * @return The scaled position based on the scale factor.
     */
    float getPosition() override;
};


#endif //CHI25_EXOSKELETON_API_MOVEMENTSCALER_H
