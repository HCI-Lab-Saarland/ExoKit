

#ifndef ANDCONDITION_H
#define ANDCONDITION_H

#include "ICondition.h"

class AndCondition : public ICondition
{
private:
    ICondition* c_left;
    ICondition* c_right;

protected:
    bool evalCondition() override;
public:
    void configure(ICondition& left, ICondition& right);
    void restore() override;
};

#endif //ANDCONDITION_H
