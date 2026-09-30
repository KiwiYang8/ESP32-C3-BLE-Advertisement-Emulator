# ESP32-C3 BLE 广播：原理说明

[5 分钟快速上手](QUICKSTART_CN.md) · [踩坑与排错](docs/troubleshooting_CN.md) · [English](README_EN.md) · [主页](README.md)

如果你只想把程序跑起来，请直接看 [QUICKSTART_CN.md](QUICKSTART_CN.md)。  
这份文档只解释项目里最值得理解的几个 BLE 概念，不重复安装步骤和排错过程。

## 1. 程序做了什么

源码：

```text
src/ESP32_C3_BLE_Emulator.ino
```

运行后，ESP32-C3 会：

1. 初始化 NimBLE；
2. 创建一个实验用 GATT Primary Service `0xFFF0`；
3. 发送一个 31-byte Legacy Advertising；
4. 把设备名 `ESP` 放进 Scan Response；
5. 以约 100 ms 的周期持续广播。

## 2. 为什么主广播是 31 bytes

Legacy BLE Advertising 的主数据区最大为：

```text
31 bytes
```

示例主包恰好占满 31 bytes：

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

它由三个 AD Structure 组成：

| 字段 | AD Type | 作用 |
|---|---:|---|
| Flags | `0x01` | 基础 BLE 广播标志 |
| Manufacturer Specific Data | `0xFF` | 自定义实验数据 |
| Complete 16-bit Service UUIDs | `0x03` | 广播测试 Service UUID |

其中：

```text
F0 FF
```

按 BLE 小端序表示：

```text
0xFFF0
```

## 3. 为什么设备名放在 Scan Response

主包已经占满 31 bytes，所以不能再直接塞设备名。

因此采用：

```text
Main Advertising = 31-byte RAW
Scan Response     = ESP
```

设备名 `ESP` 对应的 AD Structure：

```text
04 09 45 53 50
```

其中：

- `09` = Complete Local Name
- `45 53 50` = ASCII `ESP`

这样既保留主包结构，又方便在附近大量 BLE 设备中快速找到开发板。

## 4. 为什么 nRF Connect 看到的 RAW 可能超过 31 bytes

nRF Connect 可能把：

```text
Advertising + Scan Response
```

一起展示。

因此界面中的总 RAW 长度可能超过 31 bytes，但主 Advertising 本身仍然只有 31 bytes。

## 5. 为什么广播间隔设置 160

BLE Advertising Interval 单位为：

```text
0.625 ms
```

代码：

```cpp
adv->setAdvertisingInterval(160);
```

因此：

```text
160 × 0.625 ms = 100 ms
```

手机端看到 101–104 ms 左右的小幅波动属于正常现象。

## 6. GATT Service 和 Advertising 是两件事

本项目同时创建了：

```text
GATT Primary Service: 0xFFF0
```

并在 Advertising 中广播同一个 UUID。

但两者概念不同：

```text
Advertising
= 设备主动向周围广播“我在这里、我有什么特征”

GATT
= 手机真正连接设备后可以发现和访问的服务结构
```

本示例只创建一个最简单的实验 Service，用来展示两层之间的关系。

## 7. 最重要的调试原则

遇到问题时不要一次改很多变量。

推荐顺序：

```text
先确认能上传
↓
先确认 Name-only BLE 能被搜到
↓
再加入 31-byte RAW
↓
再加入 Scan Response
↓
最后检查 GATT
```

具体故障处理见：

[docs/troubleshooting_CN.md](docs/troubleshooting_CN.md)

## 8. 使用范围

本项目用于 BLE 协议学习、自有设备测试、兼容性验证和获得授权的实验环境。
