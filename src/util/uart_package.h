typedef struct {
    float target_rpm_[4];
    uint32_t sumcheck;
} rx_package_t;

typedef struct {
    float measured_rpm_[4];
    float magnetometer[3];
    uint32_t sumcheck;
} tx_package_t;

