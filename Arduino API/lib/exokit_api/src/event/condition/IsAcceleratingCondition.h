
#ifndef ISACCELERATING_H
#define ISACCELERATING_H

#include "ICondition.h"
#include "exo/ExoskeletonHandle.h"

class IsAcceleratingCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint{nullptr};
    float c_accelerationThreshold;
    unsigned long c_prior_velocity;
    unsigned long c_millis_start;
protected:
    bool evalCondition() override;
public:
    IsAcceleratingCondition();
    void configure(ExoskeletonJointHandle& joint, float accelerationThreshold = 1);
    void restore() override;
};
#endif //ISACCELERATING_H
