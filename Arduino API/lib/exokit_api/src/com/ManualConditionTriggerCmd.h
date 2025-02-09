#ifndef CHI25_EXOSKELETON_API_MANUALCONDITIONTRIGGERCMD_H
#define CHI25_EXOSKELETON_API_MANUALCONDITIONTRIGGERCMD_H


#include "ICmd.h"
#include "event/condition/ManualCondition.h"

class ManualConditionTriggerCmd: public ICmd {
private:
    const char* identifier;
    ManualCondition& condition;
public:
    /**
     * Constructor for ManualConditionTriggerCmd.
     * Initializes the command with an identifier and a reference to a ManualCondition object.
     * @param identifier The command identifier (name).
     * @param condition A reference to the ManualCondition object associated with this command.
     */
    explicit ManualConditionTriggerCmd(const char* identifier, ManualCondition& condition);
   
    /**
     * Executes the command by setting the associated condition as fulfilled.
     * 
     * @param serial The hardware serial interface used for communication.
     * @param args Arguments passed to the command (not used here).
     * @return Returns 0.
     */
    int8_t execute(HardwareSerial &serial, String args) override;

    /**
     * Retrieves the identifier for this command.
     * 
     * @return The identifier (name) of the command as a String.
     */
    String getIdentifier() override;

    /**
     * Retrieves the identifier.
     * 
     * @return The identifier (name) of the command as a String.
     */
    String getUsage() override;
};


#endif //CHI25_EXOSKELETON_API_MANUALCONDITIONTRIGGERCMD_H
