
#ifndef CHI25_EXOSKELETON_API_AMPLIFYREACTION_H
#define CHI25_EXOSKELETON_API_AMPLIFYREACTION_H


#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/IReaction.h"

class AmplifyReaction: public IReaction {
    ExoskeletonJointActiveHandle* c_joint{};
    float c_amplifyPercentage{};
    bool initialTorqueState{};
    float initialCurrent{};
    ExoskeletonJointHandle::MovementDirection c_amplifyDirection{};
    OperatingMode initialOpMode{};
    float maxVelocity{};
    float startingVelocity{};
    unsigned long lastDirChange{};
    unsigned long lastTorqueEnable{};
    bool currentDirFlex{};
    bool initialMovement{true};
    unsigned long dirChangeSuspensionTime{400};

private:
    void runLoop() override;
protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;
public:
    void shutdown(bool isCancel) override;
    void configure(ExoskeletonJointActiveHandle& joint, float amplifyPercentage, ExoskeletonJointHandle::MovementDirection amplifyDirection = ExoskeletonJointHandle::MovementDirection::BOTH, float startingVelocity = 30, float maxVelocity = 0);

};


#endif //CHI25_EXOSKELETON_API_AMPLIFYREACTION_H
