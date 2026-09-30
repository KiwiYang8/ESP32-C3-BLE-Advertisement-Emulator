# BLE Advertising 数据包说明

[English version](ble_packet_EN.md)

## Legacy Advertising 的 31-byte 限制

传统 BLE Advertising 主数据区最大为 31 bytes。本项目示例恰好使用 31 bytes，因此设备名称放到 Scan Response。

## 示例主广播

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

- `02`: 后续字段长度；
- `01`: AD Type = Flags；
- `06`: 示例 Flags 值。

### 2. Manufacturer Specific Data

```text
17 FF ...
```

- `17`: 后续 Type + Data 长度；
- `FF`: Manufacturer Specific Data；
- `FF FF`: 实验占位 Company Identifier；
- 后续为通用实验 Payload。

### 3. 16-bit Service UUID

```text
03 03 F0 FF
```

- `03`: 长度；
- `03`: Complete List of 16-bit Service UUIDs；
- `F0 FF`: 小端序，对应 `0xFFF0`。

## Scan Response

设备名 `ESP` 对应：

```text
04 09 45 53 50
```

其中 `09` 是 Complete Local Name，`45 53 50` 为 ASCII `ESP`。
