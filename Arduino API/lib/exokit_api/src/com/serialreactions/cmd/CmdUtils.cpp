#include <WString.h>
#include "exo/ExoskeletonHandle.h"
#include "exo/ExoskeletonArmHandle.h"
#include "util/DebugSerial.h"
#include "exo/ExoskeletonJointActiveHandle.h"
#include "exo/ExoskeletonStore.h"
#include "CmdUtils.h"
#include "event/reaction/JointMoveToReaction.h"

ExoskeletonHandle* parseExo(const int8_t identifier) {
    return ExoskeletonStore::getInstance().getById(identifier);
}

ExoskeletonArmHandle* parseArm(ExoskeletonHandle& exo, const String& armString) {
    if(armString.equals(F("left"))) {
        return &exo.getLeftArm();
    } else if(armString.equals(F("right"))) {
        return &exo.getRightArm();
    } else {
        return nullptr;
    }
}

ExoskeletonJointHandle* parseJoint(ExoskeletonArmHandle& arm, const String& jointString) {
    if (jointString.equals(F("elbow"))) {
        return &arm.getElbow();
    } else if (jointString.equals(F("shoulderback"))) {
        return &arm.getShoulderBack();
    } else if (jointString.equals(F("shoulderside"))) {
        return &arm.getShoulderSide();
    } else {
        return nullptr;
    }
}

int8_t tryParseExo(HardwareSerial &serial, const String& identifier, ExoskeletonHandle** outExo) {
    if(!isInt(identifier)) {
        serial.println(F("Exoskeleton must ne a (int-)number!"));
        serial.print(F("You wrote: "));
        serial.println(identifier);
        return -1;
    }
    auto exoID = (int8_t) identifier.toInt();
    *outExo = parseExo(exoID);
    if(*outExo == nullptr) {
        serial.println(F("Exoskeleton not found! "));
        serial.print(F("ExoId: "));
        serial.println(identifier);
        return -1;
    }
    return 0;
}

int8_t tryParseArm(HardwareSerial &serial, const String& exoIdString, const String& armString, ExoskeletonArmHandle** outArm) {
    ExoskeletonHandle* exo{};
    if(tryParseExo(serial, exoIdString, &exo) < 0) {
        return -1;
    }
    *outArm = parseArm(*exo, armString);
    if(*outArm == nullptr) {
        serial.println(F("Arm not found! "));
        serial.print(F("Arm: "));
        serial.println(armString);
        return -1;
    }
    return 0;
}

int8_t tryParseJoint(HardwareSerial &serial, const String& exoIdString, const String& armString, const String& jointString, ExoskeletonJointHandle** outJoint) {
    ExoskeletonArmHandle* arm{};
    if(tryParseArm(serial, exoIdString, armString, &arm) < 0) {
        return -1;
    }
    if(tryParseJoint(serial, *arm, jointString, outJoint) < 0) {
        return -1;
    }
    return 0;
}

int8_t tryParseJoint(HardwareSerial &serial, ExoskeletonArmHandle& arm, const String& jointString, ExoskeletonJointHandle** outJoint) {
    *outJoint = parseJoint(arm, jointString);
    if(*outJoint == nullptr) {
        serial.println(F("Joint not found! "));
        serial.print(F("Joint: "));
        serial.println(jointString);
        return -1;
    }
    return 0;
}

int8_t tryParseArmAngle(HardwareSerial &serial, const String& elbowAngleString, const String& shoulderSideAngleString, const String& shoulderBackAngleString, ExoArmAngles* outAngles) {
    if(elbowAngleString.equals(F("false"))) {
        outAngles->delElbowAngle();
    } else {
        float elbowAngle{};
        if(tryParseFloat(serial, elbowAngleString, &elbowAngle) < 0) {
            return -1;
        }
        outAngles->setElbowAngle(elbowAngle);
    }
    if(shoulderSideAngleString.equals(F("false"))) {
        outAngles->delShoulderSideAngle();
    } else {
        float shoulderSideAngle{};
        if(tryParseFloat(serial, shoulderSideAngleString, &shoulderSideAngle) < 0) {
            return -1;
        }
        outAngles->setShoulderSideAngle(shoulderSideAngle);
    }
    if(shoulderBackAngleString.equals(F("false"))) {
        outAngles->delShoulderBackAngle();
    } else {
        float shoulderBackAngle{};
        if(tryParseFloat(serial, shoulderBackAngleString, &shoulderBackAngle) < 0) {
            return -1;
        }
        outAngles->setShoulderBackAngle(shoulderBackAngle);
    }
    return 0;
}

int8_t tryCastActiveJoint(HardwareSerial &serial, ExoskeletonJointHandle& joint, ExoskeletonJointActiveHandle** outActiveJoint) {
    if(!joint.isActive()) {
        serial.println(F("Specified joint not active! "));
        return -1;
    }
    *outActiveJoint = static_cast<ExoskeletonJointActiveHandle*>(&joint);
    return 0;
}

int8_t tryParseBool(HardwareSerial &serial, const String& boolString, bool* outBool) {
    if(!boolString.equals(F("true")) && !boolString.equals(F("false"))) {
        serial.println(F("Expected bool! "));
        serial.print(F("Given: "));
        serial.println(boolString);
        return -1;
    }
    *outBool = boolString.equals(F("true"));
    return 0;
}

int8_t tryParseFloat(HardwareSerial &serial, const String& stringNumber, float* number) {
    if(!isFloat(stringNumber)) {
        serial.println(F("Expected float! "));
        serial.print(F("Given: "));
        serial.println(stringNumber);
        return -1;
    }
    *number = stringNumber.toFloat();
    return 0;
}

int8_t tryParseInt(HardwareSerial &serial, const String& stringNumber, long* number) {
    if(!isInt(stringNumber)) {
        serial.println(F("Expected int! "));
        serial.print(F("Given: "));
        serial.println(stringNumber);
        return -1;
    }
    *number = stringNumber.toInt();
    return 0;
}

int8_t parseTargetType(const String& stringTarget, TargetType* target) {
    if(stringTarget.equals(F("absolute"))) {
        *target = ABSOLUTE;
        return 0;
    }
    if(stringTarget.equals(F("relative"))) {
        *target = RELATIVE_STARTING_POS;
        return 0;
    }
    return -1;
}

int8_t tryParseMoveToTargetType(HardwareSerial &serial, const String& stringTarget, TargetType* target) {
    if(parseTargetType(stringTarget, target) < 0) {
        serial.print(F("Unknown MoveTo-Target-Type: "));
        serial.println(stringTarget);
        return -1;
    }
    return 0;
}

String progmem2String(const char* progmem) {
    String s;
    char myChar;
    int signMessageLength = strlen_P(progmem);
    for (int k = 0; k < signMessageLength; k++) {
        myChar = pgm_read_byte_near(progmem + k);
        s.concat(myChar);
    }
    return s;
}

int8_t tryParseMovementDirection(HardwareSerial& serial, const String& dirString, ExoskeletonJointHandle::MovementDirection* outDirection) {
    if(parseMovementDirection(dirString, outDirection) < 0) {
        serial.print(F("Unknown Movement-Direction: "));
        serial.println(dirString);
        return -1;
    }
    return 0;
}

int8_t parseMovementDirection(const String& dirString, ExoskeletonJointHandle::MovementDirection* outDirection) {
    if(dirString.equals(F("abduction")) || dirString.equals(F("flexion"))) {
        *outDirection = ExoskeletonJointHandle::MovementDirection::ABDUCTION_OR_FLEXION;
        return 0;
    }
    if(dirString.equals(F("adduction")) || dirString.equals(F("extension"))) {
        *outDirection = ExoskeletonJointHandle::MovementDirection::ADDUCTION_OR_EXTENSION;
        return 0;
    }
    if(dirString.equals(F("both"))) {
        *outDirection = ExoskeletonJointHandle::MovementDirection::BOTH;
        return 0;
    }
    return -1;
}

String getArg(const String& args, const size_t argIdx) {
    size_t i{0};
    String arg = args;
    while (i < argIdx) {
        int idx = arg.indexOf(' ');
        if(idx < 0) {
            return "";
        }
        arg = arg.substring(idx + 1);
        while (arg.length() > 0 && arg.charAt(0) == ' ') {
            arg = arg.substring(1);
        }
        i++;
    }
    int endIdx = arg.indexOf(' ');
    if (endIdx < 0) {
        return arg;
    }
    arg = arg.substring(0, endIdx);
    return arg;
}

bool isInt(const String& nr) {
    bool first = true;
    bool requireAdditionalChar = false;

    for(char c : nr) {
        if(first) {
            first = false;
            if(c == '-') {
                requireAdditionalChar = true;
                continue;
            }
        }
        if(!isDigit(c)) {
            return false;
        }
        requireAdditionalChar = false;
    }
    return !requireAdditionalChar && !first;
}

bool isFloat(const String& nr) {
    bool sawPoint = false;
    bool first = true;
    bool requireAdditionalChar = false;
    for(char c : nr) {
        if(c == '.' && !first && !requireAdditionalChar) {
            if(sawPoint) {
                return false;
            }
            sawPoint = true;
            requireAdditionalChar = true;
            continue;
        }

        if(first) {
            first = false;
            if(c == '-') {
                requireAdditionalChar = true;
                continue;
            }
        }

        if(!isDigit(c)) {
            return false;
        } else {
            requireAdditionalChar = false;
        }
    }
    return !requireAdditionalChar && !first;
}
