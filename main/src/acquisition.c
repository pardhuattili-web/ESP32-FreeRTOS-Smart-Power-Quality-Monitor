#include "acquisition.h"
#include "freertos/task.h"
#include "esp_timer.h"

QueueHandle_t g_sample_queue;

static void acquisition_task(void *arg)
{
    (void)arg;
    const TickType_t period = pdMS_TO_TICKS(10);

    while (1) {
        /*
         * Replace this deterministic source with ESP32 ADC/timer sampling.
         * Values below are low-voltage simulated signals for firmware testing.
         */
        ac_sample_t s = {
            .voltage = 12.0f,
            .current = 1.0f,
            .timestamp_us = (uint32_t)esp_timer_get_time()
        };

        (void)xQueueSend(g_sample_queue, &s, 0);
        vTaskDelay(period);
    }
}

void acquisition_start(void)
{
    g_sample_queue = xQueueCreate(64, sizeof(ac_sample_t));
    configASSERT(g_sample_queue != NULL);
    xTaskCreate(acquisition_task, "acquisition", 4096, NULL, 7, NULL);
}
