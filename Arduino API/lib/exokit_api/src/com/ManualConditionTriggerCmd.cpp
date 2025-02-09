#include <HardwareSerial.h>
#include "ManualConditionTriggerCmd.h"

ManualConditionTriggerCmd::ManualConditionTriggerCmd(const char* identifier, ManualCondition& condition):
    identifier(identifier), condition(condition) {}

int8_t ManualConditionTriggerCmd::execute(HardwareSerial &serial, String args) {
    condition.setFulfilled();
    return 0;
}

String ManualConditionTriggerCmd::getIdentifier() {
    return identifier;
}


String ManualConditionTriggerCmd::getUsage()
{
    return identifier;
}
