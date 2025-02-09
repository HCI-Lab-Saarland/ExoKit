
#ifndef CHI25_EXOSKELETON_API_FALSECONDITION_H
#define CHI25_EXOSKELETON_API_FALSECONDITION_H


#include "ICondition.h"

class FalseCondition: public ICondition {
protected:
    bool evalCondition() override;
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_FALSECONDITION_H
