#include "Event.h"

#include <util/DebugSerial.h>

#include "condition/TimeoutCondition.h"

void Event::exec() {
    switch (c_state) {
        case DISABLED:
            return;
        case LISTENING:
            if(c_condition->eval()) {
                c_condition->restore();

                // start timer for timeout condition upon start of the event
                if (c_cancelCondition != nullptr)
                {
                    if(c_cancelCondition->isTimer()) {
                        c_cancelCondition->restore();
                    }
                }
                c_state = RUNNING;
                exec();
            }
            return;
        case RUNNING:
            performRunning();
            return;
        case CANCELLED:
            return;
        case FINISHED:
            return;
        case UNCONFIGURED:
            return;
    }
}

bool Event::enable(uint32_t loopInterval) {
    if(c_state != DISABLED) {
        return false;
    }
    c_taskId = taskManager.schedule(repeatMillis(loopInterval), this);
    c_state = EventState::LISTENING;
    return true;
}

void Event::performRunning () {
    if(c_state != RUNNING) {
        return;
    }
    if(c_cancelCondition != nullptr && c_cancelCondition->eval()) {
        c_cancelCondition->restore();
        cancel();
        return;
    }
    unsigned long startTime = millis();
    unsigned long maxLoopRuntime = 100;
    while(!c_currentReaction->doRunLoop() && (startTime + maxLoopRuntime > millis())) {
        IReaction* next = c_currentReaction->findNextReaction();
        if(next != nullptr) {
            c_currentReaction = next;
            continue;
        } else {
            c_currentReaction = c_startingReaction;
            if(c_multipleTrigger) {
                c_state = LISTENING;
            } else {
                c_state = FINISHED;
                taskManager.cancelTask(c_taskId);
            }
            return;
        }
    }
}

void Event::cancel() {
    if(c_state == FINISHED) {
        return;
    }
    if(c_state == RUNNING) {
        c_currentReaction->notifyCancel();
        taskManager.cancelTask(c_taskId);
    } else if(c_state == LISTENING) {
        taskManager.cancelTask(c_taskId);
    }
    c_state = CANCELLED;
}

EventState Event::getEventState() {
    return c_state;
}

Event::Event() = default;

int Event::configure(ICondition &condition, IReaction &reaction, ICondition *cancelCondition, bool multipleTrigger) {
    if(c_state != UNCONFIGURED) {
        return -1;
    }
    c_condition = &condition;
    c_startingReaction = &reaction;
    c_currentReaction = &reaction;
    c_cancelCondition = cancelCondition;
    c_multipleTrigger = multipleTrigger;
    c_state = DISABLED;
    return 0;
}
