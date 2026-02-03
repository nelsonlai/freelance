# TFT_eSPI Configuration Guide

## Important: Configure User_Setup.h

TFT_eSPI requires configuration in the `User_Setup.h` file before use. Follow these steps:

## Step 1: Locate User_Setup.h

Navigate to your Arduino libraries folder:
- **Windows**: `Documents\Arduino\libraries\TFT_eSPI\`
- **Mac**: `~/Documents/Arduino/libraries/TFT_eSPI/`
- **Linux**: `~/Arduino/libraries/TFT_eSPI/`

## Step 2: Edit User_Setup.h

Open `User_Setup.h` in a text editor.

## Step 3: Select Your Display Driver

Uncomment the line for your display. Common options:

```cpp
// For ILI9341 displays (320x240, 240x320)
#define ILI9341_DRIVER

// For ST7735 displays (128x128, 128x160, 160x128)
#define ST7735_DRIVER

// For ST7789 displays (240x240, 240x320, 320x240)
#define ST7789_DRIVER

// For ILI9163 displays
#define ILI9163_DRIVER
```

## Step 4: Configure Pins

Find the pin configuration section and update it to match `display_config.h`:

```cpp
// ESP32 pin configuration (match display_config.h)
#define TFT_MOSI 23  // DISPLAY_MOSI
#define TFT_SCLK 18  // DISPLAY_SCLK
#define TFT_CS   5   // DISPLAY_CS
#define TFT_DC   2   // DISPLAY_DC
#define TFT_RST  4   // DISPLAY_RST

// Optional: If your display doesn't use a reset pin
// #define TFT_RST  -1

// Optional: MISO pin (not used for most displays)
// #define TFT_MISO 19
```

## Step 5: Configure Display Size

Set the display dimensions:

```cpp
// For 320x240 displays
#define TFT_WIDTH  320
#define TFT_HEIGHT 240

// For 240x320 displays (portrait)
// #define TFT_WIDTH  240
// #define TFT_HEIGHT 320
```

## Step 6: Configure SPI Settings (if needed)

For ESP32, you may need to configure SPI:

```cpp
// ESP32 specific settings
#define ESP32_PARALLEL
// or
#define ESP32_DMA
```

## Step 7: Save and Restart Arduino IDE

1. Save `User_Setup.h`
2. Close and restart Arduino IDE
3. Recompile your sketch

## Common Display Configurations

### ILI9341 (320x240)
```cpp
#define ILI9341_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 240
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
```

### ST7789 (240x240)
```cpp
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 240
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
```

### ST7735 (128x160)
```cpp
#define ST7735_DRIVER
#define TFT_WIDTH  128
#define TFT_HEIGHT 160
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
```

## Troubleshooting

### Display shows nothing
- Verify User_Setup.h is configured correctly
- Check pin connections
- Verify display type is correct
- Try different rotation: `tft.setRotation(1)` in code

### Wrong colors
- Add `tft.setSwapBytes(true);` in init() (already included)
- Check if display uses BGR instead of RGB
- Some displays need color inversion

### Display flickers
- Increase LVGL buffer size
- Reduce refresh rate
- Check SPI speed settings

### Compilation errors
- Make sure TFT_eSPI library is installed
- Restart Arduino IDE after editing User_Setup.h
- Check for conflicting pin definitions

## Alternative: Programmatic Configuration

If you prefer not to edit User_Setup.h, you can configure TFT_eSPI programmatically, but this requires modifying the library or using a different approach. The User_Setup.h method is recommended.

## Additional Resources

- [TFT_eSPI GitHub](https://github.com/Bodmer/TFT_eSPI)
- [TFT_eSPI Wiki](https://github.com/Bodmer/TFT_eSPI/wiki)
- Check your display's datasheet for driver chip information
