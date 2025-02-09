#ifndef CHI25_EXOSKELETON_API_PARALLELREACTION_H
#define CHI25_EXOSKELETON_API_PARALLELREACTION_H


#include "IReaction.h"

class PrPrepareStartupAction {
public:
    virtual ~PrPrepareStartupAction() = default;
    virtual void prepare() = 0;
};

class ParallelReaction: public IReaction {
private:
    IReaction *c_reaction1{};
    IReaction *c_currentReaction1{};
    IReaction *c_reaction2{};
    IReaction *c_currentReaction2{};
    PrPrepareStartupAction* prepareAction{};
    void runLoop() override;

protected:
    bool finishCondition() override;
    void prepare() override;

public:
    ParallelReaction();
    void configure(IReaction &, IReaction &, PrPrepareStartupAction* = nullptr);
    void shutdown(bool isCancel) override;
    void startup() override;
};


#endif //CHI25_EXOSKELETON_API_PARALLELREACTION_H
