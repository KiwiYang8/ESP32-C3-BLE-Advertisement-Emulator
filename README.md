# ESP32-C3 BLE Advertisement Emulator

**ESP32-C3 BLE 广播模拟与兼容性测试工具**  
**ESP32-C3 BLE Advertisement Emulation & Compatibility Testing Tool**

[中文快速上手](QUICKSTART_CN.md) · [English Quick Start](QUICKSTART_EN.md)  
[中文原理说明](README_CN.md) · [English Technical Guide](README_EN.md)

---

A small ESP32-C3 + NimBLE-Arduino example for learning BLE Advertising and validating packets with nRF Connect.

一个尽量简单的 ESP32-C3 + NimBLE-Arduino BLE 广播实验项目：先跑起来，再看懂原理。

## Start here / 从这里开始

**只想跑起来：**

- [中文：5 分钟快速上手](QUICKSTART_CN.md)
- [English: 5-Minute Quick Start](QUICKSTART_EN.md)

**想理解为什么这样写：**

- [中文原理说明](README_CN.md)
- [English Technical Guide](README_EN.md)

**遇到问题：**

- [中文踩坑与排错](docs/troubleshooting_CN.md)
- [English Troubleshooting](docs/troubleshooting_EN.md)

## Demo / 效果展示

Arduino IDE 中选择 `ESP32C3 Dev Module` 并烧录示例：

![Arduino IDE with ESP32C3 Dev Module](images/arduino_ide_esp32c3.jpg)

使用 nRF Connect 检查广播结构。下图已对无关设备标识和实验 RAW 数据做脱敏处理：

![Sanitized nRF Connect RAW view](images/nrf_connect_raw_sanitized.jpg)

实验链路：

```text
ESP32-C3 SuperMini
        ↓
Arduino IDE + NimBLE-Arduino
        ↓
BLE Advertising + Scan Response
        ↓
nRF Connect
        ↓
发现设备 + 验证 RAW
```

## What this example contains / 示例包含

- 31-byte Legacy Advertising
- Manufacturer Specific Data
- 16-bit test Service UUID `0xFFF0`
- Device name `ESP` in Scan Response
- ~100 ms advertising interval
- Simple GATT Primary Service

## Repository / 仓库结构

```text
.
├── README.md
├── QUICKSTART_CN.md
├── QUICKSTART_EN.md
├── README_CN.md
├── README_EN.md
├── LICENSE
├── src/
│   └── ESP32_C3_BLE_Emulator.ino
├── images/
│   ├── arduino_ide_esp32c3.jpg
│   └── nrf_connect_raw_sanitized.jpg
└── docs/
    ├── troubleshooting_CN.md
    └── troubleshooting_EN.md
```

## Scope / 使用范围

For BLE protocol learning, interoperability testing, and authorized laboratory simulation only.

仅用于 BLE 协议学习、兼容性测试与获得授权的实验环境。

## License

MIT License.
