#ifndef CHI25_EXOSKELETON_API_EXOSKELETON_H
#define CHI25_EXOSKELETON_API_EXOSKELETON_H


#include "exo/ExoskeletonHandle.h"
#include "ExoskeletonArm.h"
#include "event/Event.h"
#include "ActionBuilder.h"

class Exoskeleton {
    ExoskeletonArm leftArm;
    ExoskeletonArm rightArm;


public:
    /**
     * Creates an Exoskeleton instance, that provides a user-friendly way to program reactions and conditions.
     * @param ab An ActionBuilder object that should be used the handle the created actions and conditions.
     * @param exo An ExoskeletonHandle that can be obtained from the ExoskeletonBuilder.
     */
    Exoskeleton(ActionBuilder& ab, ExoskeletonHandle& exo);

    /**
     * @return The left arm of the exoskeleton
     */
    ExoskeletonArm& getLeftArm();

    /**
     * @return The right arm of the exoskeleton.
     */
    ExoskeletonArm& getRightArm();
};


#endif //CHI25_EXOSKELETON_API_EXOSKELETON_H
