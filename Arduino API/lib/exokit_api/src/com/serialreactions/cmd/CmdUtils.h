#ifndef CHI25_EXOSKELETON_API_CMDUTILS_H
#define CHI25_EXOSKELETON_API_CMDUTILS_H

/**
* Functions to parse the incoming data of the command-line interface.
* This includes to parse the exoID, the targeted arm side, the targeted joint, and further helper functions.
 */

#include "exo/ExoskeletonJointHandle.h"
#include "exo/ExoskeletonHandle.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "event/reaction/JointMoveToReaction.h"

#define CMD_PARSE_EXO_REGEX "(ExoID)"
ExoskeletonHandle* parseExo(const String& identifier);

#define CMD_PARSE_ARM_FROM_EXO_REGEX "(left|right)"
ExoskeletonArmHandle* parseArm(ExoskeletonHandle& exo, const String& armString);

#define CMD_PARSE_JOINT_FROM_ARM_REGEX "(elbow|shoulderback|shoulderside)"
ExoskeletonJointHandle* parseJoint(ExoskeletonArmHandle& arm, const String& jointString);

// Parse from string with error handling

#define CMD_PARSE_JOINT_REGEX CMD_PARSE_EXO_REGEX " " CMD_PARSE_ARM_FROM_EXO_REGEX " " CMD_PARSE_JOINT_FROM_ARM_REGEX
int8_t tryParseJoint(HardwareSerial &serial, const String& exoIdString, const String& armString, const String& jointString, ExoskeletonJointHandle** outJoint);

#define CMD_PARSE_ARM_REGEX CMD_PARSE_EXO_REGEX " " CMD_PARSE_ARM_FROM_EXO_REGEX
int8_t tryParseArm(HardwareSerial &serial, const String& exoIdString, const String& armString, ExoskeletonArmHandle** outArm);

int8_t tryParseExo(HardwareSerial &serial, const String& identifier, ExoskeletonHandle** outExo);

// Parse from starting-object with string and error handling

int8_t tryParseArm(HardwareSerial &serial, ExoskeletonHandle& exo, const String& armString, ExoskeletonArmHandle** outArm);

int8_t tryParseJoint(HardwareSerial &serial, ExoskeletonArmHandle& arm, const String& jointString, ExoskeletonJointHandle** outJoint);

#define CMD_PARSE_ARM_ANGLE "(elbowAngle|false) (shoulderSideAngle|false) (shoulderBackAngle|false)"
int8_t tryParseArmAngle(HardwareSerial &serial, const String& elbowAngleString, const String& shoulderSideAngleString, const String& shoulderBackAngleString, ExoArmAngles* outAngles);

#define CMD_PARSE_BOOL "(true|false)"
int8_t tryParseBool(HardwareSerial &serial, const String& boolString, bool* outBool);

int8_t tryCastActiveJoint(HardwareSerial &serial, ExoskeletonJointHandle& joint, ExoskeletonJointActiveHandle** outActiveJoint);

int8_t tryParseFloat(HardwareSerial &serial, const String& stringNumber, float* number);

int8_t tryParseInt(HardwareSerial &serial, const String& stringNumber, long *number);

#define CMD_PARSE_MOVETO_TARGET_TYPE "(absolute|relative)"
int8_t tryParseMoveToTargetType(HardwareSerial &serial, const String& stringTarget, TargetType* target);

int8_t parseTargetType(const String& stringTarget, TargetType* target);

#define CMD_PARSE_JOINT_DIRECTION "(abduction|flexion|adduction|extension|both)"
int8_t tryParseMovementDirection(HardwareSerial& serial, const String& dirString, ExoskeletonJointHandle::MovementDirection* outDirection);

int8_t parseMovementDirection(const String& dirString, ExoskeletonJointHandle::MovementDirection* outDirection);

String progmem2String(const char* progmem);

String getArg(const String& args, size_t argIdx);

bool isInt(const String& nr);

bool isFloat(const String& nr);


#endif //CHI25_EXOSKELETON_API_CMDUTILS_H
