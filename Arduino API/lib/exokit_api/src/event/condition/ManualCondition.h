
#ifndef CHI25_EXOSKELETON_API_MANUALCONDITION_H
#define CHI25_EXOSKELETON_API_MANUALCONDITION_H


#include "ICondition.h"

class ManualCondition: public ICondition {
private:
    bool state{false};
    bool unfulfillOnRestore{true};
    bool armOnFirstEval{false};
    bool armed{false};
protected:
    bool evalCondition() override;
public:
    explicit ManualCondition();
    void setFulfilled();
    void configure(bool unfulfillOnRestore = true, bool armOnFirstEval = false);
    bool getFulfilled() const;
    void restore() override;
};


#endif //CHI25_EXOSKELETON_API_MANUALCONDITION_H
