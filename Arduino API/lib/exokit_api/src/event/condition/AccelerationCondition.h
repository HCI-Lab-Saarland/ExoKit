
#ifndef ACCELERATIONCONDITION_H
#define ACCELERATIONCONDITION_H
#include <exo/ExoskeletonJointHandle.h>

#include "ICondition.h"
#include "SpeedCondition.h"

class AccelerationCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint{nullptr};
    SpeedCompareType c_compareType{FASTER_THAN};
    float c_prior_velocity{0};
    unsigned long c_millis_start{0};
    float c_acceleration{0};
    float c_tolerance{0};
protected:
    bool evalCondition() override;
public:
    AccelerationCondition();
    void configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float acceleration, float tolerance = 0);
    void restore() override;
};


#endif //ACCELERATIONCONDITION_H
