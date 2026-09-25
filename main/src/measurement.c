#include "measurement.h"
#include <math.h>

#define WINDOW_SIZE 100U

static ac_sample_t samples[WINDOW_SIZE];
static uint32_t count;
static measurement_t latest;

void measurement_reset(void)
{
    count = 0U;
    latest = (measurement_t){0};
}

void measurement_push_sample(const ac_sample_t *sample)
{
    if (sample == NULL) return;

    samples[count % WINDOW_SIZE] = *sample;
    count++;

    if (count < WINDOW_SIZE) return;

    float sum_v2 = 0.0f;
    float sum_i2 = 0.0f;
    float sum_p = 0.0f;

    for (uint32_t i = 0; i < WINDOW_SIZE; ++i) {
        const float v = samples[i].voltage;
        const float i_a = samples[i].current;
        sum_v2 += v * v;
        sum_i2 += i_a * i_a;
        sum_p += v * i_a;
    }

    latest.vrms = sqrtf(sum_v2 / WINDOW_SIZE);
    latest.irms = sqrtf(sum_i2 / WINDOW_SIZE);
    latest.real_power_w = sum_p / WINDOW_SIZE;
    latest.apparent_power_va = latest.vrms * latest.irms;
    latest.power_factor =
        (latest.apparent_power_va > 0.0001f)
        ? latest.real_power_w / latest.apparent_power_va
        : 0.0f;

    if (latest.power_factor > 1.0f) latest.power_factor = 1.0f;
    if (latest.power_factor < -1.0f) latest.power_factor = -1.0f;
}

int measurement_get_snapshot(measurement_t *out)
{
    if (out == NULL || count < WINDOW_SIZE) return -1;
    *out = latest;
    return 0;
}
