# Troubleshooting / 踩坑与排错

[Home / 主页](README.md) · [Technical / 原理](TECHNICAL.md)

| Problem / 问题 | Fix / 处理 |
|---|---|
| Arduino IDE only shows `ESP32 Family Device` / 只显示该名称 | Install `esp32 by Espressif Systems`, then select `ESP32C3 Dev Module`. / 安装 Espressif Core 后明确选择该开发板。 |
| Only `exit status 1` / 只有这一行错误 | Usually, it's because the board isn't connected properly, or the wrong board model was selected. / 一般是板子没连接好，或者板子型号没选对。 |
| `invalid header: 0xffffffff` | Select the correct board, use Upload Speed `115200`, erase flash if needed, then upload again. / 检查开发板、降低上传速度，必要时擦除 Flash 后重刷。 |
| Upload stuck at `Connecting...` / 一直连接不上 | Hold **BOOT** → press **RST** → release RST → release BOOT → upload again. / 用 BOOT + RST 进入下载模式后重试。 |
| COM port disappears / COM 口消失 | Check USB cable, port, Type-C contact, hub, and power. / 检查数据线、USB 口、接触、Hub 和供电。 |
| COM remains but upload fails / COM 还在但烧录失败 | Check board selection, download mode, and upload speed. / 检查 Board、下载模式和上传速度。 |
| nRF Connect cannot find ESP32-C3 / 搜不到设备 | First test a name-only BLE example. If visible, restore RAW fields step by step. / 先测试只有设备名的最小广播，再逐步恢复 RAW。 |
| RAW appears longer than 31 bytes / RAW 看起来超过 31 字节 | nRF Connect may combine Advertising and Scan Response in one view. / nRF Connect 可能把主广播和 Scan Response 合并显示。 |
| Interval shows 101–104 ms / 周期不是精确 100 ms | Normal scanner-side variation. / 属于扫描端正常波动。 |

## Recommended order / 推荐顺序

```text
ESP32 Core
→ Board
→ COM
→ Upload
→ Name-only BLE
→ RAW
→ Scan Response
→ GATT
```

不要同时改很多设置。  
Do not change many variables at once.
