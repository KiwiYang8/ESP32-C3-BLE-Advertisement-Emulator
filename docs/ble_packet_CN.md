# BLE Advertising 数据包说明

[English version](ble_packet_EN.md)

## Legacy Advertising 的 31-byte 限制

传统 BLE Advertising 主数据区最大为 31 bytes。本项目示例恰好使用 31 bytes，因此设备名称不再塞入主广播，而放到 Scan Response。

## 示例主广播

```text
02 01 1A
17 FF 00 01 B5 00 02 73 EB 33 C8 00 00 00
      0F 08 42 4F 1F 01 10 00 00 00
03 03 3C FE
```

拆分后：

### 1. Flags

```text
02 01 1A
```

- `02`: 后续字段长度；
- `01`: AD Type = Flags；
- `1A`: Flags 值。

### 2. Manufacturer Specific Data

```text
17 FF ...
```

- `17`: 后续 Type + Data 长度；
- `FF`: Manufacturer Specific Data；
- 后续为示例实验 Payload。

### 3. 16-bit Service UUID

```text
03 03 3C FE
```

- `03`: 长度；
- `03`: Complete List of 16-bit Service UUIDs；
- `3C FE`: 小端序，对应 `0xFE3C`。

## Scan Response

为了便于在 nRF Connect 中定位开发板，使用：

```text
ESP
```

NimBLE 生成的 Name AD Structure 为：

```text
04 09 45 53 50
```

其中 `09` 是 Complete Local Name，`45 53 50` 为 ASCII `ESP`。

## 调试建议

先确认最小 BLE Name 广播可以被发现，再加入自定义 31-byte RAW。这样可以区分“BLE 环境问题”和“自定义 Payload 问题”。
