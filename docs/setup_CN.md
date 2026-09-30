# Arduino IDE 与 ESP32-C3 配置

[English version](setup_EN.md)

## 1. 安装 ESP32 Core

Arduino IDE → 开发板管理器，搜索：

```text
esp32
```

安装：

```text
esp32 by Espressif Systems
```

如果开发板列表中没有 `ESP32C3 Dev Module`，通常说明 Espressif 的 ESP32 Core 尚未正确安装。

## 2. 安装 NimBLE-Arduino

Arduino IDE → 库管理器，搜索：

```text
NimBLE-Arduino
```

建议使用 2.x。

## 3. 选择开发板

```text
工具 → 开发板 → esp32 → ESP32C3 Dev Module
```

选择正确 COM 端口。

## 4. 推荐配置

```text
Board: ESP32C3 Dev Module
CPU Frequency: 160 MHz
Flash Size: 4 MB
Upload Speed: 115200
Serial Monitor: 115200 baud
```


## 5. 下载模式

如果上传阶段长期停留在 `Connecting...`：

1. 按住 BOOT；
2. 按一下 RST；
3. 松开 RST；
4. 松开 BOOT；
5. 重新选择可能变化的 COM 端口；
6. 再次上传。

## 6. `invalid header: 0xffffffff`

如果串口反复输出该信息，优先检查：

- 是否选择 `ESP32C3 Dev Module`；
- 是否成功完成一次完整烧录；
- 是否需要完整擦除 Flash；
- USB 数据线是否支持数据传输；
- 端口是否在复位后重新枚举。
