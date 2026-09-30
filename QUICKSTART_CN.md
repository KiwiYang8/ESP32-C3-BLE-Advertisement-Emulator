# 5 分钟上手：ESP32-C3 BLE 广播

[English](QUICKSTART_EN.md) · [专业版中文文档](README_CN.md) · [主页](README.md)

这份文档只做一件事：**让 ESP32-C3 在 Arduino IDE 中跑起来，并能被 nRF Connect 搜到。**

## 你需要准备

- ESP32-C3 SuperMini
- 一根支持数据传输的 USB-C 线
- Arduino IDE 2.x
- Android 手机 + nRF Connect

## 第 1 步：安装 ESP32 开发板支持

Arduino IDE → **开发板管理器**，搜索：

```text
esp32
```

安装：

```text
esp32 by Espressif Systems
```

## 第 2 步：安装 BLE 库

Arduino IDE → **库管理器**，搜索并安装：

```text
NimBLE-Arduino
```

建议使用 2.x。

## 第 3 步：选择开发板

选择：

```text
ESP32C3 Dev Module
```

然后选择开发板对应的 COM 端口。

推荐先使用：

```text
Upload Speed: 115200
Serial Monitor: 115200
```

## 第 4 步：打开代码

打开：

```text
src/ESP32_C3_BLE_Emulator.ino
```

直接编译并上传。

如果上传时一直停在：

```text
Connecting...
```

尝试：

```text
按住 BOOT
→ 按一下 RST
→ 松开 RST
→ 松开 BOOT
→ 重新上传
```

## 第 5 步：看串口

打开串口监视器，波特率：

```text
115200
```

正常应看到类似：

```text
BLE advertising STARTED
Device Name  : ESP
Service UUID : FFF0
Interval     : ~100 ms
```

## 第 6 步：用 nRF Connect 搜索

打开 nRF Connect → SCAN。

搜索：

```text
ESP
```

能搜到就说明：

```text
Arduino 环境      ✓
ESP32-C3          ✓
NimBLE            ✓
BLE 广播          ✓
手机扫描          ✓
```

## 第 7 步：检查 RAW

进入设备详情，查看 RAW Advertising。

设备名 `ESP` 放在 Scan Response 中，因此主 31-byte Advertising 不会被设备名挤占。

## 出问题了？

直接看：

[常见踩坑与排错](docs/troubleshooting_CN.md)

需要理解 BLE 包结构：

[BLE Advertising 数据包说明](docs/ble_packet_CN.md)

想看完整原理：

[专业版中文文档](README_CN.md)
