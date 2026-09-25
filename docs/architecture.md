# Firmware Architecture

## Runtime Flow

```
ADC / Timer
    |
    v
Acquisition Task
    |
    v
Sample Queue
    |
    v
Processing Task
    |-------------------|
    v                   v
Measurement Snapshot   Fault Monitor
    |                   |
    +---------+---------+
              v
       Telemetry Queue
              |
              v
         MQTT Task
              |
              v
          Broker
```

## Responsibilities

### acquisition
Owns sampling cadence and sensor normalization. It should never perform network operations or long blocking calculations.

### measurement
Owns RMS, real-power, apparent-power, and power-factor calculations. It operates on a defined sample window.

### fault_monitor
Evaluates measurements against configured limits and creates structured fault events.

### telemetry
Owns Wi-Fi/MQTT interaction and publishes immutable measurement snapshots. Reconnect logic belongs here rather than in acquisition or signal-processing code.

## Concurrency Rules

- Use FreeRTOS queues for ownership transfer between tasks.
- Avoid sharing mutable measurement structures without synchronization.
- Keep ADC sampling deterministic.
- Do not call MQTT APIs from time-critical acquisition code.
- Use bounded queues and explicit overflow handling.

## Suggested Priorities

| Task | Priority | Notes |
|---|---:|---|
| Acquisition | High | Time-sensitive sampling |
| Processing | Medium-high | CPU-heavy calculations |
| Fault monitor | Medium | Safety/event evaluation |
| Telemetry | Low-medium | Network latency is acceptable |

Priorities are starting points and should be tuned after measuring CPU usage and queue latency.
