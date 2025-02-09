#ifndef CHI25_EXOSKELETON_API_COMPOSEDREACTION_H
#define CHI25_EXOSKELETON_API_COMPOSEDREACTION_H


#include "IReaction.h"

class ComposedReaction: public IReaction {
private:
    bool finished{false};
    IReaction* startingReaction;
    IReaction* currentReaction;
    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    ComposedReaction();
    void shutdown(bool isCancel) override;
    void configure(IReaction* startingReaction);


};


#endif //CHI25_EXOSKELETON_API_COMPOSEDREACTION_H
