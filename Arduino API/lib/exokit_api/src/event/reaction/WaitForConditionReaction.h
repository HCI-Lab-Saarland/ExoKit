#ifndef CHI25_EXOSKELETON_API_WAITFORCONDITIONREACTION_H
#define CHI25_EXOSKELETON_API_WAITFORCONDITIONREACTION_H


#include "IReaction.h"

class WaitForConditionReaction: public IReaction {
private:
    ICondition* c_waitCondition{};

    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    WaitForConditionReaction();
    void configure(ICondition& waitCondition);
    void shutdown(bool isCancel) override;


};


#endif //CHI25_EXOSKELETON_API_WAITFORCONDITIONREACTION_H
