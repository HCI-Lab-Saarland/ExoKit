
#ifndef SPEEDREACTION_H
#define SPEEDREACTION_H

#include "exo/ExoskeletonHandle.h"
#include "ICondition.h"

enum SpeedCompareType {
    FASTER_THAN, SLOWER_THAN, WITHIN
};

class SpeedCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint{nullptr};
    SpeedCompareType c_compareType{FASTER_THAN};
    float c_thresholdDegreePerSecond{0};
    float c_tolerance{0};
protected:
    bool evalCondition() override;
public:
    SpeedCondition();
    void configure(ExoskeletonJointHandle &joint, SpeedCompareType compareType, float thresholdDegreePerSecond,
                   float tolerance = 0);
    void restore() override;
};


#endif //SPEEDREACTION_H
