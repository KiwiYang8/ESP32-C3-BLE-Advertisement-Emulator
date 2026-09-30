# ESP32-C3 + Arduino + NimBLE 踩坑与排错

[English](troubleshooting_EN.md) · [快速上手](../QUICKSTART_CN.md) · [专业文档](../README_CN.md)

这份文档专门记录实际调试 ESP32-C3 SuperMini 时最容易踩的坑。

## 1. Arduino IDE 只显示 “ESP32 Family Device”

### 现象

顶部能看到串口设备，但开发板列表里没有：

```text
ESP32C3 Dev Module
```

### 原因

通常是 **Espressif 官方 ESP32 Arduino Core 没有正确安装**。

### 解决

开发板管理器搜索：

```text
esp32
```

安装：

```text
esp32 by Espressif Systems
```

然后选择：

```text
Tools → Board → esp32 → ESP32C3 Dev Module
```

---

## 2. 编译只显示 `exit status 1`，看不到真正错误

### 处理

不要只看“串口监视器”，切换到底部：

```text
输出 / Output
```

重新点击“验证/编译”。

真正有价值的报错通常是：

```text
error: ...
fatal error: ...
no matching function ...
not declared in this scope
```

如果仍只有 `exit status 1`，优先确认开发板 Core 和 Board 是否已正确安装/选择。

---

## 3. 串口反复出现 `invalid header: 0xffffffff`

### 含义

ESP32-C3 ROM Bootloader 没有从 Flash 读到有效启动镜像。

### 常见原因

- Flash 曾经被擦除；
- 之前的固件烧录失败；
- Board/Flash 配置错误；
- 程序实际上没有成功上传。

### 处理顺序

1. Board 选择 `ESP32C3 Dev Module`；
2. Upload Speed 先设为 `115200`；
3. 必要时启用一次完整 Flash 擦除；
4. BOOT + RST 强制进入下载模式；
5. 重新上传；
6. 确认日志里出现写入与校验成功信息。

---

## 4. 一直停在 `Connecting...`

手动进入下载模式：

```text
按住 BOOT
→ 按一下 RST
→ 松开 RST
→ 松开 BOOT
```

再重新上传。

复位后 Windows 可能重新枚举 COM 端口，因此需要再次确认端口号。

---

## 5. 换数据线后仍然不稳定

先区分三种情况：

### A. COM 口直接消失

优先检查：

- USB 数据线；
- USB 接口；
- Type-C 接触；
- HUB；
- 供电。

### B. COM 口还在，但上传失败

优先检查：

- 是否进入 Download Mode；
- Board 是否选对；
- Upload Speed 是否过高。

### C. 能上传，但程序运行后不断断开

优先检查：

- 程序是否崩溃；
- 是否出现 Guru Meditation；
- 是否不断自动重启。

---

## 6. nRF Connect 搜不到 ESP32-C3

不要一开始就怀疑 RAW Payload。

先烧一个最小 BLE 广播：

```text
Device Name: ESP32C3-TEST
```

如果能搜到，说明：

```text
开发板       ✓
BLE 射频     ✓
NimBLE       ✓
nRF Connect  ✓
```

然后再逐步恢复自定义 Advertising Payload。

---

## 7. 为什么主广播里不能再加名字？

Legacy BLE Advertising 主包最大：

```text
31 bytes
```

如果主广播已经占满 31 bytes，再加入名字会改变原 Payload。

因此本项目使用：

```text
Main Advertising = 31-byte RAW
Scan Response     = Device Name
```

---

## 8. 为什么 nRF Connect RAW 看起来比 31 bytes 长？

nRF Connect 可能把：

```text
Advertising
+
Scan Response
```

组合显示。

例如设备名 `ESP` 会增加：

```text
04 09 45 53 50
```

这不代表主 Advertising 超过了 31 bytes。

---

## 9. 广播间隔为什么看到约 101–104 ms？

代码设置：

```text
160 × 0.625 ms = 100 ms
```

扫描端显示约 101–104 ms 属于正常波动，不代表配置错误。

---

## 10. 推荐排错顺序

```text
开发板 Core
↓
Board 型号
↓
COM 端口
↓
最小上传
↓
最小 BLE Name 广播
↓
nRF Connect 可发现
↓
自定义 RAW
↓
Scan Response
↓
GATT Service
```

不要一次同时改很多变量。
