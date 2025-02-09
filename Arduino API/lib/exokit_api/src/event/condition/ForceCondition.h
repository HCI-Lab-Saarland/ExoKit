
#ifndef FORCECONDITION_H
#define FORCECONDITION_H
#include <exo/ExoskeletonJointHandle.h>

#include "ICondition.h"


class ForceCondition: public ICondition {
public:
    enum ForceCompareType {
        STRONGER_THAN, WEAKER_THAN, WITHIN
    };
    ForceCondition();
    void configure(ExoskeletonJointHandle& joint, float force, ForceCompareType compareType, float tolerance = 0);
    void restore() override;
    unsigned long last_print;
    float prior_measurement;
private:
    ExoskeletonJointHandle* c_joint{nullptr};
    ForceCompareType c_compareType{STRONGER_THAN};
    float c_force{0};
    float c_tolerance{0};
protected:
    bool evalCondition() override;
};
#endif //FORCECONDITION_H
