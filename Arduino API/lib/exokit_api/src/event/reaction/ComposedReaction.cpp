#include "ComposedReaction.h"

#include <Arduino.h>

void ComposedReaction::runLoop() {
    unsigned long startTime = millis();
    unsigned long maxLoopRuntime = 100;
    while(!currentReaction->doRunLoop() && (startTime + maxLoopRuntime > millis())) {
        IReaction* next = currentReaction->findNextReaction();
        if(next != nullptr) {
            currentReaction = next;
            continue;
        } else {
            currentReaction = startingReaction;
            finished = true;
        }
    }
}

bool ComposedReaction::finishCondition() {
    return finished || this->startingReaction == nullptr;
}

void ComposedReaction::startup() {}

void ComposedReaction::prepare() {}

void ComposedReaction::shutdown(bool isCancel) {
    if(this->currentReaction != this->startingReaction || this->currentReaction->isStarted()) {
        this->currentReaction->shutdown(isCancel);
        this->currentReaction->findNextReaction();
        this->currentReaction = this->startingReaction;
    }
    finished = false;
}

void ComposedReaction::configure(IReaction* startingReaction) {
    ReactionConfigurationGuard configureGuard(*this);
    this->startingReaction = startingReaction;
    this->currentReaction = startingReaction;
}

ComposedReaction::ComposedReaction():
        IReaction(true) {}
