# BLE Advertising Packet Notes

[中文版](ble_packet_CN.md)

## The 31-byte legacy advertising limit

Legacy BLE advertising provides up to 31 bytes for the primary advertising data. This example uses all 31 bytes, so the device name is placed in Scan Response.

## Example main advertisement

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

### 1. Flags

```text
02 01 06
```

- `02`: length of the following Type + Data;
- `01`: AD Type = Flags;
- `06`: example Flags value.

### 2. Manufacturer Specific Data

```text
17 FF ...
```

- `17`: length of Type + Data;
- `FF`: Manufacturer Specific Data;
- `FF FF`: laboratory placeholder Company Identifier;
- remaining bytes are generic lab data.

### 3. 16-bit Service UUID

```text
03 03 F0 FF
```

- `03`: length;
- `03`: Complete List of 16-bit Service UUIDs;
- `F0 FF`: little-endian representation of `0xFFF0`.

## Scan Response

Device name `ESP`:

```text
04 09 45 53 50
```

`09` means Complete Local Name and `45 53 50` is ASCII `ESP`.
