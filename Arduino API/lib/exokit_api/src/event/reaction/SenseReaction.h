#ifndef SENSEREACTION_H
#define SENSEREACTION_H

#include "IReaction.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "LinkedList.h"

enum SensorType
{
    VELOCITY, SPEED, ACCELERATION, FORCE, POSITION
};

class SenseReaction: public IReaction {
private:
    ExoskeletonJointHandle* c_joint{};
    bool streamPosition{};
    bool streamVelocity{};
    bool streamSpeed{};
    bool streamLoadCell{};
    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    void shutdown(bool isCancel) override;
    SenseReaction();
    void configure(ExoskeletonJointHandle& joint, bool streamPosition, bool streamVelocity, bool streamSpeed, bool streamLoadCell);
};

#endif //SENSEREACTION_H
