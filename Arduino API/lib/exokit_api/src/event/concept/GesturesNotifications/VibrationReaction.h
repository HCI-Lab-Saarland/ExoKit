#ifndef CHI25_EXOSKELETON_API_VIBRATIONREACTION_H
#define CHI25_EXOSKELETON_API_VIBRATIONREACTION_H


#include "event/reaction/fabric/VibrationGenerator.h"
#include "event/concept/ReactionGeneratorWrapper.h"

class VibrationReaction: public ReactionGeneratorWrapper<VibrationGenerator> {
public:
    void configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude);

};


#endif //CHI25_EXOSKELETON_API_VIBRATIONREACTION_H
