# ESP32-C3 + Arduino + NimBLE Troubleshooting

[中文](troubleshooting_CN.md) · [Quick Start](../QUICKSTART_EN.md) · [Full Guide](../README_EN.md)

This page records the most common problems encountered while bringing up an ESP32-C3 SuperMini with Arduino IDE and NimBLE-Arduino.

## 1. Arduino IDE only shows “ESP32 Family Device”

If `ESP32C3 Dev Module` is missing, install:

```text
esp32 by Espressif Systems
```

Then select:

```text
Tools → Board → esp32 → ESP32C3 Dev Module
```

## 2. Compilation only shows `exit status 1`

Switch from Serial Monitor to:

```text
Output
```

Compile again and look for the first real compiler message, such as:

```text
error: ...
fatal error: ...
no matching function ...
not declared in this scope
```

If no useful error appears, verify the ESP32 core and board definition first.

## 3. Serial repeatedly prints `invalid header: 0xffffffff`

This generally means the ROM bootloader did not find a valid image in flash.

Try, in order:

1. select `ESP32C3 Dev Module`;
2. lower Upload Speed to `115200`;
3. perform a full flash erase if needed;
4. enter download mode with BOOT + RST;
5. upload again;
6. confirm that write and verification complete successfully.

## 4. Upload stays at `Connecting...`

Enter download mode manually:

```text
Hold BOOT
→ press RST
→ release RST
→ release BOOT
```

Then upload again.

Windows may enumerate a new COM port after reset, so check the port again.

## 5. USB appears unstable

Distinguish three cases:

### A. COM port disappears

Check the cable, USB port, Type-C connector, hub, and power.

### B. COM port remains but upload fails

Check download mode, selected board, and upload speed.

### C. Upload works but the board repeatedly disconnects

Check for crashes, Guru Meditation messages, and reboot loops.

## 6. nRF Connect cannot find the ESP32-C3

First use a minimal name-only BLE advertisement such as:

```text
ESP32C3-TEST
```

If it is visible, the board, BLE radio, NimBLE stack, and phone scanning path are working. Then restore the custom advertising payload step by step.

## 7. Why is the name not in the main packet?

Legacy advertising is limited to:

```text
31 bytes
```

If the packet is already full, adding a name changes the original payload.

This project therefore uses:

```text
Main Advertising = 31-byte RAW
Scan Response     = Device Name
```

## 8. Why does nRF Connect RAW appear longer than 31 bytes?

nRF Connect may display:

```text
Advertising
+
Scan Response
```

together.

The name `ESP`, for example, adds:

```text
04 09 45 53 50
```

The primary advertising packet itself is still 31 bytes.

## 9. Why is the measured interval around 101–104 ms?

The code requests:

```text
160 × 0.625 ms = 100 ms
```

Small differences observed by the scanner are normal.

## 10. Recommended debugging order

```text
ESP32 core
↓
Board definition
↓
COM port
↓
Minimal upload
↓
Minimal BLE name advertisement
↓
Visible in nRF Connect
↓
Custom RAW
↓
Scan Response
↓
GATT service
```

Change one variable at a time.
