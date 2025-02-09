
#ifndef ATEXOARMANGLECONDITION_H
#define ATEXOARMANGLECONDITION_H

#include <model/ExoArmAngles.h>

#include "ICondition.h"
#include "exo/ExoskeletonJointHandle.h"

enum PoseCompareType {
    INSIDE, OUTSIDE
};

class AtExoArmAngleCondition: public ICondition {
private:
    ExoskeletonArmHandle* arm{};
    PoseCompareType compareType{};
    ExoArmAngles exoArmAngle;
    float tolerance{};
    unsigned long duration;
    unsigned long startTime;
protected:
    bool evalCondition() override;
public:
    explicit AtExoArmAngleCondition();
    void restore() override;
    void configure(ExoskeletonArmHandle &arm, ExoArmAngles exoArmAngle, float tolerance, unsigned long duration);
};


#endif //ATEXOARMANGLECONDITION_H
