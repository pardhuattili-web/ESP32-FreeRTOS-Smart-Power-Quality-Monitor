#ifndef TELEMETRY_H
#define TELEMETRY_H
#include "measurement.h"
#include "fault_monitor.h"
void telemetry_start(void);
void telemetry_publish_snapshot(const measurement_t *m, fault_code_t fault);
#endif
