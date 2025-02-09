#include "ActionBuilder.h"
#include "event/reaction/DelayReaction.h"
#include "event/reaction/WaitForConditionReaction.h"
#include "event/condition/TrueCondition.h"
#include "event/condition/FalseCondition.h"
#include "event/condition/TimeoutCondition.h"
#include "event/condition/ManualCondition.h"

void ActionBuilder::nextReaction(IReaction& next, bool doBindOwnership) {
    if(firstReaction == nullptr) {
        firstReaction = &next;
        prevReaction = &next;
    } else {
        prevReaction->then(next);
        prevReaction = &next;
    }
    if(doBindOwnership) {
        bindOwnership(next);
    }
}

void ActionBuilder::bindOwnership(IReaction &reaction) {
    generatedReactions.add(&reaction);
}

void ActionBuilder::newParallel() {
    auto* pr = new ParallelReaction();
    nextReaction(*pr);
    auto* nop = new NoOpReaction();
    generatedReactions.add(nop);
    reactionStack.add({
                              PARALLEL,
                              pr,
                              nop
                      });
    prevReaction = new NoOpReaction();
    generatedReactions.add(prevReaction);
    pr->configure(*prevReaction, *nop);
}

void ActionBuilder::nextParallel() {
    action_stack_entry_t stackEntry = reactionStack.get(reactionStack.size() - 1);
    if (stackEntry.blockType != PARALLEL) {
        DEBUG_SERIAL.println(F("Error: stackEntry.levelType != PARALLEL"));
        return;
    }
    prevReaction = stackEntry.typeMultipurposeSlot;
}

void ActionBuilder::newBreakableBlock(ICondition& breakIf) {
    auto* cr = new ComposedReaction();
    cr->setAlternativeFinishCondition(&breakIf);
    nextReaction(*cr);
    auto* nop = new NoOpReaction();
    cr->configure(nop);
    reactionStack.add({
                              BREAKABLE,
                              cr,
                              nop
                      });
    prevReaction = nop;
    generatedReactions.add(nop);
}

void ActionBuilder::newLoopBlock(ICondition& condition) {
    auto* loopBlock = new NoOpReaction();
    nextReaction(*loopBlock);
    auto* thenR = new NoOpReaction();
    this->prevReaction = thenR;
    generatedReactions.add(thenR);
    auto* onBreakR = new NoOpReaction();
    generatedReactions.add(onBreakR);
    loopBlock->ifThenElse(condition, *thenR, *onBreakR);
    reactionStack.add({
                              LOOP,
                              loopBlock,
                              onBreakR
                      });
}

void ActionBuilder::newIfThenElseBlock(ICondition& condition) {
    auto* ifR = new NoOpReaction();
    nextReaction(*ifR);
    auto* thenR = new NoOpReaction();
    prevReaction = thenR;
    generatedReactions.add(thenR);
    auto* elseR = new NoOpReaction();
    generatedReactions.add(elseR);
    ifR->ifThenElse(condition, *thenR, *elseR);
    reactionStack.add({
                              IF_THEN_ELSE,
                              ifR,
                              elseR
                      });
}

void ActionBuilder::ifThenElseStartElse() {
    action_stack_entry_t stackEntry = reactionStack.pop();
    if (stackEntry.blockType != IF_THEN_ELSE) {
        DEBUG_SERIAL.println(F("Error: stackEntry.levelType != IF_THEN_ELSE"));
        return;
    }
    IReaction* tmp = prevReaction;
    prevReaction = stackEntry.typeMultipurposeSlot;
    stackEntry.typeMultipurposeSlot = tmp;
    reactionStack.add(stackEntry);
}

void ActionBuilder::endSpecialBlock() {
    action_stack_entry_t stackEntry = reactionStack.pop();
    if(stackEntry.blockType == LOOP) {
        prevReaction->then(*stackEntry.reaction);
        prevReaction = stackEntry.typeMultipurposeSlot;
    } else if (stackEntry.blockType == IF_THEN_ELSE) {
        auto* nop = new NoOpReaction();
        stackEntry.typeMultipurposeSlot->then(*nop);
        nextReaction(*nop);
    } else {
        prevReaction = stackEntry.reaction;
    }
}

void ActionBuilder::parallel(void (*firstParallel)(ActionBuilder&), void (*secondParallel)(ActionBuilder&)) {
    newParallel();
    firstParallel(*this);
    nextParallel();
    secondParallel(*this);
    endSpecialBlock();
}

void ActionBuilder::ifThenElse(ICondition& condition, void (*thenBlock)(ActionBuilder&), void (*elseBlock)(ActionBuilder&)) {
    newIfThenElseBlock(condition);
    if(thenBlock == nullptr) {
        thenBlock(*this);
    }
    ifThenElseStartElse();
    if(elseBlock != nullptr) {
        elseBlock(*this);
    }
    endSpecialBlock();
}

void ActionBuilder::breakableBlock(ICondition& breakIf, void (*block)(ActionBuilder&)) {
    newBreakableBlock(breakIf);
    block(*this);
    endSpecialBlock();
}

void ActionBuilder::loop(ICondition& loopCondition, void (*inLoopBlock)(ActionBuilder&)) {
    newLoopBlock(loopCondition);
    inLoopBlock(*this);
    endSpecialBlock();
}

Event * ActionBuilder::dispatch(ICondition& condition, unsigned long loopInterval, boolean multipleTrigger) {
    if(!firstReaction) {
        return nullptr;
    }
    dispatcher = new Event();
    dispatcher->configure(condition, *firstReaction, nullptr, multipleTrigger);
    dispatcher->enable(loopInterval);
    return dispatcher;
}

void ActionBuilder::delay(unsigned long millis) {
    auto* delayR = new DelayReaction();
    delayR->configure(millis);
    nextReaction(*delayR);
}

void ActionBuilder::waitFor(ICondition &condition) {
    auto* waitForConditionReaction = new WaitForConditionReaction();
    waitForConditionReaction->configure(condition);
    nextReaction(*waitForConditionReaction);
}

void ActionBuilder::reset() {
    if(dispatcher && (dispatcher->getEventState() == LISTENING || dispatcher->getEventState() == RUNNING)) {
        dispatcher->cancel();
        delete dispatcher;
        dispatcher = nullptr;
    }
    while (generatedReactions.size() > 0) {
        delete generatedReactions.pop();
    }
    while (generatedConditions.size() > 0) {
        delete generatedConditions.pop();
    }
    firstReaction = nullptr;
    prevReaction = nullptr;
}

void ActionBuilder::bindOwnership(ICondition &condition) {
    generatedConditions.add(&condition);
}

void ActionBuilder::unbindOwnerShip(ICondition &condition) {
    for(int i = 0; i < generatedConditions.size(); i++) {
        ICondition* cond = generatedConditions.get(i);
        if(cond == &condition) {
            generatedConditions.remove(i);
            break;
        }
    }
}

ICondition &ActionBuilder::trueCondition() {
    auto* condition = new TrueCondition();
    bindOwnership(*condition);
    return *condition;
}

ICondition &ActionBuilder::falseCondition() {
    auto* condition = new FalseCondition();
    bindOwnership(*condition);
    return *condition;
}

ICondition &ActionBuilder::timeoutCondition(unsigned long wait_ms) {
    auto* condition = new TimeoutCondition();
    condition->configure(wait_ms);
    bindOwnership(*condition);
    return *condition;
}

ICondition &ActionBuilder::manualCondition(bool unfulfillOnRestore, bool armOnFirstEval) {
    auto* condition = new ManualCondition();
    condition->configure(unfulfillOnRestore, armOnFirstEval);
    bindOwnership(*condition);
    return *condition;
}

bool ActionBuilder::NoOpReaction::finishCondition() {
    return true;
}

void ActionBuilder::NoOpReaction::shutdown(bool isCancel) {

}

void ActionBuilder::NoOpReaction::prepare() {

}

void ActionBuilder::NoOpReaction::startup() {

}

void ActionBuilder::NoOpReaction::runLoop() {

}
