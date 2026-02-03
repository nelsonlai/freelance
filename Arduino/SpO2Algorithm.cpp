#include "SpO2Algorithm.h"
#include <math.h>
#include <Arduino.h>

SpO2Algorithm::SpO2Algorithm() {
    reset();
}

void SpO2Algorithm::reset() {
    _bufferIndex = 0;
    _dataReady = false;
    for (uint8_t i = 0; i < SPO2_BUFFER_SIZE; i++) {
        _redBuffer[i] = 0;
        _irBuffer[i] = 0;
    }
}

void SpO2Algorithm::addSample(uint32_t red, uint32_t ir) {
    _redBuffer[_bufferIndex] = red;
    _irBuffer[_bufferIndex] = ir;
    _bufferIndex = (_bufferIndex + 1) % SPO2_BUFFER_SIZE;
    
    if (!_dataReady && _bufferIndex == 0) {
        _dataReady = true;
        Serial.println("[SPO2_ALGORITHM] Buffer filled - SpO2 calculation ready");
    }
}

float SpO2Algorithm::calculateACComponent(uint32_t *buffer) {
    float mean = calculateDCComponent(buffer);
    float sumSqDiff = 0;
    
    for (uint8_t i = 0; i < SPO2_BUFFER_SIZE; i++) {
        float diff = (float)buffer[i] - mean;
        sumSqDiff += diff * diff;
    }
    
    return sqrt(sumSqDiff / SPO2_BUFFER_SIZE);
}

float SpO2Algorithm::calculateDCComponent(uint32_t *buffer) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < SPO2_BUFFER_SIZE; i++) {
        sum += buffer[i];
    }
    return (float)sum / SPO2_BUFFER_SIZE;
}

float SpO2Algorithm::calculateRatio() {
    if (!_dataReady) {
        return 0;
    }
    
    float redAC = calculateACComponent(_redBuffer);
    float redDC = calculateDCComponent(_redBuffer);
    float irAC = calculateACComponent(_irBuffer);
    float irDC = calculateDCComponent(_irBuffer);
    
    if (redDC == 0 || irDC == 0) {
        return 0;
    }
    
    float ratio = (redAC / redDC) / (irAC / irDC);
    return ratio;
}

uint8_t SpO2Algorithm::getSpO2() {
    static uint8_t lastLoggedSpO2 = 0;
    static uint32_t calculationCount = 0;
    
    if (!_dataReady) {
        return 0;
    }
    
    float ratio = calculateRatio();
    
    if (ratio <= 0) {
        if (calculationCount % 100 == 0) {
            Serial.println("[SPO2_ALGORITHM] Warning: Invalid ratio calculated (check sensor contact)");
        }
        calculationCount++;
        return 0;
    }
    
    // Empirical formula: SpO2 = 110 - 25 * ratio
    // This is a simplified formula; real implementations use lookup tables
    float spo2 = 110.0 - 25.0 * ratio;
    
    if (spo2 < 0) spo2 = 0;
    if (spo2 > 100) spo2 = 100;
    
    uint8_t resultSpO2 = (uint8_t)spo2;
    calculationCount++;
    
    // Log when SpO2 changes significantly (every 2% or first valid reading)
    if (abs((int)resultSpO2 - (int)lastLoggedSpO2) >= 2 || (lastLoggedSpO2 == 0 && resultSpO2 > 0)) {
        float redAC = calculateACComponent(_redBuffer);
        float redDC = calculateDCComponent(_redBuffer);
        float irAC = calculateACComponent(_irBuffer);
        float irDC = calculateDCComponent(_irBuffer);
        
        Serial.print("[SPO2_ALGORITHM] SpO2 calculated: ");
        Serial.print(resultSpO2);
        Serial.print("% | Ratio: ");
        Serial.print(ratio, 3);
        Serial.print(" | Red AC/DC: ");
        Serial.print(redAC / redDC, 4);
        Serial.print(" | IR AC/DC: ");
        Serial.print(irAC / irDC, 4);
        Serial.println();
        lastLoggedSpO2 = resultSpO2;
    }
    
    return resultSpO2;
}

bool SpO2Algorithm::isDataReady() {
    return _dataReady;
}
