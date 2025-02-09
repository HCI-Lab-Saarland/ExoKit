
#include "TimeoutCondition.h"

#include <Arduino.h>

bool TimeoutCondition::evalCondition() {
    return (c_start_ms + c_wait_ms) <= millis();
}

TimeoutCondition::TimeoutCondition():
        ICondition(true) {}

void TimeoutCondition::configure(unsigned long wait_ms) {
    c_start_ms = millis();
    c_wait_ms = wait_ms;
    setConfigured();
}

bool TimeoutCondition::isTimer() {
    return true;
}

unsigned long TimeoutCondition::getTimeout() {
    return c_wait_ms;
}

void TimeoutCondition::restore()
{
    c_start_ms = millis();
}


