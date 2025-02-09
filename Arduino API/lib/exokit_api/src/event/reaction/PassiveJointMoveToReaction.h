#ifndef CHI25_EXOSKELETON_API_PASSIVEJOINTMOVETOREACTION_H
#define CHI25_EXOSKELETON_API_PASSIVEJOINTMOVETOREACTION_H


#include "IReaction.h"
#include "ActiveJointMoveToReaction.h"
#include "exo/ExoskeletonJointPassiveHandle.h"

class PassiveJointMoveToReaction: public JointMoveToReaction {
private:
    void runLoop() override;
protected:
    void startup() override;
    void prepare() override;

public:
    void shutdown(bool isCancel) override;
    void configure(ExoskeletonJointPassiveHandle& joint, float targetAngle, float tolerance = 5, TargetType targetType = ABSOLUTE);
    bool isActiveJoint() override;
    bool finishCondition() override;

};


#endif //CHI25_EXOSKELETON_API_PASSIVEJOINTMOVETOREACTION_H
