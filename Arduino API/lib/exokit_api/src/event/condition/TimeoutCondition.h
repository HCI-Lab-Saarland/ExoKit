
#ifndef TIMEOUTCONDITION_H
#define TIMEOUTCONDITION_H
#include "ICondition.h"

class TimeoutCondition: public ICondition {
private:
    unsigned long c_start_ms;
    unsigned long c_wait_ms;
protected:
    bool evalCondition() override;
public:
    TimeoutCondition();
    void configure(unsigned long wait_ms);
    void restore() override;
    bool isTimer() override;
    unsigned long getTimeout() override;
};

#endif //TIMEOUTCONDITION_H
