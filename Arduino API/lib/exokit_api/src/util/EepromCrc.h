#ifndef CHI25_EXOSKELETON_API_EEPROMCRC_H
#define CHI25_EXOSKELETON_API_EEPROMCRC_H

#include <EEPROM.h>
#include <Arduino.h>

/**
 * Computes the CRC (Cyclic Redundancy Check) checksum for a range of bytes stored in EEPROM.
 * @param start The starting address in EEPROM from which to begin.
 * @param end The ending address in EEPROM.
 * @return The computed CRC.
 */
unsigned long eeprom_crc(int start, int end) {
    const unsigned long crc_table[16] = {
            0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };
    unsigned long crc = ~0L;
    for (int index = start ; index < min((int)EEPROM.length(), end)  ; ++index) {
        crc = crc_table[(crc ^ EEPROM[index]) & 0x0f] ^ (crc >> 4);
        crc = crc_table[(crc ^ (EEPROM[index] >> 4)) & 0x0f] ^ (crc >> 4);
        crc = ~crc;
    }
    return crc;
}

#endif //CHI25_EXOSKELETON_API_EEPROMCRC_H
