#ifndef CHI25_EXOSKELETON_API_ARMMOVETOREACTIONGENERATOR_H
#define CHI25_EXOSKELETON_API_ARMMOVETOREACTIONGENERATOR_H


#include <new>
#include "event/reaction/IReaction.h"
#include "exo/ExoskeletonHandle.h"
#include "event/reaction/ParallelReaction.h"
#include "model/ExoArmAngles.h"
#include "event/reaction/JointMoveToReaction.h"
#include "event/reaction/ComposedReaction.h"
#include "event/reaction/PassiveJointMoveToReaction.h"

class ArmMoveToReactionPreparer: public PrPrepareStartupAction {
private:
    size_t jointCount{};
    int32_t maxVelocity{};
    JointMoveToReaction* jointReactions[3]{};
    ExoskeletonJointHandle* joints[3]{};
    size_t jointIndexes[3]{};
    float angles[3]{};
public:
    ArmMoveToReactionPreparer() = default;
    void configure(JointMoveToReaction** jointReactions, ExoskeletonJointHandle** joints, float* angles, float maxVelocity,
                   uint8_t jointCount, size_t* jointIndexes);
    void prepare() override;
};

class ArmMoveToReactionGenerator {
private:
    JointMoveToReaction* jointReactions[3]={};
    ParallelReaction* prInner{};
    ParallelReaction* prOuter{};
    ArmMoveToReactionPreparer* preparer{};
    ComposedReaction* composedReaction{};
    ExoskeletonJointHandle* joints[3] = {};
    uint8_t jointCount{};


public:
    ArmMoveToReactionGenerator();
    virtual ~ArmMoveToReactionGenerator();
    ComposedReaction &init(ExoskeletonArmHandle &exoArm);
    void configure(ExoArmAngles pos, float maxVelocity);
    ComposedReaction& generateReaction();
    void reset();

};

#endif //CHI25_EXOSKELETON_API_ARMMOVETOREACTIONGENERATOR_H
