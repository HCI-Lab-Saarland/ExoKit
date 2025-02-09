#include "VibrationGenerator.h"
#include "event/condition/TimeoutCondition.h"

void VibrationGenerator::reset()
{
    if(result) {
        result->shutdown(true);
    }
    for(auto & move : moves) {
        delete move;
        move = nullptr;
    }
    for(auto & it : timeouts) {
        delete it;
        it = nullptr;
    }

    delete result;
    result = nullptr;

}

ComposedReaction& VibrationGenerator::init()
{
    reset();
    for(size_t i = 0; i < 2; i++) {
        moves[i] = new ActiveJointMoveToReaction();
    }
    for(size_t i = 0; i < 2; i++) {
        timeouts[i] = new TimeoutCondition();
    }
    result = new ComposedReaction();

    return *result;
}

void VibrationGenerator::configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude) {
    ReactionConfigurationGuard configurationGuard(*result);

    float period = 1.f/frequency;
    float velocity_required = 4.f * amplitude * frequency;

    float max_velocity_available = joint.getMaxNoLoadSpeed(); // in deg/sec
    if (velocity_required >= max_velocity_available) {
        velocity_required = max_velocity_available -1; // -1  some buffer
    }

    moves[0]->configure(joint, 2*amplitude, 0, 0.2, RELATIVE_STARTING_POS);
    moves[1]->configure(joint, -2*amplitude, 0, 0.2, RELATIVE_STARTING_POS);

    moves[0]->then(*moves[1]);
    moves[1]->then(*moves[0]);

    result->configure(moves[0]);
}

