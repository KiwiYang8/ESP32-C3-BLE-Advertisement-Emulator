# ESP32-C3 BLE Advertisement Emulator & Compatibility Testing Tool

[中文](README_CN.md) | [Home](README.md)

## 1. Introduction

This project documents a BLE advertising experiment built with **ESP32-C3 / ESP32-C3 SuperMini + Arduino IDE + NimBLE-Arduino 2.x**.

It focuses on:

- constructing legacy BLE advertising packets;
- sending custom Manufacturer Specific Data;
- advertising a 16-bit Service UUID;
- placing a device name in Scan Response when the 31-byte advertising packet is already full;
- creating a simple GATT Primary Service;
- validating RAW advertising data with nRF Connect.

The project originated from an authorized, closed-lab BLE peripheral interoperability experiment. The example payload is for protocol learning and testing; it does not include authentication secrets, dynamic tokens, or server credentials.

## 2. Hardware and software

### Hardware

- ESP32-C3 SuperMini or another ESP32-C3 board
- USB-C cable with data support
- Android phone
- nRF Connect

### Software

- Arduino IDE 2.x
- `esp32 by Espressif Systems`
- NimBLE-Arduino 2.x

## 3. Arduino IDE configuration

Recommended board:

```text
ESP32C3 Dev Module
```

Typical settings:

```text
CPU Frequency: 160 MHz
Flash Size: 4 MB
Upload Speed: 115200 or 460800
Serial Monitor: 115200 baud
```

If upload is unreliable, reduce Upload Speed to `115200`.

Detailed setup: [docs/setup_EN.md](docs/setup_EN.md)

## 4. What the example does

Source:

```text
src/ESP32_C3_BLE_Emulator.ino
```

The sketch:

1. initializes NimBLE;
2. creates a `0xFE3C` Primary Service;
3. transmits a 31-byte legacy advertising payload;
4. publishes the short name `ESP` in Scan Response so the board is easy to locate among many BLE devices;
5. uses an advertising interval of approximately 100 ms.

The main advertising payload and the device name are separated: the 31-byte packet remains unchanged while the name is carried only in Scan Response.

## 5. BLE packet structure

Example main advertisement:

```text
02 01 1A
17 FF 00 01 B5 00 02 73 EB 33 C8 00 00 00
      0F 08 42 4F 1F 01 10 00 00 00
03 03 3C FE
```

Meaning:

| AD Type | Meaning |
|---|---|
| `0x01` | Flags |
| `0xFF` | Manufacturer Specific Data |
| `0x03` | Complete List of 16-bit Service UUIDs |

Because BLE UUID bytes are little-endian, `3C FE` represents UUID `0xFE3C`.

The name `ESP` is placed in Scan Response:

```text
04 09 45 53 50
```

Here, `0x09` is Complete Local Name and `45 53 50` is ASCII `ESP`.

More details: [docs/ble_packet_EN.md](docs/ble_packet_EN.md)

## 6. Usage

1. Install Arduino IDE.
2. Install `esp32 by Espressif Systems`.
3. Install NimBLE-Arduino 2.x.
4. Select `ESP32C3 Dev Module`.
5. Open `src/ESP32_C3_BLE_Emulator.ino`.
6. Compile and upload.
7. Open Serial Monitor at `115200`.
8. Start scanning in nRF Connect.
9. Search for the device name `ESP`.
10. Open RAW data and compare Advertising and Scan Response.

## 7. Expected nRF Connect result

You should see values similar to:

```text
Complete Local Name: ESP
Complete list of 16-bit Service UUIDs: 0xFE3C
Advertising interval: about 100 ms
```

The main Advertising RAW bytes should match `RAW_ADV` in the sketch.

## 8. Troubleshooting

### Arduino IDE only shows “ESP32 Family Device”

Install:

```text
esp32 by Espressif Systems
```

Then explicitly select:

```text
ESP32C3 Dev Module
```

### Serial repeatedly shows `invalid header: 0xffffffff`

This usually means the flash does not contain a valid boot image, the firmware was not written correctly, or the board definition/upload configuration is wrong. Try:

- selecting the correct board;
- lowering Upload Speed;
- performing one full flash erase;
- forcing download mode with BOOT + RST and uploading again.

### nRF Connect cannot find the ESP32-C3

First flash a minimal BLE example that advertises only a device name. If it can be found, the board, radio, and NimBLE environment are working; then restore the custom RAW payload step by step.

### Why is the name in Scan Response?

Legacy advertising allows up to 31 bytes in the main packet. This example already uses all 31 bytes, so the Local Name cannot be appended there. Scan Response carries the name without changing the main advertising payload.

## 9. Scope and security

Use this repository only for:

- BLE protocol learning;
- devices you own;
- authorized interoperability testing;
- closed-lab peripheral simulation.

Do not use identity data, authentication material, or dynamic tokens obtained from unauthorized devices to impersonate production systems. Do not use this project to bypass attendance, access control, authentication, facial verification, BLE pairing/encryption, or server-side validation.

## 10. License

MIT License. See [LICENSE](LICENSE).
