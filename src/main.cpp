#include <Arduino.h>
#include <NimBLEDevice.h>

static const char *FW_NAME = "DPF Monitor";
static const char *FW_VERSION = "0.1";
static bool scanRequested = false;
static bool stopRequested = false;

static void printHelp() {
  Serial.println("COMMANDS: HELP | INFO | SCAN | STOP");
}

static void printInfo() {
  Serial.printf("%s v%s\r\n", FW_NAME, FW_VERSION);
  Serial.println("BOARD: ESP32-S3 DevKitC-1 N16R8");
  Serial.println("MODE: SAFE STARTER - no ECU commands");
  Serial.println("BLE: NimBLE initialized");
}

static void scanBle() {
  Serial.println("BLE_SCAN_START");
  NimBLEScan *scan = NimBLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(80);

  NimBLEScanResults results = scan->getResults(8000, false);
  Serial.printf("BLE_SCAN_DONE count=%d\r\n", results.getCount());

  for (int i = 0; i < results.getCount(); ++i) {
    const NimBLEAdvertisedDevice *device = results.getDevice(i);
    if (!device) continue;
    Serial.printf("DEVICE name=\"%s\" address=%s rssi=%d",
      device->haveName() ? device->getName().c_str() : "",
      device->getAddress().toString().c_str(),
      device->getRSSI());
    if (device->haveServiceUUID()) {
      Serial.printf(" service=%s", device->getServiceUUID().toString().c_str());
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1200);
  Serial.println();
  Serial.println("DPF_MONITOR_BOOT");
  NimBLEDevice::init("DPF-Monitor");
  printInfo();
  printHelp();
  Serial.println("READY");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();

    if (command == "HELP") printHelp();
    else if (command == "INFO") printInfo();
    else if (command == "SCAN") scanRequested = true;
    else if (command == "STOP") {
      stopRequested = true;
      Serial.println("STOP: no active operation");
    }
    else if (command.length()) {
      Serial.println("ERROR: unknown command");
      printHelp();
    }
  }

  if (scanRequested) {
    scanRequested = false;
    scanBle();
    Serial.println("READY");
  }
  if (stopRequested) stopRequested = false;
  delay(10);
}
