# MAX30102 Health Monitor with ESP32 and LVGL

A comprehensive health monitoring system using ESP32, MAX30102 pulse oximeter sensor, and LVGL for the user interface.

## Features

- **Clock Display**: Analog and digital clock formats
- **Temperature Monitoring**: Real-time temperature readings from MAX30102
- **Heart Rate Monitoring**: Continuous heart rate measurement
- **Blood Oxygen (SpO2)**: Blood oxygen saturation monitoring
- **Settings Menu**: Configurable brightness, clock format, and temperature units
- **Modern UI**: Beautiful LVGL-based interface

## Hardware Requirements

- ESP32 development board
- MAX30102 pulse oximeter sensor module
- TFT display (320x240 or compatible)
- I2C connections for MAX30102
- SPI connections for display

## Pin Configuration

Edit `display_config.h` to match your hardware:

```cpp
// Display pins
#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240
#define DISPLAY_MOSI   23
#define DISPLAY_SCLK   18
#define DISPLAY_CS     5
#define DISPLAY_DC     2
#define DISPLAY_RST    4
#define DISPLAY_BL     15

// I2C pins for MAX30102
#define I2C_SDA        21
#define I2C_SCL        22
```

## Software Requirements

### Arduino IDE Setup

1. Install ESP32 board support:
   - Go to File → Preferences
   - Add this URL to Additional Board Manager URLs:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to Tools → Board → Boards Manager
   - Search for "ESP32" and install

2. Install required libraries:
   - **LVGL** (v8.3 or later): Install via Library Manager
   - **TFT_eSPI**: Install via Library Manager (or use your display's library)
   - **Wire** and **SPI**: Included with ESP32

3. Configure TFT_eSPI:
   - **IMPORTANT**: Edit `User_Setup.h` in TFT_eSPI library folder
   - See `TFT_eSPI_SETUP.md` for detailed instructions
   - Uncomment your display driver (ILI9341, ST7789, ST7735, etc.)
   - Configure pins to match `display_config.h`
   - Set display width and height
   - Save and restart Arduino IDE

### PlatformIO Setup

Create a `platformio.ini` file (see below) and install dependencies.

## Installation

1. Clone or download this repository
2. Open `MAX30102_HealthMonitor.ino` in Arduino IDE
3. Select your ESP32 board:
   - Tools → Board → ESP32 Arduino → Your ESP32 board
4. Select the correct port
5. Adjust pin configurations in `display_config.h` if needed
6. Upload the code

## Usage

1. **Initial Setup**: 
   - Connect MAX30102 to ESP32 via I2C (SDA/SCL)
   - Connect display via SPI
   - Power on the device

2. **Main Menu**: 
   - Navigate using touch or buttons
   - Select "Clock" for time display
   - Select "Temperature" for temperature readings
   - Select "Heart Rate" for HR monitoring
   - Select "Blood Oxygen" for SpO2 monitoring
   - Select "Settings" (gear icon) for configuration

3. **Clock Display**:
   - Switch between analog and digital formats
   - Time syncs via NTP (requires WiFi connection)

4. **Sensor Readings**:
   - Place finger on MAX30102 sensor
   - Wait a few seconds for readings to stabilize
   - Heart rate and SpO2 require good contact

5. **Settings**:
   - Adjust display brightness
   - Switch clock format (analog/digital)
   - Change temperature unit (Celsius/Fahrenheit)

## WiFi Configuration (Optional)

For NTP time synchronization, configure WiFi in the main sketch:

```cpp
#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// In setup():
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
```

## Troubleshooting

### MAX30102 Not Detected
- Check I2C connections (SDA/SCL)
- Verify I2C address (should be 0xAE)
- Check power supply (1.8V for VDD, 3.3V for LED)

### Display Not Working
- Verify SPI connections
- Check display initialization in `display_driver.cpp`
- Adjust display library settings
- Verify backlight pin connection

### No Sensor Readings
- Ensure finger is properly placed on sensor
- Check sensor LED brightness (may need adjustment)
- Wait 10-20 seconds for algorithms to stabilize
- Verify FIFO data is being read

### LVGL Errors
- Ensure LVGL library is properly installed
- Check buffer allocation (may need adjustment for your ESP32)
- Verify display dimensions match your hardware

## File Structure

```
Arduino/
├── MAX30102_HealthMonitor.ino  # Main application
├── MAX30102_Driver.h/cpp       # MAX30102 sensor driver
├── HeartRateAlgorithm.h/cpp    # Heart rate calculation
├── SpO2Algorithm.h/cpp         # SpO2 calculation
├── display_driver.h/cpp        # Display initialization
├── display_config.h            # Hardware pin configuration
├── ui_manager.h/cpp            # LVGL UI management
└── README.md                   # This file
```

## Algorithm Notes

The heart rate and SpO2 algorithms are simplified implementations. For production use, consider:
- More sophisticated peak detection
- Filtering and noise reduction
- Calibration procedures
- Lookup tables for SpO2 calculation

## License

This project is provided as-is for educational and development purposes.

## References

- [MAX30102 Datasheet](max30102.pdf)
- [LVGL Documentation](https://docs.lvgl.io/)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
