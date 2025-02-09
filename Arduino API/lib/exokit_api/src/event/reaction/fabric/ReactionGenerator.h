#ifndef CHI25_EXOSKELETON_API_REACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_REACTIONGENERATOR_H


#include "event/reaction/ComposedReaction.h"

class ReactionGenerator {
public:
    virtual ~ReactionGenerator();
    virtual void reset();
    virtual ComposedReaction& init();

};


#endif //CHI25_EXOSKELETON_API_REACTIONGENERATOR_H
