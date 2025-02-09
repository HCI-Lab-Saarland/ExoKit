#ifndef CHI25_EXOSKELETON_API_DEBUGSERIAL_H
#define CHI25_EXOSKELETON_API_DEBUGSERIAL_H

/**
 * Configures the debug serial port based on the target Arduino board.
 */

#if defined(ARDUINO_AVR_UNO)
    #include <HardwareSerial.h>
    extern HardwareSerial DEBUG_SERIAL;
#elif defined(ARDUINO_AVR_MEGA2560)
    #include <HardwareSerial.h>
    extern HardwareSerial& DEBUG_SERIAL;
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
    extern SerialUSB DEBUG_SERIAL;
#else
    extern SerialDEBUG_SERIAL;
#endif

/**
 * Prints a debug message.
 *
 * @tparam T The data type of the attribute value.
 * @tparam X The data type of the attribute name.
 * @param name The name of the attribute.
 * @param attr The value of the attribute.
 * @param addr The address associated with the attribute.
 */
template<typename T, typename X>
void writeDebugAttribute(X name, T attr, int addr) {
    DEBUG_SERIAL.print(F("Addr.: "));
    DEBUG_SERIAL.print(addr);
    DEBUG_SERIAL.print(F(", "));
    DEBUG_SERIAL.print(name);
    DEBUG_SERIAL.print(F(": "));
    DEBUG_SERIAL.println(attr);
}



#endif //CHI25_EXOSKELETON_API_DEBUGSERIAL_H
