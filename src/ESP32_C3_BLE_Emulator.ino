/*
 * ESP32-C3 BLE Advertisement Emulator
 * ESP32-C3 BLE 广播示例
 */

#include <Arduino.h>
#include <NimBLEDevice.h>

static const char* DEVICE_NAME = "ESP";

static const uint8_t RAW_ADV[] = {
    0x02, 0x01, 0x06,                         // Flags

    0x17, 0xFF,                               // Manufacturer data
    0xFF, 0xFF,                               // Test company ID
    0x4C, 0x41, 0x42, 0x01,
    0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x08, 0x09,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,

    0x03, 0x03, 0xF0, 0xFF                    // Service UUID 0xFFF0
};

static_assert(sizeof(RAW_ADV) == 31, "RAW_ADV must be 31 bytes");

void setup() {
    Serial.begin(115200);
    delay(1000);

    NimBLEDevice::init(DEVICE_NAME);

    NimBLEServer* server = NimBLEDevice::createServer();
    NimBLEService* service = server->createService("FFF0");
    service->start();

    NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();

    NimBLEAdvertisementData advData;
    if (!advData.addData(RAW_ADV, sizeof(RAW_ADV))) {
        Serial.println("ERROR: RAW advertising data");
        return;
    }
    adv->setAdvertisementData(advData);

    NimBLEAdvertisementData scanData;
    scanData.setName(DEVICE_NAME);
    adv->setScanResponseData(scanData);
    adv->enableScanResponse(true);

    adv->setAdvertisingInterval(160); // 160 × 0.625 ms = 100 ms

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
