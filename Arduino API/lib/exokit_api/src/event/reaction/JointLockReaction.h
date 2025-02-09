#ifndef CHI25_EXOSKELETON_API_JOINTLOCKREACTION_H
#define CHI25_EXOSKELETON_API_JOINTLOCKREACTION_H


#include "IReaction.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "ManualConditionSwitchReaction.h"

class JointLockReaction: public IReaction {
private:
    ExoskeletonJointActiveHandle* c_joint{};
    ManualCondition unlockCondition;
    ManualConditionSwitchReaction unlockReaction;
    bool c_lockStateAtStartup{};
    OperatingMode c_lockOPatStartup{};
    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    void shutdown(bool isCancel) override;
    JointLockReaction();
    void configure(ExoskeletonJointActiveHandle& joint);

    ManualCondition& getUnlockCondition();
    ManualConditionSwitchReaction& getUnlockReaction();
};


#endif //CHI25_EXOSKELETON_API_JOINTLOCKREACTION_H
