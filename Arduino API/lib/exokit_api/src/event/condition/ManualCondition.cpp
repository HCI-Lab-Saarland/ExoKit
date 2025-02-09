#include "ManualCondition.h"

bool ManualCondition::getFulfilled() const {
    return state;
}

bool ManualCondition::evalCondition() {
    if(armOnFirstEval && !armed) {
        armed = true;
    }
    return state;
}

void ManualCondition::setFulfilled() {
    if(armOnFirstEval && !armed) {
        return;
    }
    state = true;
}

void ManualCondition::restore() {
    if(unfulfillOnRestore) {
        state = false;
        armed = false;
    }
}

ManualCondition::ManualCondition():
    ICondition(true) {}

void ManualCondition::configure(bool unfulfillOnRestore, bool armOnFirstEval) {
    this->unfulfillOnRestore = unfulfillOnRestore;
    this->armOnFirstEval = armOnFirstEval;
    setConfigured();
}



