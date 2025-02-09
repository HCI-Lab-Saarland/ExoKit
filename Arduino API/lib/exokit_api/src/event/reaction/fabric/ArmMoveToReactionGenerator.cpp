#include "ArmMoveToReactionGenerator.h"
#include "event/reaction/ActiveJointMoveToReaction.h"
#include "event/reaction/PassiveJointMoveToReaction.h"
#include "event/reaction/ParallelReaction.h"
#include "util/DebugSerial.h"


void ArmMoveToReactionPreparer::prepare() {
    float maxTravelDistance = 0;
    for(size_t i = 0; i < jointCount; i++) {
        maxTravelDistance = max(maxTravelDistance, abs(abs(joints[jointIndexes[i]]->getPresentPosition()) - abs(angles[jointIndexes[i]])));
    }

    for(size_t i = 0; i < jointCount; i++) {
        if(jointReactions[jointIndexes[i]]) {
            if(jointReactions[jointIndexes[i]]->isActiveJoint()) {
                float travelDist = abs(abs(joints[jointIndexes[i]]->getPresentPosition()) - abs(angles[jointIndexes[i]]));
                static_cast<ActiveJointMoveToReaction*>(jointReactions[jointIndexes[i]])
                ->configure(static_cast<ExoskeletonJointActiveHandle&>(*joints[jointIndexes[i]]), angles[jointIndexes[i]], max(1, maxVelocity * (travelDist / maxTravelDistance)));
            } else {
                static_cast<PassiveJointMoveToReaction*>(jointReactions[jointIndexes[i]])
                ->configure(static_cast<ExoskeletonJointPassiveHandle&>(*joints[jointIndexes[i]]), angles[jointIndexes[i]]);
            }
        }
    }
}


void ArmMoveToReactionPreparer::configure(JointMoveToReaction **jointReactions, ExoskeletonJointHandle **joints, float *angles,
                                          float maxVelocity, uint8_t jointCount, size_t *jointIndexes) {
    this->jointCount = jointCount;
    this->maxVelocity = maxVelocity;
    memcpy(this->jointReactions, jointReactions, sizeof(jointReactions[0])*3);
    memcpy(this->joints, joints, sizeof(joints[0])*3);
    memcpy(this->angles, angles, sizeof(angles[0])*3);
    memcpy(this->jointIndexes, jointIndexes, sizeof(jointIndexes[0])*3);
}

ArmMoveToReactionGenerator::ArmMoveToReactionGenerator() {}

ComposedReaction &
ArmMoveToReactionGenerator::init(ExoskeletonArmHandle &exoArm) {
    reset();
    joints[0] = &exoArm.getShoulderBack();
    joints[1] = &exoArm.getShoulderSide();
    joints[2] = &exoArm.getElbow();

    for(size_t i = 0; i < 3; i++) {
        if(joints[i]->isActive()) {
            jointReactions[i] = new ActiveJointMoveToReaction();
        } else {
            jointReactions[i] = new PassiveJointMoveToReaction();
        }
    }

    composedReaction = new ComposedReaction();
    prOuter = new ParallelReaction();
    prInner = new ParallelReaction();
    preparer = new ArmMoveToReactionPreparer();

    return *composedReaction;
}

void ArmMoveToReactionGenerator::reset() {
    if(composedReaction) {
        composedReaction->shutdown(true);
    }
    for (auto & jointReaction : jointReactions) {
        delete jointReaction;
        jointReaction = nullptr;
    }
    delete prOuter;
    prOuter = nullptr;
    delete prInner;
    prInner = nullptr;
    delete preparer;
    preparer = nullptr;
    delete composedReaction;
    composedReaction = nullptr;
}

void ArmMoveToReactionGenerator::configure(ExoArmAngles pos, float maxVelocity) {
    ReactionConfigurationGuard configurationGuard(*composedReaction);
    jointCount = 0;
    float angles[3] = {};
    size_t jointIndexes[3]{};
    if(pos.isHasShoulderBack()) {
        angles[0] = pos.getShoulderBackAngle();
        jointIndexes[jointCount] = 0;
        jointCount++;
    }
    if(pos.isHasShoulderSide()) {
        angles[1] = pos.getShoulderSideAngle();
        jointIndexes[jointCount] = 1;
        jointCount++;
    }
    if(pos.isHasElbow()) {
        angles[2] = pos.getElbowAngle();
        jointIndexes[jointCount] = 2;
        jointCount++;
    }

    switch (jointCount) {
        default:
            break;
        case 1:
            if(jointReactions[jointIndexes[0]]->isActiveJoint()) {
                static_cast<ActiveJointMoveToReaction*>(jointReactions[jointIndexes[0]])
                ->configure(static_cast<ExoskeletonJointActiveHandle&>(*joints[jointIndexes[0]]), angles[jointIndexes[0]], maxVelocity);
            } else {
                static_cast<PassiveJointMoveToReaction*>(jointReactions[jointIndexes[0]])
                ->configure(static_cast<ExoskeletonJointPassiveHandle&>(*joints[jointIndexes[0]]), angles[jointIndexes[0]]);
            }
            composedReaction->configure(jointReactions[jointIndexes[0]]);
            break;
        case 2:
            preparer->configure(jointReactions, joints, angles, maxVelocity, jointCount, jointIndexes);
            prOuter->configure(*jointReactions[jointIndexes[0]], *jointReactions[jointIndexes[1]], preparer);
            composedReaction->configure(prOuter);
            break;
        case 3:
            prInner->configure(*jointReactions[jointIndexes[0]], *jointReactions[jointIndexes[1]]);
            preparer->configure(jointReactions, joints, angles, maxVelocity, jointCount, jointIndexes);
            prOuter->configure(*prInner, *jointReactions[jointIndexes[2]], preparer);
            composedReaction->configure(prOuter);
            break;
    }
}

ComposedReaction& ArmMoveToReactionGenerator::generateReaction()
{
    return *composedReaction;
}

ArmMoveToReactionGenerator::~ArmMoveToReactionGenerator() {
    reset();
}
