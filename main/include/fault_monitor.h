#ifndef FAULT_MONITOR_H
#define FAULT_MONITOR_H
#include "measurement.h"
typedef enum {
    FAULT_NONE = 0,
    FAULT_UV,
    FAULT_OV,
    FAULT_OC,
    FAULT_LPF,
    FAULT_ADC,
    FAULT_NET
} fault_code_t;
fault_code_t fault_monitor_check(const measurement_t *m);
const char *fault_monitor_name(fault_code_t code);
#endif
