#include "DelayReaction.h"
#include "Arduino.h"

void DelayReaction::runLoop() {}

void DelayReaction::shutdown(bool isCancel) {
    c_start_ms = 0;
}

bool DelayReaction::finishCondition() {
    return isStarted() && (c_start_ms + c_wait_ms) <= millis();
}

void DelayReaction::startup() {
    c_start_ms = millis();
}

DelayReaction::DelayReaction():
        IReaction(true) {}

void DelayReaction::configure(unsigned long wait_ms) {
    ReactionConfigurationGuard configureGuard(*this);
    c_wait_ms = wait_ms;
}

void DelayReaction::prepare() {}
