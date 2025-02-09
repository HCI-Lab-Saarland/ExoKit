float rpm2degsec(float rpm) {
    // 1 RPM = 6 °/s
    return rpm * 6.0;
}

float degsec2rpm(float degsec) {
    // 1 RPM = 6 °/s
    return degsec / 6.0;
}

float hz2rpm(float hz) {
    // 1 Hz = 60 RPM
    return hz * 60.0;
}

float rpm2hz(float rpm) {
    // 1 Hz = 60 RPM
    return rpm / 60.0;
}

float radsec2degsec(float radsec) {
    // 1 rad/s = 57.29578 °/s
    return radsec * 57.3;
}

float degsec2radsec(float degsec) {
    // 1 rad/s = 57.29578 °/s
    return degsec / 57.3;
}
