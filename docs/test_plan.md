# Test Plan

## Calculation Tests

| ID | Input | Expected |
|---|---|---|
| M01 | Constant voltage samples | Vrms equals input magnitude |
| M02 | Constant current samples | Irms equals input magnitude |
| M03 | Known resistive load | PF approaches 1 |
| M04 | Zero current | Apparent power = 0 and PF handled safely |
| M05 | Known sine wave | RMS matches analytical value within tolerance |

## RTOS Tests

| ID | Test | Expected |
|---|---|---|
| R01 | Acquisition queue fills | Overflow is detected/handled |
| R02 | Processing delay injected | System remains stable |
| R03 | Telemetry blocked | Acquisition continues |
| R04 | Task restart | System recovers cleanly |

## Fault Tests

| ID | Test | Expected |
|---|---|---|
| F01 | Under-voltage value | UV event |
| F02 | Over-voltage value | OV event |
| F03 | Over-current value | OC event |
| F04 | Low PF value | LPF event |
| F05 | Invalid ADC sample | ADC event |

## Network Tests

| ID | Test | Expected |
|---|---|---|
| N01 | Wi-Fi disconnect | Automatic recovery |
| N02 | MQTT broker unavailable | Acquisition continues |
| N03 | Broker returns | Telemetry resumes |
| N04 | Malformed payload path | Application remains stable |

## Safety / Validation Status

This software is not a substitute for an electrically safe measurement system. Hardware validation must use an isolated and appropriately rated sensing front-end.

The repository should only claim measured accuracy after calibration and controlled testing.
