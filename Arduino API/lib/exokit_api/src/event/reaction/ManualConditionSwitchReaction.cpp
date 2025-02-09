#include "ManualConditionSwitchReaction.h"

void ManualConditionSwitchReaction::startup() {
    manualCondition->setFulfilled();
}

void ManualConditionSwitchReaction::prepare() {

}

bool ManualConditionSwitchReaction::finishCondition() {
    return manualCondition->getFulfilled();
}

void ManualConditionSwitchReaction::runLoop() {

}

void ManualConditionSwitchReaction::shutdown(bool isCancel) {

}

ManualConditionSwitchReaction::ManualConditionSwitchReaction():
    IReaction(true) {}

void ManualConditionSwitchReaction::configure(ManualCondition &manualCondition) {
    ReactionConfigurationGuard guard(*this);
    this->manualCondition = &manualCondition;
}
