
#ifndef CHI25_EXOSKELETON_API_ISMOVINGTOWARDCONDITION_H
#define CHI25_EXOSKELETON_API_ISMOVINGTOWARDCONDITION_H

#include "exo/ExoskeletonHandle.h"
#include "ICondition.h"

class IsMovingTowardCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint;
    ExoskeletonJointHandle::MovementDirection c_direction;
    float c_thresholdVelocity;

protected:
    bool evalCondition() override;

public:
    IsMovingTowardCondition();
    void configure(ExoskeletonJointHandle& joint, ExoskeletonJointHandle::MovementDirection direction, float thresholdVelocity = 5);
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_ISMOVINGTOWARDCONDITION_H
