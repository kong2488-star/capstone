#include <Wire.h>

constexpr int kSdaPin = 21;
constexpr int kSclPin = 22;
constexpr unsigned long kSerialBaud = 115200;
constexpr uint8_t kIna226Address = 0x40;
constexpr uint8_t kManufacturerIdRegister = 0xFE;
constexpr uint8_t kDeviceIdRegister = 0xFF;
constexpr uint8_t kConfigurationRegister = 0x00;
constexpr size_t kRegisterSize = 2;

void printRegister(const char* label, uint8_t registerAddress) {
  Wire.beginTransmission(kIna226Address);
  Wire.write(registerAddress);
  if (Wire.endTransmission(false) != 0) {
    Serial.printf("%s: I2C register selection failed\n", label);
    return;
  }
  if (Wire.requestFrom(kIna226Address, kRegisterSize) != kRegisterSize) {
    Serial.printf("%s: I2C register read failed\n", label);
    return;
  }

  const uint16_t highByte = static_cast<uint16_t>(Wire.read());
  const uint16_t lowByte = static_cast<uint16_t>(Wire.read());
  const uint16_t value = (highByte << 8) | lowByte;
  Serial.printf("%s: 0x%04X\n", label, static_cast<unsigned int>(value));
}

void setup() {
  Serial.begin(kSerialBaud);
  if (!Wire.begin(kSdaPin, kSclPin)) {
    Serial.println("I2C initialization failed.");
    return;
  }

  printRegister("Manufacturer ID", kManufacturerIdRegister);
  printRegister("Device ID", kDeviceIdRegister);
  printRegister("Configuration", kConfigurationRegister);
}

void loop() {}
