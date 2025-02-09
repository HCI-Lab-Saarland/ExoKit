#include "DebugSerial.h"


#if defined(ARDUINO_AVR_UNO)
    SoftwareSerial DEBUG_SERIAL = SoftwareSerial(7, 8);
#elif defined(ARDUINO_AVR_MEGA2560)
    HardwareSerial& DEBUG_SERIAL = Serial2;
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
    SerialUSB DEBUG_SERIAL = SerialUSB();
#else
    Serial DEBUG_SERIAL = Serial();
#endif
