#ifndef MAX30102_DRIVER_H
#define MAX30102_DRIVER_H

#include <Wire.h>

// MAX30102 I2C Address
#define MAX30102_ADDRESS 0xAE  // Write address (0x57 << 1)

// Register Addresses
#define REG_INTR_STATUS_1    0x00
#define REG_INTR_STATUS_2    0x01
#define REG_INTR_ENABLE_1    0x02
#define REG_INTR_ENABLE_2    0x03
#define REG_FIFO_WR_PTR     0x04
#define REG_OVF_COUNTER     0x05
#define REG_FIFO_RD_PTR     0x06
#define REG_FIFO_DATA       0x07
#define REG_FIFO_CONFIG     0x08
#define REG_MODE_CONFIG     0x09
#define REG_SPO2_CONFIG     0x0A
#define REG_LED1_PA         0x0C  // Red LED
#define REG_LED2_PA         0x0D  // IR LED
#define REG_PILOT_PA        0x10
#define REG_TEMP_CONFIG     0x21
#define REG_TEMP_FRAC       0x20
#define REG_TEMP_DATA       0x1F
#define REG_REV_ID          0xFE
#define REG_PART_ID         0xFF

// Mode Configuration
#define MODE_SHDN           0x80
#define MODE_RESET          0x40
#define MODE_HR_ONLY        0x02
#define MODE_SPO2           0x03
#define MODE_MULTI_LED      0x07

// SpO2 Configuration
#define SPO2_ADC_RGE_2048   0x00
#define SPO2_ADC_RGE_4096   0x20
#define SPO2_ADC_RGE_8192   0x40
#define SPO2_ADC_RGE_16384  0x60
#define SPO2_SR_50          0x00
#define SPO2_SR_100         0x04
#define SPO2_SR_200         0x08
#define SPO2_SR_400         0x0C
#define SPO2_SR_800         0x10
#define SPO2_SR_1000        0x14
#define SPO2_SR_1600        0x18
#define SPO2_SR_3200        0x1C
#define LED_PW_69           0x00
#define LED_PW_118          0x01
#define LED_PW_215          0x02
#define LED_PW_411          0x03

class MAX30102 {
public:
    MAX30102();
    bool begin(TwoWire &wire = Wire);
    bool isConnected();
    void reset();
    void setup();
    bool readFIFO(uint32_t *red, uint32_t *ir);
    float readTemperature();
    void setLEDCurrent(uint8_t redCurrent, uint8_t irCurrent);
    void setSampleRate(uint8_t sampleRate);
    void setPulseWidth(uint8_t pulseWidth);
    void setADCRange(uint8_t adcRange);
    void enableFIFORollover(bool enable);
    void clearFIFO();
    uint8_t getWritePointer();
    uint8_t getReadPointer();
    uint8_t getOVFCounter();
    
private:
    TwoWire *_wire;
    uint8_t _address;
    bool writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    void readRegisters(uint8_t reg, uint8_t *buffer, uint8_t len);
};

#endif
