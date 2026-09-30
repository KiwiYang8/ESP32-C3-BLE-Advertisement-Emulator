# 5 分钟上手：ESP32-C3 BLE 广播

[专业原理说明](README_CN.md) · [踩坑与排错](docs/troubleshooting_CN.md) · [English](QUICKSTART_EN.md)

目标只有一个：**让 ESP32-C3 被 nRF Connect 搜到。**

## 1. 准备

- ESP32-C3 SuperMini
- 支持数据传输的 USB-C 线
- Arduino IDE 2.x
- Android 手机 + nRF Connect

## 2. 安装两个东西

Arduino IDE → **开发板管理器**：

```text
esp32 by Espressif Systems
```

Arduino IDE → **库管理器**：

```text
NimBLE-Arduino
```

建议使用 NimBLE-Arduino 2.x。

## 3. 选择开发板

```text
ESP32C3 Dev Module
```

选择对应 COM 端口。

推荐先用：

```text
Upload Speed: 115200
Serial Monitor: 115200
```

## 4. 烧录

打开：

```text
src/ESP32_C3_BLE_Emulator.ino
```

点击编译并上传。

## 5. 看串口

串口监视器设置为：

```text
115200
```

正常会看到：

```text
BLE advertising STARTED
Device Name  : ESP
Service UUID : FFF0
Interval     : ~100 ms
```

## 6. 手机验证

打开 nRF Connect → SCAN → 搜索：

```text
ESP
```

能搜到就说明整个链路已经通了。

## 7. 看 RAW

点进 `ESP`，查看 RAW。

设备名在 Scan Response 中，所以主 Advertising 仍然保持 31 bytes。

## 出问题了？

直接看：

[踩坑与排错](docs/troubleshooting_CN.md)

想知道为什么是 31 bytes、为什么名字放 Scan Response：

[专业原理说明](README_CN.md)
