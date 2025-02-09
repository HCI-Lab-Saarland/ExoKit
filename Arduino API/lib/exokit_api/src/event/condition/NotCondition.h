#ifndef CHI25_EXOSKELETON_API_NOTCONDITION_H
#define CHI25_EXOSKELETON_API_NOTCONDITION_H


#include "ICondition.h"

class NotCondition: public ICondition {
private:
    ICondition* c_condition{nullptr};
protected:
    bool evalCondition() override;
public:
    NotCondition();
    void configure(ICondition& condition);
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_NOTCONDITION_H
