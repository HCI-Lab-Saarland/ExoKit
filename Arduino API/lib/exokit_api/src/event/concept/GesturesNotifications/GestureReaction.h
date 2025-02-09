
#ifndef CHI25_EXOSKELETON_API_GESTUREWAVEREACTION_H
#define CHI25_EXOSKELETON_API_GESTUREWAVEREACTION_H


#include "event/reaction/fabric/GestureWaveGenerator.h"
#include "event/concept/ReactionGeneratorWrapper.h"
enum GestureType {
    WAVE
};


class GestureReaction: public ReactionGeneratorWrapper<GestureWaveGenerator> {
public:
    void configure(ExoskeletonArmHandle& arm, GestureType gesture);

};


#endif //CHI25_EXOSKELETON_API_GESTUREWAVEREACTION_H
