#include "telemetry.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "PQM";

static void telemetry_task(void *arg)
{
    (void)arg;

    while (1) {
        measurement_t m;
        if (measurement_get_snapshot(&m) == 0) {
            const fault_code_t fault = fault_monitor_check(&m);
            telemetry_publish_snapshot(&m, fault);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void telemetry_start(void)
{
    xTaskCreate(telemetry_task, "telemetry", 4096, NULL, 3, NULL);
}

void telemetry_publish_snapshot(const measurement_t *m, fault_code_t fault)
{
    if (m == NULL) return;

    ESP_LOGI(
        TAG,
        "Vrms=%.2f Irms=%.2f P=%.2fW S=%.2fVA PF=%.3f Fault=%s",
        m->vrms,
        m->irms,
        m->real_power_w,
        m->apparent_power_va,
        m->power_factor,
        fault_monitor_name(fault)
    );

    /*
     * Replace this logger with ESP-MQTT publishing:
     * - power_monitor/<device_id>/telemetry
     * - power_monitor/<device_id>/fault
     * - power_monitor/<device_id>/status
     */
}
