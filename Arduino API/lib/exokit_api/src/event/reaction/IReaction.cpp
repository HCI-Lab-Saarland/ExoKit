#include "IReaction.h"

#include <event/condition/TimeoutCondition.h>

#include "util/DebugSerial.h"

IReaction::IReaction(bool requiresConfigure):
        c_started{false}, c_requiresConfigure{requiresConfigure}, c_isConfigured{false} {}

void IReaction::then(IReaction &reaction) {
    ifThenCondition = nullptr;
    ifThenTrueReaction = &reaction;
    ifThenFalseReaction = nullptr;
}

void IReaction::ifThen(ICondition &condition, IReaction &reaction) {
    ifThenCondition = &condition;
    ifThenTrueReaction = &reaction;
}

void IReaction::ifThenElse(ICondition &condition, IReaction &trueReaction, IReaction &falseReaction) {
    ifThenCondition = &condition;
    ifThenTrueReaction = &trueReaction;
    ifThenFalseReaction = &falseReaction;
}

void IReaction::notifyFinish() {
    shutdown(false);
    c_started = false;
    c_prepared = false;
}

void IReaction::notifyCancel() {
    shutdown(true);
    c_started = false;
    c_prepared = false;
}

IReaction* IReaction::findNextReaction() {
    IReaction* reaction = nullptr;
    if(ifThenCondition != nullptr) {
        if(ifThenCondition->eval()) {
            ifThenCondition->restore();
            reaction = ifThenTrueReaction;
        } else {
            ifThenCondition->restore();
            reaction = ifThenFalseReaction;
        }
    } else if (ifThenTrueReaction != nullptr) {
        reaction = ifThenTrueReaction;
    }
    if(alternativeFinishCondition) {
        alternativeFinishCondition->restore();
    }
    return reaction;
}

bool IReaction::doRunLoop() {
    if(!isConfigured()) {
        return false;
    }
    if(!c_prepared) {
        this->startTimer();
        prepare();
        c_prepared = true;
    }
    if(evalFinishCondition()) {
        notifyFinish();
        return false;
    }
    if(!c_started) {
        startup();
        c_started = true;
    }
    runLoop();
    return true;
}


bool IReaction::isStarted() {
    return c_started;
}

void IReaction::setConfigured() {
    c_isConfigured = true;
}

bool IReaction::isConfigured() {
    if(!c_requiresConfigure) {
        return true;
    }
    return c_isConfigured;
}

void IReaction::startTimer() {
    if (alternativeFinishCondition != nullptr) {
        if (alternativeFinishCondition->isTimer()) {
            alternativeFinishCondition->restore();
        }
    }
}

void IReaction::setAlternativeFinishCondition(ICondition* alternativeFinishCondition) {
    this->alternativeFinishCondition = alternativeFinishCondition;
}

bool IReaction::evalFinishCondition() {
    if(alternativeFinishCondition && alternativeFinishCondition->eval()) {
        return true;
    }

    return finishCondition();
}

ReactionConfigurationGuard::ReactionConfigurationGuard(IReaction &reaction):
    reaction(reaction), wasStarted(reaction.isStarted()) {
    if (wasStarted) {
        reaction.shutdown(true);
        reaction.c_started = false;
        reaction.c_prepared = false;
    }
}

ReactionConfigurationGuard::~ReactionConfigurationGuard() {
    reaction.setConfigured();
    /*if(wasStarted) {
        reaction.prepare();
        reaction.c_prepared = true;
        reaction.startup();
        reaction.c_started = true;
    }*/
}


