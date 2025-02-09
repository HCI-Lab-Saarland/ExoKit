#ifndef CHI25_EXOSKELETON_API_ACTIVEJOINTMOVETOREACTION_H
#define CHI25_EXOSKELETON_API_ACTIVEJOINTMOVETOREACTION_H


#include "IReaction.h"
#include "JointMoveToReaction.h"
#include "exo/ExoskeletonJointActiveHandle.h"

class ActiveJointMoveToReaction: public JointMoveToReaction {
private:
    bool c_initialTorqueState{false};
    float c_initialVelocityProfile{};
    OperatingMode c_initialJointMode{};
    float velocity{};
    void runLoop() override;

protected:
    void startup() override;
    void prepare() override;

public:
    void configure(ExoskeletonJointActiveHandle& joint, float goalAngle, float velocity, float goalAngleTolerance = 5, TargetType targetType = ABSOLUTE);
    void configure(ExoskeletonJointActiveHandle& joint, PositionProvider& followPosition, float velocity);
    void shutdown(bool isCancel) override;
    bool isActiveJoint() override;
    bool finishCondition() override;
};


#endif //CHI25_EXOSKELETON_API_ACTIVEJOINTMOVETOREACTION_H
