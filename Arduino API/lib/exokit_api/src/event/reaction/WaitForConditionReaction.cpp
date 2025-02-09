#include "WaitForConditionReaction.h"

WaitForConditionReaction::WaitForConditionReaction():
    IReaction(true) {}

void WaitForConditionReaction::configure(ICondition &waitCondition) {
    ReactionConfigurationGuard configureGuard(*this);
    c_waitCondition = &waitCondition;
}

void WaitForConditionReaction::shutdown(bool isCancel) {
    c_waitCondition->restore();
}

void WaitForConditionReaction::startup() {}

void WaitForConditionReaction::runLoop() {}

bool WaitForConditionReaction::finishCondition() {
    return c_waitCondition->eval();
}

void WaitForConditionReaction::prepare() {}
