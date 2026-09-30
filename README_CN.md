# ESP32-C3 BLE 广播模拟与兼容性测试工具

[English](README_EN.md) | [返回主页](README.md)

## 1. 项目简介

本项目记录一个基于 **ESP32-C3 / ESP32-C3 SuperMini + Arduino IDE + NimBLE-Arduino 2.x** 的 BLE 广播实验流程。

项目目标是学习和验证：

- 如何构造 BLE Legacy Advertising；
- 如何发送自定义 Manufacturer Specific Data；
- 如何广播 16-bit Service UUID；
- 如何在主广播已占满 31 字节时，把设备名放到 Scan Response；
- 如何创建一个简单 GATT Primary Service；
- 如何使用 nRF Connect 检查 RAW Advertising 数据。

仓库采用通用实验 Payload 与实验 UUID，适合协议学习、兼容性验证和自有设备仿真。

## 2. 硬件与软件

- ESP32-C3 SuperMini（或其他 ESP32-C3 开发板）
- 支持数据传输的 USB-C 数据线
- Android 手机 + nRF Connect
- Arduino IDE 2.x
- `esp32 by Espressif Systems`
- NimBLE-Arduino 2.x

## 3. Arduino IDE 配置

开发板：

```text
ESP32C3 Dev Module
```

常用参数：

```text
CPU Frequency: 160 MHz
Flash Size: 4 MB
Upload Speed: 115200 或 460800
Serial Monitor: 115200 baud
```

详细安装步骤见：[docs/setup_CN.md](docs/setup_CN.md)

## 4. 当前示例

源码：

```text
src/ESP32_C3_BLE_Emulator.ino
```

程序执行：

1. 初始化 NimBLE；
2. 创建通用实验 Service `0xFFF0`；
3. 发送 31-byte Legacy Advertising Payload；
4. 使用 Scan Response 发布短设备名 `ESP`；
5. 设置约 100 ms 广播周期。

## 5. BLE 数据包结构

示例主广播：

```text
02 01 06
17 FF FF FF 4C 41 42 01 02 03 04 05 06 07 08 09
      10 11 12 13 14 15 16 17
03 03 F0 FF
```

对应：

| AD Type | 含义 |
|---|---|
| `0x01` | Flags |
| `0xFF` | Manufacturer Specific Data |
| `0x03` | Complete List of 16-bit Service UUIDs |

其中 `F0 FF` 按 BLE 小端序表示 UUID `0xFFF0`。

设备名称 `ESP` 放在 Scan Response 中：

```text
04 09 45 53 50
```

详细说明见：[docs/ble_packet_CN.md](docs/ble_packet_CN.md)

## 6. 使用方法

1. 安装 Arduino IDE；
2. 安装 `esp32 by Espressif Systems`；
3. 安装 NimBLE-Arduino 2.x；
4. 选择 `ESP32C3 Dev Module`；
5. 打开源码；
6. 编译并上传；
7. 串口监视器设置为 `115200`；
8. nRF Connect 搜索 `ESP`；
9. 打开 RAW 数据，核对 Advertising 与 Scan Response。

## 7. 常见问题

- 只显示 “ESP32 Family Device”：安装 Espressif 的 ESP32 Core 并明确选择 `ESP32C3 Dev Module`。
- `invalid header: 0xffffffff`：重新选择开发板、降低上传速度，必要时擦除 Flash 并用 BOOT + RST 进入下载模式。
- nRF Connect 搜不到：先烧录最小 Name-only BLE 示例，再逐步恢复自定义 RAW。
- 名字为什么在 Scan Response：因为 Legacy Advertising 主包最多 31 bytes，本示例主包已占满。

## 8. 使用范围

本项目用于 BLE 协议学习、自有设备测试、兼容性验证和获得授权的实验环境。

## 9. License

MIT License，详见 [LICENSE](LICENSE)。
