#ifndef SPO2_ALGORITHM_H
#define SPO2_ALGORITHM_H

#include <stdint.h>

#define SPO2_BUFFER_SIZE 100

class SpO2Algorithm {
public:
    SpO2Algorithm();
    void addSample(uint32_t red, uint32_t ir);
    uint8_t getSpO2();
    bool isDataReady();
    void reset();
    
private:
    uint32_t _redBuffer[SPO2_BUFFER_SIZE];
    uint32_t _irBuffer[SPO2_BUFFER_SIZE];
    uint8_t _bufferIndex;
    bool _dataReady;
    
    float calculateRatio();
    float calculateACComponent(uint32_t *buffer);
    float calculateDCComponent(uint32_t *buffer);
};

#endif
