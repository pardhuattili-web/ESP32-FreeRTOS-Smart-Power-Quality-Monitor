# Firmware Application

This directory contains the ESP-IDF application layer.

The current scaffold supports **safe simulated/low-voltage sample input** for validating the FreeRTOS and measurement architecture before integrating an isolated sensing front-end.

## Build

From the repository root after creating a standard ESP-IDF project environment:

```bash
idf.py set-target esp32
idf.py build
idf.py flash
idf.py monitor
```

The repository intentionally does not include Wi-Fi credentials, broker credentials, or device secrets.
