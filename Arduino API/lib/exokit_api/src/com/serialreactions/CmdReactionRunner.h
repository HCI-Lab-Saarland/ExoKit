#ifndef CHI25_EXOSKELETON_API_CMDREACTIONRUNNER_H
#define CHI25_EXOSKELETON_API_CMDREACTIONRUNNER_H


#include "event/Event.h"
#include "event/condition/TrueCondition.h"

class CmdReactionRunner {
    static CmdReactionRunner* instance;
    Event* event{};
    IReaction* reaction{};
    TrueCondition trueCondition;
    CmdReactionRunner() = default;

public:
    /**
     * Getter for CmdReactionRunner instance.
     * @return The unique instance of CmdReactionRunner.
     */
    static CmdReactionRunner& getInstance();

    /**
     * Launches the given reaction by setting up a new event and configuring it.
     * The previous reaction, if any, is canceled.
     * @param reaction The reaction to be launched.
     */
    void launchReaction(IReaction& reaction);

    /**
     * Cancels the current reaction, if any, by canceling the associated event and cleaning up resources.
     * @return True if a reaction was canceled successfully, false if no reaction was running.
     */
    bool cancelReaction();
};


#endif //CHI25_EXOSKELETON_API_CMDREACTIONRUNNER_H
