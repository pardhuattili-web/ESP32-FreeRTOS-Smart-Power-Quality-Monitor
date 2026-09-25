# ESP32 FreeRTOS Smart Power Quality Monitor

> **Embedded IoT project | ESP32 + FreeRTOS + ADC + MQTT**

A modular ESP32 monitoring system that acquires isolated voltage/current waveforms, calculates electrical measurements, detects abnormal operating conditions, and publishes telemetry over Wi-Fi/MQTT.

The firmware is structured around FreeRTOS tasks and queues so acquisition, signal processing, fault monitoring, and network communication remain decoupled.

> ⚠️ **Safety:** This project is intended for **isolated, low-voltage/safe measurement interfaces** during development. Do not connect ESP32 GPIO/ADC pins directly to mains voltage. Any mains-connected implementation requires appropriate isolation, protection, creepage/clearance, rated sensors, and qualified electrical design.

## Project Goals

- Sample voltage and current waveforms at a controlled rate.
- Calculate RMS voltage/current and apparent power.
- Estimate power factor from sampled waveforms.
- Detect over-voltage and over-current events.
- Move measurements between FreeRTOS tasks using queues.
- Publish telemetry through MQTT.
- Maintain local event/fault records.
- Demonstrate watchdog-based recovery and modular ESP-IDF design.

## System Architecture

```text
 Voltage Sensor ─┐
                 ├──> ADC Sampling Task
 Current Sensor ─┘          |
                            v
                    Measurement Queue
                            |
                            v
                   Signal Processing Task
                     |              |
                     v              v
              Measurement      Fault Monitor
                     |              |
                     +------+-------+
                            |
                            v
                    Telemetry Queue
                            |
                            v
                    MQTT/Wi-Fi Task
                            |
                            v
                       MQTT Broker
```

## Target Platform

| Item | Selection |
|---|---|
| MCU | ESP32 |
| Framework | ESP-IDF |
| Language | C |
| RTOS | FreeRTOS |
| Sampling | ADC + hardware timer |
| Connectivity | 2.4 GHz Wi-Fi |
| Protocol | MQTT |
| Debug | UART / ESP-IDF monitor |

## Repository Structure

```text
ESP32-FreeRTOS-Smart-Power-Quality-Monitor/
├── README.md
├── docs/
│   ├── architecture.md
│   ├── measurement_model.md
│   ├── mqtt_protocol.md
│   └── test_plan.md
└── main/
    ├── CMakeLists.txt
    ├── app_main.c
    ├── include/
    │   ├── measurement.h
    │   ├── acquisition.h
    │   ├── fault_monitor.h
    │   └── telemetry.h
    └── src/
        ├── acquisition.c
        ├── measurement.c
        ├── fault_monitor.c
        └── telemetry.c
```

## Measurements

The reference implementation uses sampled waveform data to derive:

```
Vrms  = sqrt( mean(v²) )
Irms  = sqrt( mean(i²) )
S     = Vrms × Irms
PF    = P / S
```

Where:

- **Vrms** = RMS voltage
- **Irms** = RMS current
- **S** = apparent power
- **P** = real power
- **PF** = power factor

The exact ADC scaling constants belong in the hardware configuration layer because the sensor/transducer and front-end determine the conversion.

## FreeRTOS Design

### Task 1 — Acquisition
Runs at a fixed sampling cadence and pushes normalized samples into the measurement pipeline.

### Task 2 — Signal Processing
Consumes samples, applies basic offset handling/filtering, and calculates electrical parameters.

### Task 3 — Fault Monitor
Checks measurement values against configurable thresholds and creates event records.

### Task 4 — Telemetry
Publishes the latest measurement snapshot and active faults through MQTT.

### Queueing

The reference design uses queues between acquisition, processing, and telemetry layers to keep tasks loosely coupled and avoid direct cross-task ownership of application data.

## Example MQTT Topics

```text
power_monitor/<device_id>/telemetry
power_monitor/<device_id>/fault
power_monitor/<device_id>/status
```

Example telemetry payload:

```json
{
  "vrms": 230.4,
  "irms": 1.82,
  "real_power_w": 390.5,
  "apparent_power_va": 419.3,
  "power_factor": 0.93,
  "fault": 0
}
```

## Fault Detection

Reference events:

| Code | Condition |
|---|---|
| `UV` | Under-voltage |
| `OV` | Over-voltage |
| `OC` | Over-current |
| `LPF` | Low power factor |
| `ADC` | ADC/acquisition fault |
| `NET` | Network/MQTT fault |

Thresholds must be configurable for the safe measurement setup being used.

## Development Roadmap

### Phase 1 — Acquisition
- [x] Repository structure
- [x] Measurement model
- [ ] ADC configuration
- [ ] Sampling timer
- [ ] Sensor scaling

### Phase 2 — Signal Processing
- [ ] RMS calculation
- [ ] Real-power calculation
- [ ] Apparent-power calculation
- [ ] Power-factor estimation
- [ ] Basic filtering

### Phase 3 — Real-Time System
- [ ] FreeRTOS acquisition task
- [ ] Processing task
- [ ] Fault monitor task
- [ ] Telemetry task
- [ ] Queue-based communication

### Phase 4 — Connectivity
- [ ] Wi-Fi station mode
- [ ] MQTT client
- [ ] Telemetry publishing
- [ ] Connection recovery
- [ ] Event publishing

### Phase 5 — Reliability
- [ ] Watchdog integration
- [ ] Sensor timeout detection
- [ ] Ring-buffer/event history
- [ ] Configuration persistence

## Validation

Recommended development progression:

1. Generate synthetic waveform samples in software.
2. Validate RMS/power calculations against known values.
3. Test FreeRTOS queue behavior under load.
4. Verify fault thresholds with controlled inputs.
5. Test MQTT disconnect/reconnect behavior.
6. Only then connect approved isolated measurement hardware.

Do not claim real mains measurement accuracy until the complete analog front-end, sensor calibration, isolation, and measurement procedure have been validated.

## Portfolio Skills Demonstrated

- Embedded C
- ESP-IDF
- FreeRTOS multitasking
- ADC acquisition
- Digital signal processing basics
- Inter-task communication
- Wi-Fi
- MQTT
- Fault detection
- Watchdog/recovery concepts
- Modular firmware architecture

## Future Extensions

- Web dashboard
- OTA firmware updates
- TLS-secured MQTT
- SD-card event logging
- Energy consumption (Wh/kWh) accumulation
- Modbus TCP gateway
- TinyML anomaly detection
- Multi-phase monitoring

## Author

**Pardhu Attili**

GitHub: [@pardhuattili-web](https://github.com/pardhuattili-web)

## Status

**Architecture + reference firmware scaffold**

Hardware and measurement accuracy should be marked **Not Yet Validated** until the intended sensor/front-end and test setup have been physically verified.
