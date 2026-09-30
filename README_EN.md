# ESP32-C3 BLE Advertisement Emulator & Compatibility Testing Tool

[中文](README_CN.md) | [Home](README.md)

## 1. Introduction

This project documents a BLE advertising experiment built with **ESP32-C3 / ESP32-C3 SuperMini + Arduino IDE + NimBLE-Arduino 2.x**.

It focuses on:

- constructing legacy BLE advertising packets;
- sending custom Manufacturer Specific Data;
- advertising a 16-bit Service UUID;
- placing a device name in Scan Response when the 31-byte advertising packet is full;
- creating a simple GATT Primary Service;
- validating RAW advertising data with nRF Connect.

The repository uses a generic laboratory payload and UUID for protocol learning and interoperability testing.

## 2. Hardware and software

- ESP32-C3 SuperMini or another ESP32-C3 board
- USB-C cable with data support
- Android phone + nRF Connect
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

Detailed setup: [docs/setup_EN.md](docs/setup_EN.md)

## 4. What the example does

Source:

```text
src/ESP32_C3_BLE_Emulator.ino
```

The sketch:

1. initializes NimBLE;
2. creates generic lab Service `0xFFF0`;
3. transmits a 31-byte legacy advertising payload;
4. publishes short name `ESP` in Scan Response;
5. uses an advertising interval of approximately 100 ms.

## 5. BLE packet structure

Example main advertisement:

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

Meaning:

| AD Type | Meaning |
|---|---|
| `0x01` | Flags |
| `0xFF` | Manufacturer Specific Data |
| `0x03` | Complete List of 16-bit Service UUIDs |

Because BLE UUID bytes are little-endian, `F0 FF` represents UUID `0xFFF0`.

The name `ESP` is placed in Scan Response:

```text
04 09 45 53 50
```

More details: [docs/ble_packet_EN.md](docs/ble_packet_EN.md)

## 6. Usage

1. Install Arduino IDE.
2. Install `esp32 by Espressif Systems`.
3. Install NimBLE-Arduino 2.x.
4. Select `ESP32C3 Dev Module`.
5. Open the source sketch.
6. Compile and upload.
7. Open Serial Monitor at `115200`.
8. Scan for `ESP` in nRF Connect.
9. Inspect Advertising and Scan Response RAW data.

## 7. Troubleshooting

- Only “ESP32 Family Device” appears: install the Espressif ESP32 core and explicitly select `ESP32C3 Dev Module`.
- `invalid header: 0xffffffff`: verify the board, lower upload speed, and if necessary erase flash and enter download mode with BOOT + RST.
- nRF Connect cannot find the board: first verify a minimal name-only BLE example, then restore the RAW payload.
- Why use Scan Response for the name: the legacy primary advertising packet is limited to 31 bytes and this example already fills it.

## 8. Scope

For BLE protocol learning, devices you own, interoperability testing, and authorized laboratory simulation.

## 9. License

MIT License. See [LICENSE](LICENSE).
