
#ifndef CHI25_EXOSKELETON_API_ARMCOMPOSEDREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMCOMPOSEDREACTIONGENERATOR_H


#include "event/reaction/ComposedReaction.h"
#include "event/reaction/ParallelReaction.h"
#include "exo/ExoskeletonArmHandle.h"

template<typename T>
class ArmComposedReactionGenerator {
protected:
    T* jointGenerators[3]{};
    ComposedReaction* generatedReactions[3]{};
    ComposedReaction* composedReaction{};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ExoskeletonArmHandle* arm{};
    virtual ComposedReaction& initType(T& type) = 0;
    virtual void parallelize(int8_t jointCount);
    
public:
    virtual ~ArmComposedReactionGenerator();
    virtual void reset();
    virtual ComposedReaction& init(ExoskeletonArmHandle &exoArm);
};

template<typename T>
ArmComposedReactionGenerator<T>::~ArmComposedReactionGenerator() {
    reset();
}

template<typename T>
void ArmComposedReactionGenerator<T>::parallelize(int8_t jointCount) {
    switch (jointCount) {
        case 1:
            composedReaction->configure(generatedReactions[0]);
            break;
        case 2:
            pr1->configure(*generatedReactions[0], *generatedReactions[1]);
            composedReaction->configure(pr1);
            break;
        case 3:
            pr2->configure(*generatedReactions[1], *generatedReactions[2]);
            pr1->configure(*pr2, *generatedReactions[0]);
            composedReaction->configure(pr1);
            break;
        default:
            composedReaction->configure(nullptr);
            break;
    }
}

template<typename T>
void ArmComposedReactionGenerator<T>::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    for(auto & it : jointGenerators) {
        delete it;
        it = nullptr;
    }
    for(auto & it : generatedReactions) {
        it = nullptr;
    }
    delete pr1;
    pr1 = nullptr;
    delete pr2;
    pr2 = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

template<typename T>
ComposedReaction &ArmComposedReactionGenerator<T>::init(ExoskeletonArmHandle &exoArm) {
    reset();
    arm = &exoArm;
    int8_t jointCount = 0;
    if(arm->getElbow().isActive()) {
        jointGenerators[jointCount] = new T();
        generatedReactions[jointCount] = &initType(*jointGenerators[jointCount]);
        jointCount++;
    }
    if(arm->getShoulderSide().isActive()) {
        jointGenerators[jointCount] = new T();
        generatedReactions[jointCount] = &initType(*jointGenerators[jointCount]);
        jointCount++;
    }
    if(arm->getShoulderBack().isActive()) {
        jointGenerators[jointCount] = new T();
        generatedReactions[jointCount] = &initType(*jointGenerators[jointCount]);
        jointCount++;
    }
    composedReaction = new ComposedReaction();
    pr1 = new ParallelReaction();
    pr2 = new ParallelReaction();
    return *composedReaction;
}


#endif //CHI25_EXOSKELETON_API_ARMCOMPOSEDREACTIONGENERATOR_H
