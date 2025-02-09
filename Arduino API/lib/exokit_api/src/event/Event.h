#ifndef CHI25_EXOSKELETON_API_EVENT_H
#define CHI25_EXOSKELETON_API_EVENT_H


#include "event/condition/ICondition.h"
#include "event/reaction/IReaction.h"
#include "TaskTypes.h"
#include <TaskManagerIO.h>

class IReaction;

enum EventState {
    UNCONFIGURED, DISABLED, LISTENING, RUNNING, FINISHED, CANCELLED
};

class Event: public Executable {
private:
    ICondition* c_condition{};
    IReaction* c_startingReaction{};
    IReaction* c_currentReaction{};
    ICondition* c_cancelCondition{};
    bool c_multipleTrigger{};
    taskid_t c_taskId{0};
    EventState c_state{UNCONFIGURED};

    /**
     * Executes a running event.
     * Runs the associated reaction loop, and handles cancel conditions and state transitions.
     */
    void performRunning();

public:
        
    /**
     * Default constructor for the Event class.
     */
    Event();
        
     /**
     * Configures the event with the specified conditions and reactions.
     * 
     * @param condition The condition that triggers the event.
     * @param reaction The reaction to perform when the event is triggered.
     * @param cancelCondition The condition that cancels the event, or nullptr if no cancel condition exists.
     * @param multipleTrigger Boolean indicating whether the event can trigger multiple times.
     * @return 0 if the configuration was successful, -1 if the event was already configured.
     */
    int configure(ICondition& condition, IReaction& reaction, ICondition* cancelCondition = nullptr, bool multipleTrigger = false);
    
    /**
     * Handles the current event based on its state and
     * handles transitions between the different event states: 
     * DISABLED, LISTENING, RUNNING, CANCELLED, FINISHED, UNCONFIGURED.
     */    
    void exec() override;

    /**
     * Enables the event, scheduling it to repeat at the specified interval, 
     * and changes the event state to LISTENING.
     * @param loopInterval The interval in milliseconds between repeated executions.
     * @return True if the event was successfully enabled, false if it was already enabled.
     */
    bool enable(uint32_t loopInterval);

    /**
     * Gets the current state of the event.
     * @return The current state of the event (DISABLED, LISTENING, RUNNING, CANCELLED, FINISHED, UNCONFIGURED).
     */
    EventState getEventState();
    
    /**
     * Cancels the event and handles the cleanup of running tasks.
     */
    void cancel();

};


#endif //CHI25_EXOSKELETON_API_EVENT_H
