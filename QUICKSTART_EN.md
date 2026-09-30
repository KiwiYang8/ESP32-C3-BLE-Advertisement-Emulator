# 5-Minute Quick Start: ESP32-C3 BLE Advertising

[中文](QUICKSTART_CN.md) · [Full English Guide](README_EN.md) · [Home](README.md)

This guide has one goal: **get the ESP32-C3 advertising over BLE and visible in nRF Connect.**

## What you need

- ESP32-C3 SuperMini
- USB-C cable with data support
- Arduino IDE 2.x
- Android phone + nRF Connect

## Step 1: Install ESP32 board support

Arduino IDE → **Boards Manager**, search for:

```text
esp32
```

Install:

```text
esp32 by Espressif Systems
```

## Step 2: Install NimBLE-Arduino

Arduino IDE → **Library Manager**, search for:

```text
NimBLE-Arduino
```

NimBLE-Arduino 2.x is recommended.

## Step 3: Select the board

Select:

```text
ESP32C3 Dev Module
```

Then select the corresponding COM port.

Start with:

```text
Upload Speed: 115200
Serial Monitor: 115200
```

## Step 4: Open the sketch

Open:

```text
src/ESP32_C3_BLE_Emulator.ino
```

Compile and upload.

If upload stays at:

```text
Connecting...
```

try:

```text
Hold BOOT
→ press RST
→ release RST
→ release BOOT
→ upload again
```

## Step 5: Open Serial Monitor

Use:

```text
115200 baud
```

Expected output is similar to:

```text
BLE advertising STARTED
Device Name  : ESP
Service UUID : FFF0
Interval     : ~100 ms
```

## Step 6: Scan with nRF Connect

Open nRF Connect → SCAN.

Search for:

```text
ESP
```

If it appears, the full chain works:

```text
Arduino setup     ✓
ESP32-C3          ✓
NimBLE            ✓
BLE advertising   ✓
Phone scanning    ✓
```

## Step 7: Inspect RAW data

Open the device and inspect RAW advertising data.

The name `ESP` is placed in Scan Response, so the main 31-byte advertising packet remains unchanged.

## Something went wrong?

See:

[Troubleshooting](docs/troubleshooting_EN.md)

For packet structure:

[BLE Advertising Packet Notes](docs/ble_packet_EN.md)

For the full explanation:

[Full English Guide](README_EN.md)
