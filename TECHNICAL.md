# Technical Notes / 原理说明

[Home / 主页](README.md) · [Troubleshooting / 排错](TROUBLESHOOTING.md)

## 1. 31-byte Advertising

Legacy BLE 主 Advertising 最大为 **31 bytes**.  
Legacy BLE primary advertising data is limited to **31 bytes**.

本项目示例 / Example:

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

| AD Type | Meaning / 含义 |
|---|---|
| `0x01` | Flags |
| `0xFF` | Manufacturer Specific Data |
| `0x03` | Complete 16-bit Service UUIDs |

`F0 FF` uses BLE little-endian byte order and represents `0xFFF0`.  
`F0 FF` 按 BLE 小端序表示 `0xFFF0`。

## 2. Why Scan Response? / 为什么用 Scan Response？

主包已经占满 31 bytes，因此设备名 `ESP` 放到 Scan Response。  
The main packet is full, so the device name `ESP` is placed in Scan Response.

```text
Main Advertising = 31-byte RAW
Scan Response     = ESP
```

`ESP`:

```text
04 09 45 53 50
```

`09` = Complete Local Name; `45 53 50` = ASCII `ESP`.

nRF Connect may display Advertising + Scan Response together, so the shown RAW data can be longer than 31 bytes.  
nRF Connect 可能把两部分一起显示，因此界面中的 RAW 总长度可能超过 31 bytes。

## 3. Advertising interval / 广播周期

```cpp
adv->setAdvertisingInterval(160);
```

BLE unit / BLE 单位:

```text
0.625 ms
```

Therefore / 因此:

```text
160 × 0.625 ms = 100 ms
```

Scanner readings around 101–104 ms are normal.  
扫描端显示约 101–104 ms 属于正常波动。

## 4. Advertising vs GATT

```text
Advertising = discovery data broadcast nearby
Advertising = 面向周围设备的发现信息

GATT = services available after connection
GATT = 建立连接后可访问的服务结构
```

The example creates a minimal GATT Primary Service `0xFFF0` and also advertises the same UUID.  
示例创建最简单的 `0xFFF0` GATT Primary Service，并在广播中发布同一 UUID。

## 5. Debugging rule / 调试原则

```text
Upload works
→ Name-only BLE works
→ Add RAW
→ Add Scan Response
→ Check GATT
```

一次只改一个变量。  
Change one variable at a time.
