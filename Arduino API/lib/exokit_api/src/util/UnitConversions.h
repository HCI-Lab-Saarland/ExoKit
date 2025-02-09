#ifndef UNITCONVERSIONS_H
#define UNITCONVERSIONS_H

/**
 * Converts revolutions per minute (RPM) to degrees per second.
 * @param rpm The speed in revolutions per minute.
 * @return The equivalent speed in degrees per second.
 */
float rpm2degsec(float rpm);

/**
 * Converts degrees per second to revolutions per minute.
 * @param degsec The speed in degrees per second.
 * @return The equivalent speed in revolutions per minute.
 */
float degsec2rpm(float degsec);

/**
 * Converts hertz (Hz) to revolutions per minute.
 * @param hz The frequency in hertz.
 * @return The equivalent in revolutions per minute.
 */
float hz2rpm(float hz);

/**
 * Converts revolutions per minute to hertz (Hz).
 * @param rpm The speed in revolutions per minute.
 * @return The equivalent frequency in hertz.
 */
float rpm2hz(float rpm);

/**
 * Converts angular velocity from radians per second to degrees per second.
 * @param radsec The angular velocity in radians per second.
 * @return The equivalent angular velocity in degrees per second.
 */
float radsec2degsec(float radsec);

/**
 * Converts angular velocity from degrees per second to radians per second.
 * @param degsec The angular velocity in degrees per second.
 * @return The equivalent angular velocity in radians per second.
 */
float degsec2radsec(float degsec);

#endif //UNITCONVERSIONS_H
