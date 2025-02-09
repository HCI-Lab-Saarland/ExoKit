#include "CmdReactionRunner.h"
#include "event/condition/TrueCondition.h"
#include "util/DebugSerial.h"

CmdReactionRunner* CmdReactionRunner::instance{};

CmdReactionRunner &CmdReactionRunner::getInstance() {
    if(!instance) {
        instance = new CmdReactionRunner();
    }
    return *instance;
}

void CmdReactionRunner::launchReaction(IReaction &reaction) {
    cancelReaction();
    this->event = new Event();
    this->event->configure(trueCondition, reaction, nullptr, false);
    this->reaction = &reaction;
    this->event->enable(1);
}

bool CmdReactionRunner::cancelReaction() {
    if(!event) {
        return false;
    }
    event->cancel();

    delete event;
    event = nullptr;
    delete reaction;
    reaction = nullptr;
    return true;
}
