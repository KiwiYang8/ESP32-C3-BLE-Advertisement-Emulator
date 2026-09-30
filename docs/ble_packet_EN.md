# BLE Advertising Packet Notes

[中文版](ble_packet_CN.md)

## The 31-byte legacy advertising limit

Legacy BLE advertising provides up to 31 bytes for the primary advertising data. This example uses all 31 bytes, so the device name is moved to Scan Response rather than appended to the main packet.

## Example main advertisement

```text
02 01 1A
17 FF 00 01 B5 00 02 73 EB 33 C8 00 00 00
      0F 08 42 4F 1F 01 10 00 00 00
03 03 3C FE
```

### 1. Flags

```text
02 01 1A
```

- `02`: length of the following Type + Data;
- `01`: AD Type = Flags;
- `1A`: Flags value.

### 2. Manufacturer Specific Data

```text
17 FF ...
```

- `17`: length of Type + Data;
- `FF`: Manufacturer Specific Data;
- remaining bytes are the example laboratory payload.

### 3. 16-bit Service UUID

```text
03 03 3C FE
```

- `03`: length;
- `03`: Complete List of 16-bit Service UUIDs;
- `3C FE`: little-endian representation of `0xFE3C`.

## Scan Response

For easy identification in nRF Connect, the device name is:

```text
ESP
```

The corresponding Name AD Structure is:

```text
04 09 45 53 50
```

`09` means Complete Local Name and `45 53 50` is ASCII `ESP`.

## Debugging strategy

First verify that a minimal name-only BLE advertisement is discoverable. Then add the custom 31-byte payload. This separates radio/environment problems from custom-payload problems.
