#ifndef ARMLOCKREACTIONGENERATOR_H
#define ARMLOCKREACTIONGENERATOR_H
#include <event/reaction/ComposedReaction.h>
#include <event/reaction/JointLockReaction.h>
#include <event/reaction/ParallelReaction.h>

class ArmLockReactionGenerator {
private:
    JointLockReaction* generatedReactions[3]={};
    ParallelReaction* pr1{};
    ParallelReaction* pr2{};
    ComposedReaction* composedReaction{};
    ExoskeletonJointHandle* joints[3] = {};
    uint8_t jointCount{};
    ExoskeletonArmHandle* arm{};
public:
    virtual ~ArmLockReactionGenerator();
    ComposedReaction &init(ExoskeletonArmHandle &exoArm);
    void configure();
    void reset();

};

#endif //ARMLOCKREACTIONGENERATOR_H
