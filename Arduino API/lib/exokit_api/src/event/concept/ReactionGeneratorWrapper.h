
#ifndef CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPER_H
#define CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPER_H

#include "ReactionGeneratorWrapperBase.h"


template<typename GeneratorType>
class ReactionGeneratorWrapper: public ReactionGeneratorWrapperBase<GeneratorType> {

private:
    ComposedReaction& callInit() override;

};

template<typename GeneratorType>
ComposedReaction &ReactionGeneratorWrapper<GeneratorType>::callInit() {
    return this->generator->init();
}


#endif //CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPER_H
