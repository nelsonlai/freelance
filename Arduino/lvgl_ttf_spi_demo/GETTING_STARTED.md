# Getting Started Guide

This guide will help you set up your development environment and run your first LVGL example on ESP32 with TFT display.

## Prerequisites

### Hardware Required
- ESP32 development board (ESP32-DevKitC or similar)
- TFT display with SPI interface (e.g., ILI9341, ST7789)
- Jumper wires for connections
- USB cable for ESP32
- Breadboard (optional, for easier connections)

### Software Required
- **PlatformIO** (recommended) or Arduino IDE
- **VS Code** with PlatformIO extension (if using PlatformIO)
- USB drivers for ESP32 (CP2102 or CH340)

---

## Step 1: Install PlatformIO

### Option A: VS Code Extension (Recommended)
1. Install Visual Studio Code
2. Open VS Code
3. Go to Extensions (Ctrl+Shift+X / Cmd+Shift+X)
4. Search for "PlatformIO IDE"
5. Click Install

### Option B: Standalone PlatformIO Core
1. Visit: https://platformio.org/install/cli
2. Follow installation instructions for your OS

### Verify Installation
Open terminal/command prompt and run:
```bash
pio --version
```

---

## Step 2: Configure TFT_eSPI Library

**IMPORTANT:** This step is required before compiling any code!

### Find TFT_eSPI Library Location

1. Open terminal in your project directory
2. Run: `pio pkg list` to see installed packages
3. Or navigate to PlatformIO packages directory:
   - **Windows:** `%USERPROFILE%\.platformio\packages\framework-arduinoespressif32\libraries\TFT_eSPI`
   - **macOS/Linux:** `~/.platformio/packages/framework-arduinoespressif32/libraries/TFT_eSPI`

### Configure User_Setup.h

1. Navigate to the TFT_eSPI library folder
2. Open `User_Setup.h` (or create `User_Setup_Select.h`)
3. Uncomment your display driver, for example:

```cpp
// For ILI9341 display:
#define ILI9341_DRIVER

// For ST7789 display:
// #define ST7789_DRIVER

// Pin definitions (adjust to match your wiring):
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
#define TFT_BL   15

// Display orientation
#define TFT_ROTATION 0  // 0=portrait, 1=landscape
```

### Common Display Drivers
- `ILI9341_DRIVER` - Common 2.8" displays
- `ST7789_DRIVER` - Common 1.3" and 1.54" displays
- `ST7735_DRIVER` - Common 1.8" displays
- Check your display's datasheet for the correct driver

---

## Step 3: Wire Your Display

Connect your TFT display to ESP32 according to the pin definitions in `display_config.h`:

| Display Pin | ESP32 GPIO | Description |
|------------|------------|-------------|
| VCC        | 3.3V       | Power (3.3V, NOT 5V!) |
| GND        | GND        | Ground |
| MOSI/SDA   | GPIO 23    | SPI Data |
| SCLK/SCL   | GPIO 18    | SPI Clock |
| CS         | GPIO 5     | Chip Select |
| DC/A0      | GPIO 2     | Data/Command |
| RST        | GPIO 4     | Reset |
| BL         | GPIO 15    | Backlight (optional) |

**⚠️ Warning:** 
- Use 3.3V for VCC, NOT 5V!
- Double-check your display's pinout - they vary by manufacturer
- Some displays have different pin names (MOSI vs SDA, etc.)

---

## Step 4: Open the Project

### Using PlatformIO in VS Code:
1. Open VS Code
2. File → Open Folder
3. Navigate to the `lvgl_ttf_spi_demo` folder
4. PlatformIO should detect the project automatically

### Using PlatformIO CLI:
```bash
cd lvgl_ttf_spi_demo
pio run
```

---

## Step 5: Select Your Example

The project contains multiple example files. To use one:

1. **Rename the example file** to `main.cpp` or `main.ino`
2. Or create a `src` folder and copy the example there
3. Or use PlatformIO's multiple source files feature

### Quick Method (PlatformIO):
1. Copy the example code you want to try
2. Create `src/main.cpp` and paste the code
3. Compile and upload

### Example: Using 01_basic_setup.ino
```bash
# Copy example to src folder
cp 01_basic_setup.ino src/main.cpp

# Compile
pio run

# Upload
pio run -t upload

# Monitor serial output
pio device monitor
```

---

## Step 6: Compile and Upload

### Using PlatformIO Toolbar (VS Code):
1. Click the checkmark icon (✓) to compile
2. Click the arrow icon (→) to upload
3. Click the plug icon (🔌) to open serial monitor

### Using PlatformIO CLI:
```bash
# Compile
pio run

# Upload
pio run -t upload

# Monitor serial output
pio device monitor
```

### Using Arduino IDE:
1. Install ESP32 board support (if not already installed)
2. Install LVGL and TFT_eSPI libraries via Library Manager
3. Open the .ino file
4. Select Tools → Board → ESP32 Dev Module
5. Select Tools → Port → (your ESP32 port)
6. Click Upload

---

## Step 7: Verify It Works

After uploading:

1. **Check Serial Monitor:**
   - Open serial monitor (115200 baud)
   - You should see initialization messages
   - Look for "[DISPLAY] Display initialization complete"

2. **Check Display:**
   - Display should show the example UI
   - If blank, check:
     - Power connections (3.3V and GND)
     - SPI connections (MOSI, SCLK, CS, DC, RST)
     - Backlight connection (if applicable)
     - TFT_eSPI User_Setup.h configuration

3. **Common Issues:**
   - **Blank screen:** Check wiring and User_Setup.h
   - **Garbled colors:** Enable `tft.setSwapBytes(true)`
   - **Nothing happens:** Check serial monitor for errors
   - **Compilation errors:** Verify TFT_eSPI is configured correctly

---

## Step 8: Try Different Examples

Work through the examples in order:

1. **01_basic_setup.ino** - Minimal setup, verify display works
2. **02_display_text.ino** - Learn to display text and information
3. **03_create_buttons.ino** - Learn button creation and event handling
4. **04_complete_ui.ino** - Complete application with multiple screens

Each example builds on the previous one, teaching new concepts.

---

## Troubleshooting

### Display Shows Nothing
- ✅ Check all connections (especially power and ground)
- ✅ Verify TFT_eSPI User_Setup.h matches your display
- ✅ Check backlight connection (if your display has one)
- ✅ Try different rotation: `tft.setRotation(0-3)`
- ✅ Verify display is powered (3.3V, not 5V!)

### Compilation Errors
- ✅ Ensure TFT_eSPI User_Setup.h is configured
- ✅ Check that LVGL and TFT_eSPI libraries are installed
- ✅ Verify platformio.ini has correct library versions
- ✅ Try cleaning build: `pio run -t clean`

### Display Shows Garbled Colors
- ✅ Enable byte swapping: `tft.setSwapBytes(true)`
- ✅ Check color format in LVGL configuration
- ✅ Verify display driver in User_Setup.h

### Buttons Don't Respond
- ✅ Ensure `lv_timer_handler()` is called in `loop()`
- ✅ Check touch input configuration (if using touch)
- ✅ Verify event callbacks are registered correctly

### Memory Issues
- ✅ Reduce display buffer size
- ✅ Enable PSRAM if available: `-DBOARD_HAS_PSRAM`
- ✅ Check free heap: `Serial.println(ESP.getFreeHeap());`

### Serial Monitor Shows Errors
- ✅ Check baud rate (115200)
- ✅ Verify USB cable connection
- ✅ Try different USB port
- ✅ Install correct USB drivers (CP2102 or CH340)

---

## Next Steps

Once you have the basic example working:

1. **Read the README.md** - Comprehensive guide to all concepts
2. **Study the examples** - Each one teaches specific concepts
3. **Try modifications** - Change colors, sizes, positions
4. **Read QUICK_REFERENCE.md** - Quick lookup for common operations
5. **Build your own UI** - Combine what you've learned

---

## Learning Path

### Beginner
1. ✅ Get basic setup working (01_basic_setup.ino)
2. ✅ Display text (02_display_text.ino)
3. ✅ Create buttons (03_create_buttons.ino)

### Intermediate
4. ✅ Complete UI (04_complete_ui.ino)
5. ✅ Experiment with styling
6. ✅ Add more widgets (sliders, charts, etc.)

### Advanced
7. ✅ Multiple screens with navigation
8. ✅ Custom themes
9. ✅ Animations
10. ✅ Touch gestures
11. ✅ Data visualization

---

## Additional Resources

- **LVGL Documentation:** https://docs.lvgl.io/
- **TFT_eSPI GitHub:** https://github.com/Bodmer/TFT_eSPI
- **ESP32 Documentation:** https://docs.espressif.com/
- **PlatformIO Documentation:** https://docs.platformio.org/

---

## Getting Help

If you're stuck:

1. **Check Serial Output** - Often contains helpful error messages
2. **Review Examples** - Compare your code with working examples
3. **Read Documentation** - LVGL and TFT_eSPI have excellent docs
4. **Search Forums** - ESP32 and LVGL communities are very helpful
5. **Simplify** - Start with minimal code and add features gradually

---

## Summary Checklist

Before starting:
- [ ] PlatformIO installed
- [ ] TFT_eSPI User_Setup.h configured
- [ ] Display wired correctly
- [ ] USB drivers installed
- [ ] Project opened in PlatformIO

First example:
- [ ] 01_basic_setup.ino compiles
- [ ] Code uploaded to ESP32
- [ ] Display shows blue rectangle
- [ ] Serial monitor shows initialization messages

Ready to learn:
- [ ] Understand basic setup
- [ ] Can modify example code
- [ ] Ready to try next example

**You're ready to start building embedded GUIs! 🎉**
