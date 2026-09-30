# ESP32-C3 BLE Advertisement Emulator

**ESP32-C3 BLE 广播模拟与兼容性测试工具**  
**ESP32-C3 BLE Advertisement Emulation & Compatibility Testing Tool**

[中文文档](README_CN.md) · [English Documentation](README_EN.md)

---

This repository shows how to use an **ESP32-C3 / ESP32-C3 SuperMini** with **Arduino IDE** and **NimBLE-Arduino 2.x** to construct a legacy BLE advertising packet, expose a test GATT service, and verify the result with **nRF Connect**.

本仓库记录如何使用 **ESP32-C3 / ESP32-C3 SuperMini**、**Arduino IDE** 与 **NimBLE-Arduino 2.x** 构造 BLE Legacy Advertising 数据包、创建测试 GATT Service，并通过 **nRF Connect** 验证广播结果。

## What is included / 项目内容

- 31-byte legacy BLE advertising example / 31 字节 Legacy Advertising 示例
- Manufacturer Specific Data
- 16-bit Service UUID example (`0xFE3C`)
- Optional device name in Scan Response / 可选 Scan Response 设备名
- ~100 ms advertising interval / 约 100 ms 广播周期
- ESP32-C3 Arduino source / ESP32-C3 Arduino 源码
- Bilingual setup, packet-format, and troubleshooting notes / 中英文配置、数据包与排错文档

## Quick start / 快速开始

1. Install **esp32 by Espressif Systems** in Arduino IDE.
2. Install **NimBLE-Arduino 2.x**.
3. Select **ESP32C3 Dev Module**.
4. Open `src/ESP32_C3_BLE_Emulator.ino`.
5. Compile and upload.
6. Use nRF Connect to scan for the device name `ESP`.
7. Inspect RAW advertising data and the advertised service UUID.

中文详细步骤见：[README_CN.md](README_CN.md)  
English guide: [README_EN.md](README_EN.md)

## Repository layout / 仓库结构

```text
.
├── README.md
├── README_CN.md
├── README_EN.md
├── LICENSE
├── src/
│   └── ESP32_C3_BLE_Emulator.ino
└── docs/
    ├── setup_CN.md
    ├── setup_EN.md
    ├── ble_packet_CN.md
    └── ble_packet_EN.md
```

## Scope / 使用范围

This project is intended for **BLE protocol learning, interoperability testing, and authorized laboratory simulation**. Use only devices and advertising data that you own or are authorized to test. Do not use it to bypass attendance, access-control, authentication, pairing, encryption, facial verification, or server-side security mechanisms.

本项目仅用于 **BLE 协议学习、兼容性测试与获得授权的实验室仿真**。请仅对本人拥有或明确授权测试的设备与广播数据使用本项目，不应用于绕过考勤、门禁、认证、配对、加密、人脸验证或服务端安全机制。

## License

MIT License. See [LICENSE](LICENSE).
