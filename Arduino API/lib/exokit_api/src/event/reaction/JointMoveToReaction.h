#ifndef CHI25_EXOSKELETON_API_JOINTMOVETOREACTION_H
#define CHI25_EXOSKELETON_API_JOINTMOVETOREACTION_H


#include "IReaction.h"
#include "exo/PositionProvider.h"
#include "exo/ExoskeletonJointHandle.h"

enum TargetType {
    ABSOLUTE, RELATIVE_STARTING_POS, RELATIVE_CURRENT_POS
};

class JointMoveToReaction: public IReaction {
protected:
    TargetType targetType{};
    float configuredTargetAngle{};
    PositionProvider* positionProvider{};
    ExoskeletonJointHandle* c_joint{};
    float targetAngle{};
    float targetAngleTolerance{};

public:
    JointMoveToReaction();
    virtual bool isActiveJoint() = 0;
};


#endif //CHI25_EXOSKELETON_API_JOINTMOVETOREACTION_H
