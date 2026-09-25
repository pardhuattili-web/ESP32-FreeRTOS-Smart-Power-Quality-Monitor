# Measurement Model

## Sample Representation

The acquisition layer should convert raw ADC counts into engineering units before they enter the processing queue.

```c
typedef struct {
    float voltage;
    float current;
    uint32_t timestamp_us;
} ac_sample_t;
```

## Calculation Window

For N samples:

```
Vrms = sqrt((v1² + v2² + ... + vN²) / N)
Irms = sqrt((i1² + i2² + ... + iN²) / N)
```

Real power can be estimated from instantaneous samples:

```
P = mean(v[n] * i[n])
```

Apparent power:

```
S = Vrms * Irms
```

Power factor:

```
PF = P / S
```

Handle the S = 0 case explicitly.

## Calibration

Sensor-specific parameters should remain configurable:

- ADC reference/full-scale
- Voltage transducer ratio
- Current transducer ratio
- Offset
- Gain correction

Do not hard-code mains calibration constants without documenting the actual sensor and analog front-end.
