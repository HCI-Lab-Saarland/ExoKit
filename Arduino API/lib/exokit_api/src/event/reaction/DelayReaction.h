#ifndef CHI25_EXOSKELETON_API_DELAYREACTION_H
#define CHI25_EXOSKELETON_API_DELAYREACTION_H


#include "IReaction.h"

class DelayReaction: public IReaction {
private:
    unsigned long c_start_ms;
    unsigned long c_wait_ms;
    void runLoop() override;

protected:
    bool finishCondition() override;
    void prepare() override;

public:
    DelayReaction();
    void configure(unsigned long wait_ms);
    void shutdown(bool isCancel) override;
    void startup() override;

};


#endif //CHI25_EXOSKELETON_API_DELAYREACTION_H
