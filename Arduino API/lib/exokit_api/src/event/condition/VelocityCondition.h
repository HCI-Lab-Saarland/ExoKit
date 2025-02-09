
#ifndef CHI25_EXOSKELETON_API_VELOCITYCONDITION_H
#define CHI25_EXOSKELETON_API_VELOCITYCONDITION_H


#include "exo/ExoskeletonHandle.h"
#include "ICondition.h"
#include "SpeedCondition.h"


class VelocityCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint{nullptr};
    SpeedCompareType c_compareType{FASTER_THAN};
    float c_thresholdDegreePerSecond{0};
    float c_tolerance{0};
protected:
    bool evalCondition() override;
public:
    VelocityCondition();
    void configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float thresholdDegreePerSecond,
                   float tolerance = 0);
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_VELOCITYCONDITION_H
