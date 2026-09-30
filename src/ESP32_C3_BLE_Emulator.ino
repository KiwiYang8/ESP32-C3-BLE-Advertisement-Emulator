/*
 * ESP32-C3 BLE Advertisement Emulator
 * ESP32-C3 BLE 广播模拟器
 *
 * For BLE protocol learning, interoperability testing, and authorized
 * laboratory simulation only.
 * 仅用于 BLE 协议学习、兼容性测试和获得授权的实验室仿真。
 */

#include <Arduino.h>
#include <NimBLEDevice.h>

// Short name carried in Scan Response.
// 短设备名放在 Scan Response 中。
static const char* DEVICE_NAME = "ESP";

// Generic laboratory example payload.
// 通用实验室示例 Payload。
static const uint8_t RAW_ADV[] = {
    // Flags
    0x02, 0x01, 0x06,

    // Manufacturer Specific Data:
    // 0xFFFF = test/private placeholder company identifier
    // 后续为自定义实验数据
    0x17, 0xFF,
    0xFF, 0xFF,
    0x4C, 0x41, 0x42, 0x01,
    0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x08, 0x09,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,

    // Complete List of 16-bit Service UUIDs
    // 0xFFF0 -> little endian / 小端序 = F0 FF
    0x03, 0x03, 0xF0, 0xFF
};

static_assert(sizeof(RAW_ADV) == 31,
              "RAW_ADV must be exactly 31 bytes");

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("====================================");
    Serial.println("ESP32-C3 BLE Advertisement Emulator");
    Serial.println("====================================");

    NimBLEDevice::init(DEVICE_NAME);

    NimBLEServer* server = NimBLEDevice::createServer();

    // Generic laboratory GATT service.
    // 通用实验 GATT Service。
    NimBLEService* service =
        server->createService(NimBLEUUID("FFF0"));
    service->start();

    NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();

    NimBLEAdvertisementData advData;
    bool rawOK = advData.addData(RAW_ADV, sizeof(RAW_ADV));

    if (!rawOK) {
        Serial.println("ERROR: Failed to add RAW advertising data.");
        return;
    }

    adv->setAdvertisementData(advData);

    // Keep the 31-byte main packet unchanged and put the name in Scan Response.
    // 主广播保持 31 字节不变，名称单独放入 Scan Response。
    NimBLEAdvertisementData scanData;
    scanData.setName(DEVICE_NAME);

    adv->setScanResponseData(scanData);
    adv->enableScanResponse(true);

    // 160 * 0.625 ms = 100 ms
    adv->setAdvertisingInterval(160);

    if (adv->start()) {
        Serial.println("BLE advertising STARTED");
        Serial.println("Device Name  : ESP");
        Serial.println("Service UUID : FFF0");
        Serial.println("Interval     : ~100 ms");
    } else {
        Serial.println("ERROR: BLE advertising failed");
    }
}

void loop() {
    delay(1000);
}
