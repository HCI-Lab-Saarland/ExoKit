
#ifndef CHI25_EXOSKELETON_API_ARMREACTIONGENERATORWRAPPER_H
#define CHI25_EXOSKELETON_API_ARMREACTIONGENERATORWRAPPER_H

#include "exo/ExoskeletonArmHandle.h"
#include "ReactionGeneratorWrapperBase.h"


template<typename GeneratorType>
class ArmReactionGeneratorWrapper: public ReactionGeneratorWrapperBase<GeneratorType> {
private:
    ComposedReaction& callInit() override;
protected:
    ExoskeletonArmHandle* arm{};
    ExoskeletonArmHandle* newInitArm{};
    void init() override;

};

template<typename GeneratorType>
ComposedReaction &ArmReactionGeneratorWrapper<GeneratorType>::callInit() {
    return this->generator->init(*this->newInitArm);
}

template<typename GeneratorType>
void ArmReactionGeneratorWrapper<GeneratorType>::init() {
    if(this->composedReaction == nullptr || (this->arm != this->newInitArm && this->newInitArm)) {
        this->generator->reset();
        this->composedReaction = &this->callInit();
        this->arm = this->newInitArm;
    }
}




#endif //CHI25_EXOSKELETON_API_ARMREACTIONGENERATORWRAPPER_H
