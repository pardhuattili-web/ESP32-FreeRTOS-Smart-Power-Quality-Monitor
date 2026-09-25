#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "acquisition.h"
#include "measurement.h"
#include "telemetry.h"

static void processing_task(void *arg)
{
    (void)arg;
    ac_sample_t sample;
    measurement_reset();

    while (1) {
        if (xQueueReceive(g_sample_queue, &sample, portMAX_DELAY) == pdTRUE) {
            measurement_push_sample(&sample);
        }
    }
}

void app_main(void)
{
    acquisition_start();

    xTaskCreate(processing_task, "processing", 4096, NULL, 5, NULL);
    telemetry_start();
}
