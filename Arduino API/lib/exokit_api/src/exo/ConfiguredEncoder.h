#ifndef CHI25_EXOSKELETON_API_CONFIGUREDENCODER_H
#define CHI25_EXOSKELETON_API_CONFIGUREDENCODER_H


#include "TaskTypes.h"

class ConfiguredEncoder;

class ConfiguredEncoderVelocitySampleExecutable: public Executable {
private:
    ConfiguredEncoder& encoder;
public:
    /**
     * Constructor for ConfiguredEncoderVelocitySampleExecutable. Links the executable object to the provided ConfiguredEncoder instance.
     * @param encoder The encoder instance to associate with this executable.
     */
    explicit ConfiguredEncoderVelocitySampleExecutable(ConfiguredEncoder& encoder);
    
    /**
     * Executes the velocity sampling function.
     */
    void exec() override;
};

class ConfiguredEncoder {
    friend ConfiguredEncoderVelocitySampleExecutable;
private:
    int potiPin;
    int potiMaxRoM;
    float zeroPos;

    ConfiguredEncoderVelocitySampleExecutable executable;
    bool isVelocityTracking{false};
    taskid_t velocityTrackingTaskId{0};
    float velocityPrevPosition[2]{0, 0};
    size_t velocityReferencePositionIdx{0};
    unsigned long velocityPrevPositionTimestamp[2]{0, 0};
    unsigned long maxVelocityReferenceAgeMs{100};
    void sampleVelocityReference();
    float convertRawToAngle(int raw) const;

public:
     /**
     Initializes the encoder with a potentiometer pin.
     * Also enables velocity tracking by default.
     *
     * @param analogPotiPin The analog pin connected to the potentiometer.
     * @param countsPerRevolution.
     */
    ConfiguredEncoder(int analogPotiPin, int countsPerRevolution);

    /**
     * Destructor for the ConfiguredEncoder class.
     * Disables velocity tracking before destroying the object.
     */
    ~ConfiguredEncoder();
    ConfiguredEncoder& operator=(const ConfiguredEncoder& other) = delete;
    ConfiguredEncoder(const ConfiguredEncoder& other) = delete;

    /**
     * Reads the raw analog value from the potentiometer.
     * @return The raw analog reading.
     */
    int readRaw();

    /**
     * Reads the current angle of the potentiometer.
     * Converts the raw analog input value to an angle and subtracts the zero position offset.
     * @return The current angle in degrees.
     */
    float readAngle();

    /**
     * Sets the zero position of the encoder. This is used to calibrate the encoder.
     * @param currentAngleRelativeZero The current angle relative to the new zero position.
     */
    void tare(float currentAngleRelativeZero);

    /**
     * Gets the current velocity.
     * @return The velocity in degrees per second.
     */
    float getVelocity();

    /**
     * Enables or disables velocity tracking. If enabled, it schedules a task to periodically sample velocity reference points.
     * If disabled, it cancels the velocity tracking task.
     * @param isEnable True to enable velocity tracking, false to disable it.
     */
    void enableVelocityTracking(bool isEnable);

    /**
     * Loads encoder configuration from EEPROM.
     * Reads the stored zero position from EEPROM memory.
     * @param offset The EEPROM memory address.
     * @return The next available EEPROM address.
     */
    int16_t loadConfigFromEEPROM(int16_t i);

    /**
     * Persists encoder configuration, including zero position, to EEPROM.
     * @param offset The EEPROM memory address to store the configuration.
     * @return The next available EEPROM address after storing the data.
     */
    int16_t persistConfigToEEPROM(int16_t offset);
};


#endif //CHI25_EXOSKELETON_API_CONFIGUREDENCODER_H
