#include <Wire.h>

constexpr int kSdaPin = 21;
constexpr int kSclPin = 22;
constexpr unsigned long kSerialBaud = 115200;

void setup() {
  Serial.begin(kSerialBaud);
  if (!Wire.begin(kSdaPin, kSclPin)) {
    Serial.println("I2C initialization failed.");
    return;
  }

  unsigned int deviceCount = 0;
  for (uint8_t address = 0x08; address <= 0x77; ++address) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.printf("I2C device found at 0x%02X\n", static_cast<unsigned int>(address));
      ++deviceCount;
    }
  }
  Serial.printf("I2C devices found: %u\n", deviceCount);
}

void loop() {}
