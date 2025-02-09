#ifndef IREACTION_H
#define IREACTION_H

#include "event/condition/ICondition.h"

class ReactionConfigurationGuard;

class IReaction {
    friend class ReactionConfigurationGuard;
private:
    ICondition* alternativeFinishCondition{};
    ICondition* ifThenCondition{};
    IReaction* ifThenTrueReaction{};
    IReaction* ifThenFalseReaction{};
    bool c_started{};
    bool c_prepared{};
    bool c_requiresConfigure;
    bool c_isConfigured;

    virtual void runLoop() = 0;
    void notifyFinish();
    bool evalFinishCondition();

protected:
    void setConfigured();
    virtual bool finishCondition() = 0;
    virtual void startup() = 0;
    virtual void prepare() = 0;

public:
    explicit IReaction(bool requiresConfigure = false);

    void startTimer();
    virtual void shutdown(bool isCancel) = 0;
    bool isStarted();
    void then(IReaction& reaction);
    virtual ~IReaction() = default;
    void ifThen(ICondition& condition, IReaction& reaction);
    void ifThenElse(ICondition& condition, IReaction& trueReaction, IReaction& falseReaction);
    bool isConfigured();
    void setAlternativeFinishCondition(ICondition* alternativeFinishCondition);

    //Only to by used by Event:
    bool doRunLoop();
    IReaction* findNextReaction();
    void notifyCancel();
};

class ReactionConfigurationGuard {
private:
    IReaction& reaction;
    bool wasStarted;
public:
    explicit ReactionConfigurationGuard(IReaction& reaction);
    ~ReactionConfigurationGuard();
};


#endif //IREACTION_H
