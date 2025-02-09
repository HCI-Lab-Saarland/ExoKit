#ifndef CHI25_EXOSKELETON_API_SERIALCMDREADER_H
#define CHI25_EXOSKELETON_API_SERIALCMDREADER_H


#include <HardwareSerial.h>
#include "TaskTypes.h"
#include "ICmd.h"
#include "LinkedList.h"

class SerialCmdReader: public Executable {
private:
    HardwareSerial& serial;
    LinkedList<ICmd*> commands;
    LinkedList<ICmd*> serialControlCommands;
    bool isSerialControlCommands{false};
    taskid_t taskId;
public:
    /**
     * Constructor for SerialCmdReader.
     * Initializes the serial command line interface and command list, and schedules the task for regular execution.
     * @param serial The hardware serial interface to use for communication.
     * @param interval The interval (in milliseconds) for the task to execute.
     */
    explicit SerialCmdReader(HardwareSerial& serial, uint32_t interval = 100);

    /**
     * Destructor for SerialCmdReader.
     */
    ~SerialCmdReader() override;

    /**
     * Executes the command reader logic.
     * Reads a command from the serial input, processes it, and calls the appropriate handler.
     */
    void exec() override;

    /**
     * Registers a new command for the SerialCmdReader to handle.
     * @param cmd The command object to register.
     * @return True if the command was successfully registered, false if a command with the same identifier already exists.
     */
    bool registerCmd(ICmd& cmd);

    /**
     * Unregisters a command from the SerialCmdReader.
     * 
     * @param cmd The command object to unregister.
     * @return True if the command was found and removed, false otherwise.
     */
    bool unregisterCmd(ICmd& cmd);

    
    /**
     * Enables serial control commands for the command line interface (CLI).
     * Adds the list of predefined commands that can be called through the CLI.
     */
    void enableSerialControlCommands();

};


#endif //CHI25_EXOSKELETON_API_SERIALCMDREADER_H
