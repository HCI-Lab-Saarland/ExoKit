

#ifndef VIBRATIONTEST_H
#define VIBRATIONTEST_H
#include <exo/ExoskeletonJointActiveHandle.h>

class VibrationTest: public IReaction {
private:
    ExoskeletonJointActiveHandle* c_joint;

    uint8_t c_frequency = 65; // 65 Hz
    float c_amplitude = 1; //1 deg
    int c_duration_ms = 1000; // internal test dummy, 100 ms vibration duration
    int c_repetitions = 0;
    int c_repetitions_counter = 0;
    int32_t velocity_required = 0;
    float period = 0;
    unsigned long c_start_ms = 0;

    bool c_lockStateAtStartup{};
    OperatingMode c_lockOPatStartup{};
    void runLoop() override;

protected:
    bool finishCondition() override;
    void startup() override;
    void prepare() override;

public:
    void shutdown(bool isCancel) override;
    VibrationTest();
    void configure(ExoskeletonJointActiveHandle& joint, uint8_t frequency, float amplitude); // int duration
};

#endif //VIBRATIONTEST_H
