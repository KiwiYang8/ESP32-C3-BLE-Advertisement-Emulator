# ESP32-C3 BLE Advertisement Emulator

**ESP32-C3 BLE 广播模拟与兼容性测试工具**  
**ESP32-C3 BLE Advertisement Emulation & Compatibility Testing Tool**

[中文快速上手](QUICKSTART_CN.md) · [English Quick Start](QUICKSTART_EN.md)  
[中文专业文档](README_CN.md) · [English Full Guide](README_EN.md)

---

This repository shows how to use an **ESP32-C3 / ESP32-C3 SuperMini** with **Arduino IDE** and **NimBLE-Arduino 2.x** to construct a legacy BLE advertising packet, expose a test GATT service, and verify the result with **nRF Connect**.

本仓库记录如何使用 **ESP32-C3 / ESP32-C3 SuperMini**、**Arduino IDE** 与 **NimBLE-Arduino 2.x** 构造 BLE Legacy Advertising 数据包、创建测试 GATT Service，并通过 **nRF Connect** 验证广播结果。

## Choose your path / 选择阅读方式

### I just want it to work / 我只想先跑起来

- [中文：5 分钟傻瓜式快速上手](QUICKSTART_CN.md)
- [English: 5-Minute Quick Start](QUICKSTART_EN.md)

### I want to understand how it works / 我想理解原理

- [中文专业版文档](README_CN.md)
- [English Full Guide](README_EN.md)

### Something is broken / 遇到问题

- [中文：踩坑与排错](docs/troubleshooting_CN.md)
- [English: Troubleshooting](docs/troubleshooting_EN.md)

## What is included / 项目内容

- 31-byte legacy BLE advertising example / 31 字节 Legacy Advertising 示例
- Manufacturer Specific Data
- Generic 16-bit lab Service UUID example (`0xFFF0`)
- Device name in Scan Response / Scan Response 设备名
- ~100 ms advertising interval / 约 100 ms 广播周期
- ESP32-C3 Arduino source / ESP32-C3 Arduino 源码
- Bilingual quick-start, setup, packet-format, and troubleshooting docs / 中英文快速上手、配置、数据包与排错文档

## Demo / 效果展示

Current demo flow:

```text
ESP32-C3 SuperMini
        ↓
Arduino IDE + NimBLE-Arduino
        ↓
31-byte BLE Advertising
        +
Scan Response: ESP
        ↓
nRF Connect
        ↓
Device discovered + RAW packet verified
```

Screenshots will be added under `images/` after removing device addresses and unrelated personal information.

后续会在 `images/` 中加入演示截图，并对 BLE 地址、状态栏及其他无关个人信息进行裁剪或打码。

## Quick start / 快速开始

1. Install **esp32 by Espressif Systems** in Arduino IDE.
2. Install **NimBLE-Arduino 2.x**.
3. Select **ESP32C3 Dev Module**.
4. Open `src/ESP32_C3_BLE_Emulator.ino`.
5. Compile and upload.
6. Use nRF Connect to scan for device name `ESP`.
7. Inspect RAW advertising data.

## Repository layout / 仓库结构

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
└── docs/
    ├── setup_CN.md
    ├── setup_EN.md
    ├── ble_packet_CN.md
    ├── ble_packet_EN.md
    ├── troubleshooting_CN.md
    └── troubleshooting_EN.md
```

## Scope / 使用范围

This project is intended for **BLE protocol learning, interoperability testing, and authorized laboratory simulation**. Use only devices and advertising data that you own or are authorized to test.

本项目仅用于 **BLE 协议学习、兼容性测试与获得授权的实验室仿真**。请仅对本人拥有或明确授权测试的设备与广播数据使用本项目。

## License

MIT License. See [LICENSE](LICENSE).
