
#ifndef CHI25_EXOSKELETON_API_RESISTREACTION_H
#define CHI25_EXOSKELETON_API_RESISTREACTION_H


#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/IReaction.h"

class ResistReaction: public IReaction {
    ExoskeletonJointActiveHandle* joint{};
    float resistPercentageLinearGrowthLength{100};
    float resistancePercentage{};
    bool initialTorqueState{};
    float initialCurrent{};
    ExoskeletonJointHandle::MovementDirection resistDirection{};
    OperatingMode initialOpMode{};
    bool currentDirFlex{};
    bool initialMovement{true};
    float minVelocity{};

private:
    void runLoop() override;
protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;
public:
    void shutdown(bool isCancel) override;
    void configure(ExoskeletonJointActiveHandle &joint, float resistancePercentage, ExoskeletonJointHandle::MovementDirection resistDirection = ExoskeletonJointHandle::MovementDirection::BOTH, float minVelocity = 0);



};


#endif //CHI25_EXOSKELETON_API_RESISTREACTION_H
