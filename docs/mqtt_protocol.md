# MQTT Protocol

## Topics

```
power_monitor/<device_id>/telemetry
power_monitor/<device_id>/fault
power_monitor/<device_id>/status
```

## Telemetry

Example:

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

## Fault Event

Example:

```json
{
  "code": "OV",
  "value": 258.2,
  "threshold": 250.0,
  "timestamp": 1720000000
}
```

## Status Event

Example:

```json
{
  "device": "esp32-pqm-01",
  "wifi": true,
  "mqtt": true,
  "uptime_s": 3600
}
```

## Reliability

The client should:

- reconnect after Wi-Fi loss;
- reconnect after broker loss;
- avoid blocking acquisition tasks;
- use bounded payload buffers;
- publish only validated measurement snapshots;
- optionally enable TLS for production-like deployments.
