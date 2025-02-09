#include "SerialCmdReader.h"
#include "com/serialreactions/cmd/JointLockCmd.h"
#include "com/serialreactions/cmd/CancelRunningCmd.h"
#include "com/serialreactions/cmd/JointMoveToCmd.h"
#include "com/serialreactions/cmd/JointAmplifyCmd.h"
#include "com/serialreactions/cmd/JointResistCmd.h"
#include "com/serialreactions/cmd/JointVibrationCmd.h"
#include "com/serialreactions/cmd/JointConstrainToCmd.h"
#include "com/serialreactions/cmd/JointGuideAwayCmd.h"
#include "com/serialreactions/cmd/JointGuideTowardsCmd.h"
#include "com/serialreactions/cmd/JointJerkCmd.h"
#include "com/serialreactions/cmd/JointMirrorCmd.h"
#include "com/serialreactions/cmd/JointFilterSpeedCmd.h"
#include "com/serialreactions/cmd/ArmLockCmd.h"
#include "com/serialreactions/cmd/ArmAmplifyCmd.h"
#include "com/serialreactions/cmd/ArmConstrainToCmd.h"
#include "com/serialreactions/cmd/ArmFilterSpeedCmd.h"
#include "com/serialreactions/cmd/ArmGuideAwayCmd.h"
#include "com/serialreactions/cmd/ArmGuideTowardsCmd.h"
#include "com/serialreactions/cmd/ArmJerkCmd.h"
#include "com/serialreactions/cmd/ArmMirrorCmd.h"
#include "com/serialreactions/cmd/ArmMoveToCmd.h"
#include "com/serialreactions/cmd/ArmResistCmd.h"
#include "TaskManagerIO.h"
#include "com/serialreactions/cmd/ArmGestureCmd.h"
#include "serialreactions/cmd/ArmVibrateCmd.h"


SerialCmdReader::SerialCmdReader(HardwareSerial &serial, uint32_t interval):
        serial(serial), commands(LinkedList<ICmd*>()) {
    taskId = taskManager.scheduleFixedRate(interval, this);
}

SerialCmdReader::~SerialCmdReader() {
    if(isSerialControlCommands) {
        while (serialControlCommands.size() > 0) {
            delete serialControlCommands.pop();
        }
    }
    taskManager.cancelTask(taskId);
}

void SerialCmdReader::exec() {
    if(serial.available() <= 0) {
        return;
    }
    String cmdRaw = serial.readStringUntil('\n');
    cmdRaw.trim();
    cmdRaw.toLowerCase();
    int argsSplit = cmdRaw.indexOf(' ');
    String cmdIdentifier;
    String cmdArgs = "";
    if(argsSplit == -1) {
        cmdIdentifier = cmdRaw;
    } else {
        cmdIdentifier = cmdRaw.substring(0, argsSplit);
        cmdArgs = cmdRaw.substring(argsSplit + 1);
    }
    for(int idx = 0; idx < commands.size(); idx++) {
        if(!commands[idx]->getIdentifier().equals(cmdIdentifier)) {
            continue;
        }
        if(commands[idx]->execute(serial, cmdArgs) < 0) {
            serial.print("Syntax: ");
            serial.println(commands[idx]->getUsage());
            return;
        }
        return;
    }

    if(cmdIdentifier.equals(F("help")) || cmdIdentifier.equals(F("h")) || cmdIdentifier.equals(F("?"))) {
        for(int idx = 0; idx < commands.size(); idx++) {
            serial.println(commands[idx]->getUsage());
        }
        return;
    }
    serial.println(F("Unknown command! Type 'help', 'h' or '?' for a list of all commands."));
}

bool SerialCmdReader::registerCmd(ICmd &cmd) {
    for(int idx = 0; idx < commands.size(); idx++) {
        if(commands[idx]->getIdentifier().equals(cmd.getIdentifier())) {
            return false;
        }
    }
    commands.add(&cmd);
    return true;
}

bool SerialCmdReader::unregisterCmd(ICmd &cmd) {
    bool found = false;
    int idx = 0;
    for(;idx < commands.size(); idx++) {
        if(commands[idx] == &cmd) {
            found = true;
            break;
        }
    }
    if(found) {
        commands.remove(idx);
        return true;
    }
    return false;
}

void SerialCmdReader::enableSerialControlCommands() {
    if(isSerialControlCommands) {
        return;
    }
    isSerialControlCommands = true;

    serialControlCommands.add(new CancelRunningCmd());

    serialControlCommands.add(new JointAmplifyCmd());
    serialControlCommands.add(new JointConstrainToCmd());
    serialControlCommands.add(new JointFilterSpeedCmd());
    serialControlCommands.add(new JointGuideAwayCmd());
    serialControlCommands.add(new JointGuideTowardsCmd());
    serialControlCommands.add(new JointJerkCmd());
    serialControlCommands.add(new JointLockCmd());
    serialControlCommands.add(new JointMirrorCmd());
    serialControlCommands.add(new JointMoveToCmd());
    serialControlCommands.add(new JointResistCmd());
    serialControlCommands.add(new JointVibrationCmd());

    serialControlCommands.add(new ArmAmplifyCmd());
    serialControlCommands.add(new ArmConstrainToCmd());
    serialControlCommands.add(new ArmFilterSpeedCmd());
    serialControlCommands.add(new ArmGestureCmd());
    serialControlCommands.add(new ArmGuideAwayCmd());
    serialControlCommands.add(new ArmGuideTowardsCmd());
    serialControlCommands.add(new ArmJerkCmd());
    serialControlCommands.add(new ArmLockCmd());
    serialControlCommands.add(new ArmMirrorCmd());
    serialControlCommands.add(new ArmMoveToCmd());
    serialControlCommands.add(new ArmResistCmd());
    serialControlCommands.add(new ArmVibrateCmd);

    for(int i = 0; i < serialControlCommands.size(); i++) {
        registerCmd(*serialControlCommands.get(i));
    }
}
