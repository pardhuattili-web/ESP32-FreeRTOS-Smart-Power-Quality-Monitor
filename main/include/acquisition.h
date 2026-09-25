#ifndef ACQUISITION_H
#define ACQUISITION_H
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "measurement.h"
extern QueueHandle_t g_sample_queue;
void acquisition_start(void);
#endif
