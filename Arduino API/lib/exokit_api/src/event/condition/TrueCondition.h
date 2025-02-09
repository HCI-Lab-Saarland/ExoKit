
#ifndef CHI25_EXOSKELETON_API_TRUECONDITION_H
#define CHI25_EXOSKELETON_API_TRUECONDITION_H


#include "ICondition.h"

class TrueCondition : public ICondition {
protected:
    bool evalCondition() override;
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_TRUECONDITION_H
