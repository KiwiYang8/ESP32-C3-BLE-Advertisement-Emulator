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

本项目来源于一个封闭实验环境中的 BLE 外设兼容性测试。仓库中的示例数据用于实验与协议学习，不涉及认证密钥、动态令牌或服务端凭据。

## 2. 硬件与软件

### 硬件

- ESP32-C3 SuperMini（或其他 ESP32-C3 开发板）
- 支持数据传输的 USB-C 数据线
- Android 手机
- nRF Connect

### 软件

- Arduino IDE 2.x
- `esp32 by Espressif Systems`
- NimBLE-Arduino 2.x

## 3. Arduino IDE 配置

开发板建议选择：

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

如果上传不稳定，优先把 Upload Speed 降到 `115200`。

详细安装步骤见：[docs/setup_CN.md](docs/setup_CN.md)

## 4. 当前示例做了什么

源码：

```text
src/ESP32_C3_BLE_Emulator.ino
```

程序执行以下操作：

1. 初始化 NimBLE；
2. 创建一个 `0xFE3C` Primary Service；
3. 发送一个 31-byte Legacy Advertising Payload；
4. 使用 Scan Response 发布短设备名 `ESP`，便于在附近 BLE 设备很多时快速定位；
5. 设置约 100 ms 广播周期。

主 Advertising 与设备名彼此分离：主广播保持 31 字节，名字仅存在于 Scan Response 中。

## 5. BLE 数据包结构

示例主广播：

```text
02 01 1A
17 FF 00 01 B5 00 02 73 EB 33 C8 00 00 00
      0F 08 42 4F 1F 01 10 00 00 00
03 03 3C FE
```

对应：

| AD Type | 含义 |
|---|---|
| `0x01` | Flags |
| `0xFF` | Manufacturer Specific Data |
| `0x03` | Complete List of 16-bit Service UUIDs |

其中 `3C FE` 按 BLE 小端序表示 UUID `0xFE3C`。

设备名称 `ESP` 放在 Scan Response 中：

```text
04 09 45 53 50
```

其中 `0x09` 表示 Complete Local Name，`45 53 50` 为 ASCII 字符串 `ESP`。

详细说明见：[docs/ble_packet_CN.md](docs/ble_packet_CN.md)

## 6. 使用方法

1. 安装 Arduino IDE；
2. 安装 `esp32 by Espressif Systems`；
3. 安装 NimBLE-Arduino 2.x；
4. 选择 `ESP32C3 Dev Module`；
5. 打开 `src/ESP32_C3_BLE_Emulator.ino`；
6. 编译并上传；
7. 打开串口监视器，波特率设为 `115200`；
8. 使用 nRF Connect 扫描；
9. 搜索设备名 `ESP`；
10. 打开 RAW，核对 Advertising 与 Scan Response。

## 7. nRF Connect 预期结果

应能看到：

```text
Complete Local Name: ESP
Complete list of 16-bit Service UUIDs: 0xFE3C
Advertising interval: about 100 ms
```

主 Advertising RAW 应与源码中的 `RAW_ADV` 一致。

## 8. 常见问题

### Arduino IDE 只显示 “ESP32 Family Device”

请安装：

```text
esp32 by Espressif Systems
```

然后明确选择：

```text
ESP32C3 Dev Module
```

### 串口反复出现 `invalid header: 0xffffffff`

通常表示 Flash 中没有有效启动镜像、烧录位置异常或程序没有成功写入。可以尝试：

- 重新选择正确开发板；
- 降低 Upload Speed；
- 启用一次完整 Flash 擦除；
- 使用 BOOT + RST 强制进入下载模式后重新烧录。

### nRF Connect 搜不到设备

先烧录一个只带设备名的最小 BLE 测试程序。如果能搜到，说明开发板、射频和 NimBLE 环境正常，再逐步恢复 RAW Advertising。

### 为什么名字放在 Scan Response？

Legacy Advertising 主包最大为 31 bytes。当前示例主广播已经占满，因此不能继续添加 Local Name。Scan Response 可以单独携带名字，同时不修改主 Advertising Payload。

## 9. 安全与使用范围

本项目仅用于：

- BLE 协议学习；
- 自有设备测试；
- 兼容性验证；
- 封闭实验环境中的外设仿真。

请不要把从未经授权设备获取的身份数据、认证数据或动态令牌用于仿冒真实生产系统，也不要用于绕过考勤、门禁、认证、人脸识别、BLE 配对、加密或服务器校验。

## 10. License

MIT License，详见 [LICENSE](LICENSE)。
