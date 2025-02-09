
#ifndef CHI25_EXOSKELETON_API_ATPOSITIONCONDITION_H
#define CHI25_EXOSKELETON_API_ATPOSITIONCONDITION_H


#include "ICondition.h"
#include "exo/ExoskeletonJointHandle.h"

enum CompareType {
    LOWER_THEN, HIGHER_EQUAL_THEN, EQUAL
};

class AtPositionCondition: public ICondition {
private:
    ExoskeletonJointHandle* joint{};
    CompareType compareType{};
    float angle{};
    float tolerance{};
protected:
    bool evalCondition() override;
public:
    explicit AtPositionCondition();
    void restore() override;
    void configure(ExoskeletonJointHandle &joint, CompareType compareType, float angle, float tolerance);
};


#endif //CHI25_EXOSKELETON_API_ATPOSITIONCONDITION_H
