# Arduino IDE and ESP32-C3 Setup

[中文版](setup_CN.md)

## 1. Install the ESP32 core

In Arduino IDE → Boards Manager, search for:

```text
esp32
```

Install:

```text
esp32 by Espressif Systems
```

If `ESP32C3 Dev Module` is missing, the Espressif Arduino core is usually not installed correctly.

## 2. Install NimBLE-Arduino

Arduino IDE → Library Manager, search for:

```text
NimBLE-Arduino
```

NimBLE-Arduino 2.x is recommended.

## 3. Select the board

```text
Tools → Board → esp32 → ESP32C3 Dev Module
```

Select the correct COM port.

## 4. Recommended configuration

```text
Board: ESP32C3 Dev Module
CPU Frequency: 160 MHz
Flash Size: 4 MB
Upload Speed: 115200
Serial Monitor: 115200 baud
```

## 5. Download mode

If upload remains stuck at `Connecting...`:

1. hold BOOT;
2. press and release RST;
3. release BOOT;
4. re-select the COM port if Windows enumerated a new one;
5. upload again.

## 6. `invalid header: 0xffffffff`

If this is printed repeatedly, check:

- that `ESP32C3 Dev Module` is selected;
- that a complete upload actually succeeded;
- whether a full flash erase is needed;
- that the USB cable supports data;
- whether the COM port changed after reset.
