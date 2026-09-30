# ESP32-C3 BLE Advertisement Emulator

ESP32-C3 BLE 广播模拟与兼容性测试示例（钉钉蓝牙打卡神器）
A minimal ESP32-C3 + NimBLE-Arduino BLE advertising example.

[Technical / 原理](TECHNICAL.md) · [Troubleshooting / 排错](TROUBLESHOOTING.md)

## Demo / 效果

![Arduino IDE](images/arduino_ide_esp32c3.jpg)

![nRF Connect](images/nrf_connect_raw_sanitized.jpg)

## Quick Start / 快速上手

1. Arduino IDE 安装 / Install:
   - `esp32 by Espressif Systems`
   - `NimBLE-Arduino 2.x`
2. 开发板 / Board: `ESP32C3 Dev Module`
3. 上传速度 / Upload Speed: `115200`
4. 打开 / Open: `src/ESP32_C3_BLE_Emulator.ino`
5. 编译并上传 / Compile and upload
6. nRF Connect 搜索 / Scan for: `ESP`

串口正常输出 / Expected serial output:

```text
BLE advertising STARTED
Device Name  : ESP
Service UUID : FFF0
Interval     : ~100 ms
```

## Example / 示例

```text
ESP32-C3
  ↓
31-byte BLE Advertising
  +
Scan Response: ESP
  ↓
nRF Connect
```

- Manufacturer Specific Data
- 16-bit test Service UUID: `0xFFF0`
- Device name `ESP` in Scan Response
- Advertising interval: ~100 ms

## Files / 文件

```text
.
├── README.md
├── TECHNICAL.md
├── TROUBLESHOOTING.md
├── LICENSE
├── src/
│   └── ESP32_C3_BLE_Emulator.ino
└── images/
    ├── arduino_ide_esp32c3.jpg
    └── nrf_connect_raw_sanitized.jpg
```

## Scope / 使用范围

For BLE learning, interoperability testing, and authorized laboratory use only.  
仅用于 BLE 学习、兼容性测试和获得授权的实验环境。

## License

MIT
