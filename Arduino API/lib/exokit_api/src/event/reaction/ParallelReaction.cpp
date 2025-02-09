#include <WString.h>
#include <Arduino.h>
#include "ParallelReaction.h"
#include "util/DebugSerial.h"

void ParallelReaction::runLoop() {

    unsigned long startTime = millis();
    unsigned long maxLoopRuntime = (!c_currentReaction1 || !c_currentReaction2) ? 100 : 50;
    while(c_currentReaction1 != nullptr && !c_currentReaction1->doRunLoop() && (startTime + maxLoopRuntime > millis())) {
        IReaction* next = c_currentReaction1->findNextReaction();
        c_currentReaction1 = next;
    }

    startTime = millis();
    while (c_currentReaction2 != nullptr && !c_currentReaction2->doRunLoop() && (startTime + maxLoopRuntime > millis())) {
        IReaction* next = c_currentReaction2->findNextReaction();
        c_currentReaction2 = next;
    }

}

void ParallelReaction::shutdown(bool isCancel) {
    if(c_currentReaction1 != nullptr) {
        c_currentReaction1->shutdown(isCancel);
    }
    if(c_currentReaction2 != nullptr) {
        c_currentReaction2->shutdown(isCancel);
    }
    c_currentReaction1 = c_reaction1;
    c_currentReaction2 = c_reaction2;
}

bool ParallelReaction::finishCondition() {
    return c_currentReaction1 == nullptr && c_currentReaction2 == nullptr;
}

void ParallelReaction::startup() {}

ParallelReaction::ParallelReaction():
    IReaction(true) {}

void ParallelReaction::configure(IReaction &reaction1, IReaction &reaction2, PrPrepareStartupAction* prepareStartupAction) {
    ReactionConfigurationGuard configureGuard(*this);
    c_reaction1 = &reaction1;
    c_reaction2 = &reaction2;
    c_currentReaction1 = &reaction1;
    c_currentReaction2 = &reaction2;
    prepareAction = prepareStartupAction;
}

void ParallelReaction::prepare() {
    if(prepareAction) {
        prepareAction->prepare();
    }
}
