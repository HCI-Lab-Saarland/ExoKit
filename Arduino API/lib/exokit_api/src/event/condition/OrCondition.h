
#ifndef ORCONDITION_H
#define ORCONDITION_H
#include "ICondition.h"

class OrCondition : public ICondition
{
private:
    ICondition* c_left{nullptr};
    ICondition* c_right{nullptr};
protected:
    bool evalCondition() override;
public:
    OrCondition();
    void configure(ICondition& left, ICondition& right);
    void restore() override;
};

#endif //ORCONDITION_H
