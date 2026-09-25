#include "fault_monitor.h"

#define UV_LIMIT 10.5f
#define OV_LIMIT 14.5f
#define OC_LIMIT 8.0f
#define LPF_LIMIT 0.70f

fault_code_t fault_monitor_check(const measurement_t *m)
{
    if (m == NULL) return FAULT_ADC;
    if (m->vrms < UV_LIMIT) return FAULT_UV;
    if (m->vrms > OV_LIMIT) return FAULT_OV;
    if (m->irms > OC_LIMIT) return FAULT_OC;
    if (m->power_factor < LPF_LIMIT) return FAULT_LPF;
    return FAULT_NONE;
}

const char *fault_monitor_name(fault_code_t code)
{
    switch (code) {
    case FAULT_UV: return "UV";
    case FAULT_OV: return "OV";
    case FAULT_OC: return "OC";
    case FAULT_LPF: return "LPF";
    case FAULT_ADC: return "ADC";
    case FAULT_NET: return "NET";
    default: return "NONE";
    }
}
