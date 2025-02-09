
#ifndef ISMOVINGCONDITION_H
#define ISMOVINGCONDITION_H

#include "exo/ExoskeletonHandle.h"
#include "ICondition.h"

class IsMovingCondition: public ICondition {
private:
    ExoskeletonJointHandle* c_joint{nullptr};
protected:
    bool evalCondition() override;
public:
    IsMovingCondition();
    void configure(ExoskeletonJointHandle& joint);
    void restore() override;
};

#endif //ISMOVINGCONDITION_H
