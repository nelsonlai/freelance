# Quick Start Guide

## Hardware Connections

### MAX30102 to ESP32
- VIN → 3.3V (or 5V if module has regulator)
- GND → GND
- SDA → GPIO 21 (or as configured)
- SCL → GPIO 22 (or as configured)
- INT → Not used (optional)

### Display to ESP32
- VCC → 3.3V or 5V (check display specs)
- GND → GND
- MOSI → GPIO 23
- SCLK → GPIO 18
- CS → GPIO 5
- DC → GPIO 2
- RST → GPIO 4
- BL → GPIO 15 (backlight)

## Software Setup

### Step 1: Install Arduino IDE
1. Download from https://www.arduino.cc/en/software
2. Install ESP32 board support (see README.md)

### Step 2: Install Libraries
Open Arduino IDE → Sketch → Include Library → Manage Libraries

Install:
- **LVGL** (by LVGL) - version 8.3.0 or later
- **TFT_eSPI** (by Bodmer) - if using compatible display

### Step 3: Configure TFT_eSPI (REQUIRED)
**IMPORTANT**: You must configure TFT_eSPI before uploading code!

1. Navigate to: `Arduino/libraries/TFT_eSPI/`
2. Edit `User_Setup.h` file
3. Uncomment your display driver (e.g., `#define ILI9341_DRIVER`)
4. Configure pins to match `display_config.h`:
   ```cpp
   #define TFT_MOSI 23
   #define TFT_SCLK 18
   #define TFT_CS   5
   #define TFT_DC   2
   #define TFT_RST  4
   ```
5. Set display dimensions (e.g., `#define TFT_WIDTH 320`, `#define TFT_HEIGHT 240`)
6. Save the file
7. **Restart Arduino IDE** (required for changes to take effect)

See `TFT_eSPI_SETUP.md` for detailed instructions and common display configurations.

### Step 4: Configure Pins
Edit `display_config.h` to match your hardware connections.

### Step 5: Upload Code
1. Open `MAX30102_HealthMonitor.ino`
2. Select Board: Tools → Board → ESP32 Dev Module
3. Select Port: Tools → Port → (your ESP32 port)
4. Click Upload

## First Run

1. Open Serial Monitor (115200 baud)
2. You should see initialization messages
3. If MAX30102 is not detected, check I2C connections
4. Display should show the main menu

## Testing Sensors

1. Navigate to "Heart Rate" or "Blood Oxygen"
2. Place finger firmly on MAX30102 sensor
3. Wait 10-20 seconds for readings to stabilize
4. Ensure good contact - readings should appear

## Troubleshooting

**No display output:**
- Check SPI connections
- Verify display library configuration
- Check backlight pin

**MAX30102 not found:**
- Verify I2C connections (SDA/SCL)
- Check power supply
- Try different I2C pins

**No sensor readings:**
- Ensure finger covers sensor completely
- Wait longer for algorithms to process
- Check Serial Monitor for errors

**Clock shows 00:00:00:**
- WiFi not connected (NTP requires internet)
- Configure WiFi in main sketch
- Or set time manually

## Next Steps

- Configure WiFi for NTP time sync
- Adjust sensor LED current if readings are weak
- Customize UI colors and fonts
- Add data logging functionality
