#include "CancelRunningCmd.h"
#include "CmdUtils.h"
#include "com/serialreactions/CmdReactionRunner.h"


String CancelRunningCmd::getUsage() {
    static const char regex[] PROGMEM = "cancel";
    return progmem2String(regex);
}

int8_t CancelRunningCmd::execute(HardwareSerial &serial, String args) {
    CmdReactionRunner::getInstance().cancelReaction();
    return 0;
}
