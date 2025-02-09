#ifndef CHI25_EXOSKELETON_API_MANUALCONDITIONSWITCHREACTION_H
#define CHI25_EXOSKELETON_API_MANUALCONDITIONSWITCHREACTION_H


#include "event/condition/ManualCondition.h"
#include "event/reaction/IReaction.h"

class ManualConditionSwitchReaction: public IReaction {
    ManualCondition* manualCondition{};
    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    ManualConditionSwitchReaction();
    void shutdown(bool isCancel) override;
    void configure(ManualCondition& manualCondition);

};


#endif //CHI25_EXOSKELETON_API_MANUALCONDITIONSWITCHREACTION_H
