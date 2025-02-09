#ifndef CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPERBASE_H
#define CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPERBASE_H


#include "event/reaction/fabric/ReactionGenerator.h"

template<typename GeneratorType>
class ReactionGeneratorWrapperBase: public IReaction {
private:
    virtual ComposedReaction& callInit() = 0;
protected:
    GeneratorType* generator{};
    ComposedReaction* composedReaction{};
    bool finished{false};
    void runLoop() override;

protected:
    bool finishCondition() override;
    virtual void init();
    void startup() override;
    void prepare() override;

public:
    ReactionGeneratorWrapperBase();
    ~ReactionGeneratorWrapperBase() override;
    void shutdown(bool isCancel) override;

};

template<typename GeneratorType>
ReactionGeneratorWrapperBase<GeneratorType>::~ReactionGeneratorWrapperBase() {
    delete generator;
}

template<typename GeneratorType>
void ReactionGeneratorWrapperBase<GeneratorType>::init() {
    if(composedReaction == nullptr) {
        composedReaction = &callInit();
    }
}

template<typename GeneratorType>
ReactionGeneratorWrapperBase<GeneratorType>::ReactionGeneratorWrapperBase() {
    generator = new GeneratorType();
}


template<typename GeneratorType>
void ReactionGeneratorWrapperBase<GeneratorType>::prepare() {

}

template<typename GeneratorType>
bool ReactionGeneratorWrapperBase<GeneratorType>::finishCondition() {
    return finished;
}

template<typename GeneratorType>
void ReactionGeneratorWrapperBase<GeneratorType>::startup() {}

template<typename GeneratorType>
void ReactionGeneratorWrapperBase<GeneratorType>::shutdown(bool isCancel) {
    composedReaction->shutdown(isCancel);
    finished = false;
}

template<typename GeneratorType>
void ReactionGeneratorWrapperBase<GeneratorType>::runLoop() {
    finished = !composedReaction->doRunLoop();
}


#endif //CHI25_EXOSKELETON_API_REACTIONGENERATORWRAPPERBASE_H
