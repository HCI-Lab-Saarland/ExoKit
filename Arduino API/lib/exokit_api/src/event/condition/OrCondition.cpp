#include "OrCondition.h"

OrCondition::OrCondition():
        ICondition(true) {}

bool OrCondition::evalCondition()
{
    return c_left->eval() || c_right->eval();
}

void OrCondition::configure(ICondition &left, ICondition &right) {
    c_left = &left;
    c_right = &right;
    setConfigured();
}

void OrCondition::restore() {
    c_left->restore();
    c_right->restore();
}
