#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <stdint.h>
typedef struct {
    float vrms;
    float irms;
    float real_power_w;
    float apparent_power_va;
    float power_factor;
} measurement_t;
typedef struct {
    float voltage;
    float current;
    uint32_t timestamp_us;
} ac_sample_t;
void measurement_reset(void);
void measurement_push_sample(const ac_sample_t *sample);
int measurement_get_snapshot(measurement_t *out);
#endif
