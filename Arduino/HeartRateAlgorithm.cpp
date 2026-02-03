#include "HeartRateAlgorithm.h"
#include <Arduino.h>

HeartRateAlgorithm::HeartRateAlgorithm() {
    reset();
}

void HeartRateAlgorithm::reset() {
    _bufferIndex = 0;
    _dataReady = false;
    _lastPeakTime = 0;
    _peakCount = 0;
    _intervalIndex = 0;
    for (uint8_t i = 0; i < HR_ALGORITHM_BUFFER_SIZE; i++) {
        _buffer[i] = 0;
    }
    for (uint8_t i = 0; i < 10; i++) {
        _peakIntervals[i] = 0;
    }
}

void HeartRateAlgorithm::addSample(uint32_t irValue) {
    _buffer[_bufferIndex] = irValue;
    _bufferIndex = (_bufferIndex + 1) % HR_ALGORITHM_BUFFER_SIZE;
    
    if (!_dataReady && _bufferIndex == 0) {
        _dataReady = true;
        Serial.println("[HR_ALGORITHM] Buffer filled - Heart rate calculation ready");
    }
    
    if (_dataReady && _bufferIndex >= 3) {
        uint8_t prevIdx = (_bufferIndex - 2 + HR_ALGORITHM_BUFFER_SIZE) % HR_ALGORITHM_BUFFER_SIZE;
        uint8_t currIdx = (_bufferIndex - 1 + HR_ALGORITHM_BUFFER_SIZE) % HR_ALGORITHM_BUFFER_SIZE;
        uint8_t nextIdx = _bufferIndex;
        
        if (detectPeak(_buffer[currIdx], _buffer[prevIdx], _buffer[nextIdx])) {
            if (_lastPeakTime > 0) {
                uint32_t interval = (_bufferIndex - _lastPeakTime + HR_ALGORITHM_BUFFER_SIZE) % HR_ALGORITHM_BUFFER_SIZE;
                if (interval >= HR_ALGORITHM_MIN_PEAK_DISTANCE) {
                    _peakIntervals[_intervalIndex] = interval;
                    _intervalIndex = (_intervalIndex + 1) % 10;
                    _peakCount++;
                    
                    // Log peak detection (only every 5th peak to avoid spam)
                    if (_peakCount % 5 == 0) {
                        Serial.print("[HR_ALGORITHM] Peak detected #");
                        Serial.print(_peakCount);
                        Serial.print(" | Interval: ");
                        Serial.print(interval);
                        Serial.print(" samples (");
                        Serial.print(interval * 10);  // Convert to ms at 100Hz
                        Serial.println("ms)");
                    }
                }
            }
            _lastPeakTime = currIdx;
        }
    }
}

bool HeartRateAlgorithm::detectPeak(uint32_t value, uint32_t prevValue, uint32_t nextValue) {
    uint32_t avg = calculateAverage();
    return (value > prevValue && value > nextValue && value > avg * 1.1);
}

uint32_t HeartRateAlgorithm::calculateAverage() {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < HR_ALGORITHM_BUFFER_SIZE; i++) {
        sum += _buffer[i];
    }
    return sum / HR_ALGORITHM_BUFFER_SIZE;
}

uint8_t HeartRateAlgorithm::getHeartRate() {
    static uint8_t lastLoggedBPM = 0;
    
    if (_peakCount < 3) {
        if (_peakCount == 0 && _dataReady) {
            static bool loggedWaiting = false;
            if (!loggedWaiting) {
                Serial.println("[HR_ALGORITHM] Waiting for more peaks (need at least 3)");
                loggedWaiting = true;
            }
        }
        return 0;
    }
    
    uint32_t sum = 0;
    uint8_t count = 0;
    for (uint8_t i = 0; i < 10; i++) {
        if (_peakIntervals[i] > 0) {
            sum += _peakIntervals[i];
            count++;
        }
    }
    
    if (count == 0) {
        return 0;
    }
    
    // Assuming 100Hz sample rate
    float avgInterval = (float)sum / count;
    float bpm = 6000.0 / avgInterval;  // 100 samples/sec = 6000 samples/min
    
    if (bpm < 40 || bpm > 200) {
        if (bpm != 0) {
            Serial.print("[HR_ALGORITHM] Warning: Calculated BPM out of range: ");
            Serial.print(bpm, 1);
            Serial.println(" (valid range: 40-200 BPM)");
        }
        return 0;
    }
    
    uint8_t resultBPM = (uint8_t)bpm;
    
    // Log when BPM changes significantly
    if (abs((int)resultBPM - (int)lastLoggedBPM) >= 5 || lastLoggedBPM == 0) {
        Serial.print("[HR_ALGORITHM] Heart rate calculated: ");
        Serial.print(resultBPM);
        Serial.print(" BPM (from ");
        Serial.print(count);
        Serial.print(" intervals, avg: ");
        Serial.print(avgInterval, 1);
        Serial.println(" samples)");
        lastLoggedBPM = resultBPM;
    }
    
    return resultBPM;
}

bool HeartRateAlgorithm::isDataReady() {
    return _dataReady;
}
