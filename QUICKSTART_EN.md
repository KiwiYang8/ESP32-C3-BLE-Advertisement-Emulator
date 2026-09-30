# 5-Minute Quick Start: ESP32-C3 BLE Advertising

[Technical Guide](README_EN.md) · [Troubleshooting](docs/troubleshooting_EN.md) · [中文](QUICKSTART_CN.md)

The only goal here is: **make the ESP32-C3 visible in nRF Connect.**

## 1. Prepare

- ESP32-C3 SuperMini
- USB-C cable with data support
- Arduino IDE 2.x
- Android phone + nRF Connect

## 2. Install two things

Arduino IDE → **Boards Manager**:

```text
esp32 by Espressif Systems
```

Arduino IDE → **Library Manager**:

```text
NimBLE-Arduino
```

NimBLE-Arduino 2.x is recommended.

## 3. Select the board

```text
ESP32C3 Dev Module
```

Select the matching COM port.

Start with:

```text
Upload Speed: 115200
Serial Monitor: 115200
```

## 4. Upload

Open:

```text
src/ESP32_C3_BLE_Emulator.ino
```

Compile and upload.

## 5. Check Serial Monitor

Use:

```text
115200 baud
```

Expected output:

```text
BLE advertising STARTED
Device Name  : ESP
Service UUID : FFF0
Interval     : ~100 ms
```

## 6. Verify with your phone

Open nRF Connect → SCAN → search for:

```text
ESP
```

If it appears, the full path is working.

## 7. Inspect RAW

Open `ESP` and inspect RAW data.

The device name is carried in Scan Response, so the primary advertising packet remains 31 bytes.

## Something went wrong?

See:

[Troubleshooting](docs/troubleshooting_EN.md)

For the 31-byte limit, Scan Response, and GATT/Advertising relationship:

[Technical Guide](README_EN.md)
