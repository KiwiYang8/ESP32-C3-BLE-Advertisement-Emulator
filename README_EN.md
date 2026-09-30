# ESP32-C3 BLE Advertising: Technical Guide

[5-Minute Quick Start](QUICKSTART_EN.md) · [Troubleshooting](docs/troubleshooting_EN.md) · [中文](README_CN.md) · [Home](README.md)

If you only want to get the example running, use [QUICKSTART_EN.md](QUICKSTART_EN.md).  
This page explains the core BLE ideas without repeating setup and troubleshooting instructions.

## 1. What the sketch does

Source:

```text
src/ESP32_C3_BLE_Emulator.ino
```

The ESP32-C3:

1. initializes NimBLE;
2. creates a laboratory GATT Primary Service `0xFFF0`;
3. sends a 31-byte legacy advertising packet;
4. puts the device name `ESP` in Scan Response;
5. advertises at approximately 100 ms intervals.

## 2. Why the main packet is 31 bytes

Legacy BLE Advertising allows up to:

```text
31 bytes
```

The example fills those 31 bytes:

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

It contains three AD structures:

| Field | AD Type | Purpose |
|---|---:|---|
| Flags | `0x01` | Basic BLE advertising flags |
| Manufacturer Specific Data | `0xFF` | Custom laboratory data |
| Complete 16-bit Service UUIDs | `0x03` | Advertised test service |

Because BLE UUID bytes are little-endian:

```text
F0 FF → 0xFFF0
```

## 3. Why the device name is in Scan Response

The primary packet is already full, so the name cannot be appended without changing it.

The example therefore uses:

```text
Main Advertising = 31-byte RAW
Scan Response     = ESP
```

The name `ESP` is encoded as:

```text
04 09 45 53 50
```

where:

- `09` = Complete Local Name
- `45 53 50` = ASCII `ESP`

## 4. Why nRF Connect may show more than 31 bytes

nRF Connect can display:

```text
Advertising + Scan Response
```

together.

So the displayed RAW data may be longer than 31 bytes even though the primary advertising packet itself is still 31 bytes.

## 5. Why the interval is set to 160

BLE advertising intervals use units of:

```text
0.625 ms
```

The sketch uses:

```cpp
adv->setAdvertisingInterval(160);
```

Therefore:

```text
160 × 0.625 ms = 100 ms
```

A scanner may report values around 101–104 ms; small variations are normal.

## 6. GATT Service and Advertising are different layers

The example creates:

```text
GATT Primary Service: 0xFFF0
```

and also advertises the same UUID.

Conceptually:

```text
Advertising
= device discovery information broadcast to nearby scanners

GATT
= services available after a client connects
```

The project keeps GATT intentionally minimal.

## 7. Recommended debugging order

```text
Upload works
↓
Name-only BLE is discoverable
↓
Add the 31-byte RAW packet
↓
Add Scan Response
↓
Check GATT
```

For concrete failures, see:

[docs/troubleshooting_EN.md](docs/troubleshooting_EN.md)

## 8. Scope

For BLE protocol learning, devices you own, interoperability testing, and authorized laboratory simulation.
