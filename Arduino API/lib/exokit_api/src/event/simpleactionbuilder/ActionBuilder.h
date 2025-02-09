#ifndef CHI25_EXOSKELETON_API_ACTIONBUILDER_H
#define CHI25_EXOSKELETON_API_ACTIONBUILDER_H


#include "event/reaction/IReaction.h"
#include "LinkedList.h"
#include "event/reaction/ParallelReaction.h"
#include "util/DebugSerial.h"
#include "event/reaction/ComposedReaction.h"
#include "event/Event.h"

class ActionBuilder {
    class NoOpReaction: public IReaction {
        void runLoop() override;
        void startup() override;
        void prepare() override;
        void shutdown(bool isCancel) override;
        bool finishCondition() override;
    };

    enum SpecialBlockType {
        BREAKABLE, IF_THEN_ELSE,
        PARALLEL, LOOP
    };
    struct action_stack_entry_t {
        SpecialBlockType blockType;
        IReaction* reaction;
        IReaction* typeMultipurposeSlot;
    };

    Event* dispatcher;
    IReaction* firstReaction{};
    IReaction* prevReaction{};
    LinkedList<action_stack_entry_t> reactionStack;
    LinkedList<IReaction*> generatedReactions;
    LinkedList<ICondition*> generatedConditions;

    void newParallel();
    void nextParallel();
    void newBreakableBlock(ICondition& breakIf);
    void newLoopBlock(ICondition& condition);
    void newIfThenElseBlock(ICondition& condition);
    void ifThenElseStartElse();
    void endSpecialBlock();

public:
    /**
     * Declares the ActionBuilder as the owner of the given condition.
     * The given object will be deleted if the ActionBuilder is deleted or reset.
     * @param condition The condition to bind to the ActionBuilder
     */
    void bindOwnership(ICondition& condition);

    /**
     * Revokes the ActionBuilder's ownership over the given object.
     * The given object will not be deleted if the ActionBuilder is deleted or reset.
     * @param reaction The reaction to unbind.
     */
    void bindOwnership(IReaction& reaction);

    /**
     * Revokes the ActionBuilder's ownership over the given object.
     * The given object will not be deleted if the ActionBuilder is deleted or reset.
     * @param condition The condition to unbind.
     */
    void unbindOwnerShip(ICondition& condition);

    /**
     * Resets the current ActionBuilder and deletes all conditions and actions that have been configured using it.
     */
    void reset();

    /**
     * Appends a reaction to the current sequence of reactions.
     * @param next The reaction to append.
     * @param doBindOwnership If true the ActionBuilder instance becomes the owner of the given action.
     * Destroying the ActionBuilder or calling reset() will delete the given action.
     */
    void nextReaction(IReaction& next, bool doBindOwnership = true);

    /**
     * Executes two action chains in parallel.
     * @param firstParallel The method that defines the first action chain.
     * @param secondParallel The method that defines the second action chain.
     */
    void parallel(void (*firstParallel)(ActionBuilder&), void (*secondParallel)(ActionBuilder&));

    /**
     * An If/else block
     * @param condition The condition
     * @param thenBlock The method that defines the action chain that should be executed if the condition evaluates to true.
     * @param elseBlock The method that defines the action chain that should be executed if the condition evaluates to false.
     */
    void ifThenElse(ICondition& condition, void (*thenBlock)(ActionBuilder&), void (*elseBlock)(ActionBuilder&));

    /**
     * Defines a code block that can break any time, if the breakIf condition evaluates to true.
     * @param breakIf The condition.
     * @param block The method that defines the action chain that can be breakek.
     */
    void breakableBlock(ICondition& breakIf, void (*block)(ActionBuilder&));

    /**
     * Puts the actions defined in the method in a (while like) loop that repeats as long as loopCondition evaluates to true.
     * @param loopCondition The condition that determines if the loop continues or not.
     * @param inLoopBlock The method that defines the actions, that the loop body is made of.
     */
    void loop(ICondition& loopCondition, void (*inLoopBlock)(ActionBuilder&));

    /**
     * Activates give action that was previously configured using this ActionBuilder-Object.
     * The action triggers when the condition given at "condition" evaluates to true.
     * @param condition The condition that starts the action.
     * @param loopInterval Specifies the interval (in ms) in which tasks, that the exoskeleton executes are being processed.
     * A smaller interval makes the exoskeleton more responsive.
     * @param multipleTrigger Should the action restart when it finished. When restarting the exoskeleton also waits
     * for "condition" to evaluate to true before it triggers the action again.
     * @return
     */
    Event * dispatch(ICondition& condition, unsigned long loopInterval, bool multipleTrigger=true);

    /**
     * Waits for the selected amount of time.
     * @param millis The time in ms.
     */
    void delay(unsigned long millis);

    /**
     * Waits till the given condition evaluates to true.
     * @param condition The condition.
     */
    void waitFor(ICondition& condition);

    /**
     * Creates and returns a condition that always evaluates to true.
     * @return The condition object.
     */
    ICondition& trueCondition();

    /**
     * Creates and returns a condition that always evaluates to false.
     * @return The condition object.
     */
    ICondition& falseCondition();

    /**
     * Creates and returns a condition that waits for a selected amount of time. The timer starts at the first evaluation of the condition.
     * @param wait_ms The time in ms.
     * @return The condition object.
     */
    ICondition& timeoutCondition(unsigned long wait_ms);

    /**
     * Creates and returns a manual condition. That can be triggered using custom code.
     * @param unfulfillOnRestore Set to true, if the condition should be reset if an an action that is attached to it finishes.
     * @param armOnFirstEval Set to true, if it action should only trigger after it has been evaluated at least once.
     * @return The condition object.
     */
    ICondition& manualCondition(bool unfulfillOnRestore = true, bool armOnFirstEval = false);

};


#endif //CHI25_EXOSKELETON_API_ACTIONBUILDER_H
