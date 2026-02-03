#include "MAX30102_Driver.h"
#include <Arduino.h>

MAX30102::MAX30102() {
    _address = MAX30102_ADDRESS;
    _wire = nullptr;
}

bool MAX30102::begin(TwoWire &wire) {
    _wire = &wire;
    _wire->begin();
    
    // Check if device is connected
    if (!isConnected()) {
        Serial.print("[MAX30102] Device not responding at address 0x");
        Serial.println(MAX30102_ADDRESS, HEX);
        return false;
    }
    
    Serial.println("[MAX30102] Device detected, initializing...");
    reset();
    delay(100);
    setup();
    
    Serial.println("[MAX30102] Initialization complete");
    return true;
}

bool MAX30102::isConnected() {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
}

void MAX30102::reset() {
    Serial.print("[MAX30102] Resetting device... ");
    if (writeRegister(REG_MODE_CONFIG, MODE_RESET)) {
        delay(100);
        Serial.println("OK");
    } else {
        Serial.println("FAILED - I2C write error");
    }
}

void MAX30102::setup() {
    Serial.println("[MAX30102] Configuring registers...");
    
    // FIFO Configuration: Sample averaging = 4, FIFO rollover enabled
    Serial.print("[MAX30102]   FIFO Config (0x4F): ");
    if (writeRegister(REG_FIFO_CONFIG, 0x4F)) {
        Serial.println("OK - Sample averaging=4, Rollover enabled");
    } else {
        Serial.println("FAILED");
    }
    
    // Mode Configuration: SpO2 mode
    Serial.print("[MAX30102]   Mode Config (SpO2): ");
    if (writeRegister(REG_MODE_CONFIG, MODE_SPO2)) {
        Serial.println("OK - SpO2 mode (Red + IR LEDs)");
    } else {
        Serial.println("FAILED");
    }
    
    // SpO2 Configuration: Sample rate = 100Hz, LED pulse width = 411us, ADC range = 4096
    uint8_t spo2Config = SPO2_SR_100 | LED_PW_411 | SPO2_ADC_RGE_4096;
    Serial.print("[MAX30102]   SpO2 Config: ");
    if (writeRegister(REG_SPO2_CONFIG, spo2Config)) {
        Serial.print("OK - Sample rate=100Hz, Pulse width=411μs, ADC range=4096nA (0x");
        Serial.print(spo2Config, HEX);
        Serial.println(")");
    } else {
        Serial.println("FAILED");
    }
    
    // LED Current: Red = 0x1F (6.4mA), IR = 0x1F (6.4mA)
    Serial.print("[MAX30102]   LED Current: ");
    setLEDCurrent(0x1F, 0x1F);
    Serial.print("Red=6.4mA (0x1F), IR=6.4mA (0x1F) - ");
    Serial.println("OK");
    
    // Clear FIFO
    Serial.print("[MAX30102]   Clearing FIFO... ");
    clearFIFO();
    Serial.println("OK");
}

bool MAX30102::readFIFO(uint32_t *red, uint32_t *ir) {
    static uint32_t readErrorCount = 0;
    uint8_t temp[6];
    
    // Read 6 bytes from FIFO
    readRegisters(REG_FIFO_DATA, temp, 6);
    
    // Check if we got valid data
    if (!_wire->available() && temp[0] == 0 && temp[1] == 0 && temp[2] == 0) {
        readErrorCount++;
        if (readErrorCount % 100 == 0) {
            Serial.print("[MAX30102] Warning: Possible FIFO read issue (error count: ");
            Serial.print(readErrorCount);
            Serial.println(")");
        }
        return false;
    }
    
    *red = ((uint32_t)temp[0] << 16) | ((uint32_t)temp[1] << 8) | temp[2];
    *ir = ((uint32_t)temp[3] << 16) | ((uint32_t)temp[4] << 8) | temp[5];
    
    // Mask to 18 bits
    *red &= 0x03FFFF;
    *ir &= 0x03FFFF;
    
    return true;
}

float MAX30102::readTemperature() {
    // Enable temperature reading
    if (!writeRegister(REG_TEMP_CONFIG, 0x01)) {
        Serial.println("[MAX30102] Error: Failed to enable temperature reading");
        return 0.0;
    }
    delay(100);
    
    uint8_t tempInt = readRegister(REG_TEMP_DATA);
    uint8_t tempFrac = readRegister(REG_TEMP_FRAC);
    
    float temperature = tempInt + (tempFrac * 0.0625);
    
    // Log temperature reading details (only if significantly different from previous)
    static float lastLoggedTemp = -999;
    if (abs(temperature - lastLoggedTemp) > 0.5) {
        Serial.print("[MAX30102] Temperature: ");
        Serial.print(tempInt);
        Serial.print(" + ");
        Serial.print(tempFrac);
        Serial.print("/16 = ");
        Serial.print(temperature, 3);
        Serial.println("°C");
        lastLoggedTemp = temperature;
    }
    
    return temperature;
}

void MAX30102::setLEDCurrent(uint8_t redCurrent, uint8_t irCurrent) {
    writeRegister(REG_LED1_PA, redCurrent);
    writeRegister(REG_LED2_PA, irCurrent);
}

void MAX30102::setSampleRate(uint8_t sampleRate) {
    uint8_t config = readRegister(REG_SPO2_CONFIG);
    config &= 0xE3;  // Clear sample rate bits
    config |= sampleRate;
    writeRegister(REG_SPO2_CONFIG, config);
}

void MAX30102::setPulseWidth(uint8_t pulseWidth) {
    uint8_t config = readRegister(REG_SPO2_CONFIG);
    config &= 0xFC;  // Clear pulse width bits
    config |= pulseWidth;
    writeRegister(REG_SPO2_CONFIG, config);
}

void MAX30102::setADCRange(uint8_t adcRange) {
    uint8_t config = readRegister(REG_SPO2_CONFIG);
    config &= 0x9F;  // Clear ADC range bits
    config |= adcRange;
    writeRegister(REG_SPO2_CONFIG, config);
}

void MAX30102::enableFIFORollover(bool enable) {
    uint8_t config = readRegister(REG_FIFO_CONFIG);
    if (enable) {
        config |= 0x10;
    } else {
        config &= 0xEF;
    }
    writeRegister(REG_FIFO_CONFIG, config);
}

void MAX30102::clearFIFO() {
    writeRegister(REG_FIFO_WR_PTR, 0);
    writeRegister(REG_OVF_COUNTER, 0);
    writeRegister(REG_FIFO_RD_PTR, 0);
}

uint8_t MAX30102::getWritePointer() {
    return readRegister(REG_FIFO_WR_PTR);
}

uint8_t MAX30102::getReadPointer() {
    return readRegister(REG_FIFO_RD_PTR);
}

uint8_t MAX30102::getOVFCounter() {
    return readRegister(REG_OVF_COUNTER);
}

bool MAX30102::writeRegister(uint8_t reg, uint8_t value) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(value);
    return (_wire->endTransmission() == 0);
}

uint8_t MAX30102::readRegister(uint8_t reg) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(_address, (uint8_t)1);
    if (_wire->available()) {
        return _wire->read();
    }
    return 0;
}

void MAX30102::readRegisters(uint8_t reg, uint8_t *buffer, uint8_t len) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(_address, len);
    for (uint8_t i = 0; i < len && _wire->available(); i++) {
        buffer[i] = _wire->read();
    }
}
