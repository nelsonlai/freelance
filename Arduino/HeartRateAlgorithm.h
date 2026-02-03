#ifndef HEARTRATE_ALGORITHM_H
#define HEARTRATE_ALGORITHM_H

#include <stdint.h>

#define HR_ALGORITHM_BUFFER_SIZE 100
#define HR_ALGORITHM_MIN_PEAK_DISTANCE 30  // Minimum samples between peaks

class HeartRateAlgorithm {
public:
    HeartRateAlgorithm();
    void addSample(uint32_t irValue);
    uint8_t getHeartRate();
    bool isDataReady();
    void reset();
    
private:
    uint32_t _buffer[HR_ALGORITHM_BUFFER_SIZE];
    uint8_t _bufferIndex;
    bool _dataReady;
    uint32_t _lastPeakTime;
    uint8_t _peakCount;
    uint32_t _peakIntervals[10];
    uint8_t _intervalIndex;
    
    bool detectPeak(uint32_t value, uint32_t prevValue, uint32_t nextValue);
    uint32_t calculateAverage();
};

#endif
