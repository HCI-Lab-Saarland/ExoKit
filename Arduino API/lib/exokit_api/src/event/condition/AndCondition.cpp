
#include "AndCondition.h"

bool AndCondition::evalCondition() {
    return c_left->eval() && c_right->eval();
}

void AndCondition::configure(ICondition &left, ICondition &right) {
    c_left = &left;
    c_right = &right;
    setConfigured();
}

void AndCondition::restore() {
    c_left->restore();
    c_right->restore();
}
