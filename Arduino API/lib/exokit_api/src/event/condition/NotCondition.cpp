#include "NotCondition.h"

void NotCondition::configure(ICondition &condition) {
    c_condition = &condition;
    setConfigured();
}

NotCondition::NotCondition():
        ICondition(true) {}

bool NotCondition::evalCondition() {
    return !c_condition->eval();
}

void NotCondition::restore() {
    c_condition->restore();
}
