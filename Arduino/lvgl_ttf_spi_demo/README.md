# ESP32 + TFT_eSPI + LVGL Complete Guide

## Table of Contents
1. [Introduction](#introduction)
2. [Architecture Overview](#architecture-overview)
3. [Hardware Requirements](#hardware-requirements)
4. [Software Setup](#software-setup)
5. [Understanding the Components](#understanding-the-components)
6. [Basic Concepts](#basic-concepts)
7. [Code Examples](#code-examples)
8. [Common Patterns](#common-patterns)
9. [Troubleshooting](#troubleshooting)

---

## Introduction

This guide provides a comprehensive introduction to using **LVGL (Light and Versatile Graphics Library)** with **ESP32** and **TFT_eSPI** display drivers. You'll learn how to create interactive graphical user interfaces (GUIs) for embedded systems.

### What You'll Learn
- How ESP32 communicates with TFT displays
- How to initialize and configure LVGL
- How to display text and information
- How to create interactive buttons
- How to handle user input and events
- How to build complete user interfaces

---

## Architecture Overview

### The Three-Layer Stack

```
┌─────────────────────────────────┐
│      Your Application Code       │
│    (LVGL Widgets & Callbacks)    │
└──────────────┬──────────────────┘
               │
┌──────────────▼──────────────────┐
│         LVGL Library             │
│    (Graphics Rendering Engine)   │
└──────────────┬──────────────────┘
               │
┌──────────────▼──────────────────┐
│       TFT_eSPI Driver            │
│    (Hardware Display Interface)  │
└──────────────┬──────────────────┘
               │
┌──────────────▼──────────────────┐
│          ESP32 Hardware          │
│    (SPI Bus, GPIO Pins, etc.)    │
└──────────────────────────────────┘
```

### Data Flow

1. **Your Code** creates LVGL objects (labels, buttons, etc.)
2. **LVGL** manages the graphics, layout, and events
3. **TFT_eSPI** translates LVGL's drawing commands to hardware
4. **ESP32** sends data over SPI to the display

---

## Hardware Requirements

### Required Components
- **ESP32 Development Board** (ESP32-DevKitC or similar)
- **TFT Display** with SPI interface (e.g., ILI9341, ST7789, etc.)
- **Jumper Wires** for connections
- **Power Supply** (USB cable for ESP32)

### Pin Connections

Based on `display_config.h`, here are the typical connections:

| Display Pin | ESP32 GPIO | Function |
|------------|------------|----------|
| MOSI       | GPIO 23    | SPI Data |
| SCLK       | GPIO 18    | SPI Clock |
| CS         | GPIO 5     | Chip Select |
| DC         | GPIO 2     | Data/Command |
| RST        | GPIO 4     | Reset |
| BL         | GPIO 15    | Backlight |
| VCC        | 3.3V       | Power |
| GND        | GND        | Ground |

**Note:** Pin assignments may vary based on your display model. Always check your display's datasheet.

---

## Software Setup

### 1. PlatformIO Configuration

The `platformio.ini` file configures:
- **Platform**: ESP32 (espressif32)
- **Framework**: Arduino
- **Libraries**: 
  - `lvgl/lvgl@^8.3.0` - Graphics library
  - `bodmer/TFT_eSPI@^2.5.0` - Display driver

### 2. TFT_eSPI Configuration

Before using TFT_eSPI, you must configure it for your display:

1. Navigate to: `~/.platformio/packages/framework-arduinoespressif32/libraries/TFT_eSPI/`
2. Edit `User_Setup.h` or create `User_Setup_Select.h`
3. Uncomment your display driver (e.g., `ILI9341_DRIVER`)
4. Set the correct pin definitions

**Example User_Setup.h configuration:**
```cpp
#define ILI9341_DRIVER
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
#define TFT_BL   15
```

---

## Understanding the Components

### 1. ESP32 (Microcontroller)

The ESP32 is a powerful microcontroller with:
- **Dual-core processor** (240 MHz)
- **WiFi and Bluetooth** capabilities
- **SPI interface** for display communication
- **GPIO pins** for control signals
- **PSRAM** (optional) for graphics buffers

### 2. TFT_eSPI (Display Driver)

TFT_eSPI is a library that:
- Handles **SPI communication** with the display
- Provides **low-level drawing functions** (pixels, lines, rectangles)
- Manages **display initialization** and configuration
- Supports **multiple display controllers** (ILI9341, ST7789, etc.)

**Key Functions:**
- `tft.init()` - Initialize the display
- `tft.fillScreen(color)` - Fill entire screen
- `tft.setAddrWindow(x, y, w, h)` - Set drawing area
- `tft.pushColors(data, count)` - Send pixel data

### 3. LVGL (Graphics Library)

LVGL is a graphics library that provides:
- **Widget system** (buttons, labels, sliders, etc.)
- **Layout management** (flex, grid)
- **Event handling** (clicks, drags, etc.)
- **Animation support**
- **Theme system** for styling

**Key Concepts:**
- **Objects**: Everything in LVGL is an object (screen, button, label)
- **Parent-Child**: Objects form a tree structure
- **Events**: User interactions trigger events
- **Callbacks**: Functions called when events occur

---

## Basic Concepts

### 1. LVGL Initialization Flow

```cpp
// Step 1: Initialize LVGL library
lv_init();

// Step 2: Create a display buffer
static lv_color_t buf1[DISPLAY_BUF_SIZE];
static lv_color_t buf2[DISPLAY_BUF_SIZE];  // Double buffering

// Step 3: Register display driver
lv_display_t *disp = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
lv_display_set_flush_cb(disp, display_flush);

// Step 4: Create input device (touch/mouse)
lv_indev_t *indev = lv_indev_create();
lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
lv_indev_set_read_cb(indev, touchpad_read);

// Step 5: Create your UI
create_ui();
```

### 2. Display Flush Callback

LVGL calls this function when it needs to update the display:

```cpp
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    // area: Region to update (x1, y1, x2, y2)
    // px_map: Pixel data buffer
    
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)px_map, w * h, true);
    tft.endWrite();
    
    // Tell LVGL we're done
    lv_display_flush_ready(disp);
}
```

### 3. Creating Objects

All LVGL objects follow this pattern:

```cpp
// Create object
lv_obj_t *obj = lv_obj_create(parent);

// Set properties
lv_obj_set_size(obj, width, height);
lv_obj_set_pos(obj, x, y);
lv_obj_set_style_bg_color(obj, lv_color_hex(0x0000FF), 0);

// Add to parent (if not screen)
lv_obj_set_parent(obj, parent);
```

### 4. Event Handling

```cpp
// Create button
lv_obj_t *btn = lv_btn_create(lv_scr_act());

// Add event callback
lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED, NULL);

// Event handler function
void button_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        Serial.println("Button clicked!");
    }
}
```

---

## Code Examples

### Example 1: Basic Display Setup
**File:** `01_basic_setup.ino`

This example shows the minimal code needed to initialize the display and LVGL.

**Key Learning Points:**
- Display initialization sequence
- LVGL initialization
- Buffer allocation
- Basic screen creation

### Example 2: Displaying Text
**File:** `02_display_text.ino`

This example demonstrates how to create and style text labels.

**Key Learning Points:**
- Creating labels
- Setting text content
- Text alignment
- Font styling
- Color management

### Example 3: Creating Buttons
**File:** `03_create_buttons.ino`

This example shows how to create buttons and handle clicks.

**Key Learning Points:**
- Button creation
- Button styling
- Event callbacks
- User interaction handling

### Example 4: Complete UI Example
**File:** `04_complete_ui.ino`

This example combines everything into a functional interface.

**Key Learning Points:**
- Multiple widgets
- Layout management
- State management
- Complex event handling

---

## Common Patterns

### Pattern 1: Updating Display Information

```cpp
// Create label once
lv_obj_t *info_label = lv_label_create(lv_scr_act());

// Update text in loop
void loop() {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 1000) {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Time: %lu ms", millis());
        lv_label_set_text(info_label, buffer);
        lastUpdate = millis();
    }
    lv_timer_handler();  // Must call this regularly
}
```

### Pattern 2: Button with State

```cpp
static bool led_state = false;

void toggle_led_cb(lv_event_t *e) {
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
    
    lv_obj_t *btn = lv_event_get_target(e);
    if (led_state) {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), 0);
    } else {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), 0);
    }
}
```

### Pattern 3: Screen Navigation

```cpp
lv_obj_t *screen1;
lv_obj_t *screen2;

void create_screens() {
    screen1 = lv_obj_create(NULL);
    screen2 = lv_obj_create(NULL);
    
    // Add content to screens...
}

void switch_to_screen2(lv_event_t *e) {
    lv_scr_load(screen2);
}
```

### Pattern 4: Progress Indicator

```cpp
lv_obj_t *bar = lv_bar_create(lv_scr_act());
lv_bar_set_range(bar, 0, 100);
lv_bar_set_value(bar, 50, LV_ANIM_ON);
```

---

## Troubleshooting

### Problem: Display shows nothing / blank screen

**Solutions:**
1. Check SPI connections (MOSI, SCLK, CS, DC, RST)
2. Verify TFT_eSPI User_Setup.h configuration
3. Check display power supply (3.3V)
4. Verify backlight pin connection
5. Try different display rotation: `tft.setRotation(0-3)`

### Problem: Display shows garbled colors

**Solutions:**
1. Enable byte swapping: `tft.setSwapBytes(true)`
2. Check color format in LVGL config (should be RGB565)
3. Verify display controller type in User_Setup.h

### Problem: LVGL objects don't appear

**Solutions:**
1. Ensure `lv_timer_handler()` is called regularly in `loop()`
2. Check that objects are added to a screen: `lv_scr_act()` or custom screen
3. Verify display buffer size is sufficient
4. Check Serial output for LVGL error messages

### Problem: Buttons don't respond to clicks

**Solutions:**
1. Verify touch input callback is registered
2. Check touch pin connections
3. Implement touchpad_read() function properly
4. Test with mouse input device if available

### Problem: Low frame rate / slow updates

**Solutions:**
1. Increase display buffer size
2. Use partial rendering mode
3. Reduce number of objects on screen
4. Enable PSRAM if available
5. Optimize flush callback (minimize SPI overhead)

### Problem: Memory issues / crashes

**Solutions:**
1. Reduce display buffer size
2. Use smaller color depth if possible
3. Enable PSRAM: `-DBOARD_HAS_PSRAM` in platformio.ini
4. Reduce number of LVGL objects
5. Check available heap: `ESP.getFreeHeap()`

---

## Best Practices

### 1. Memory Management
- Use static buffers when possible
- Monitor heap usage during development
- Free unused objects: `lv_obj_del(obj)`

### 2. Performance
- Call `lv_timer_handler()` frequently (every 5-10ms)
- Use double buffering for smooth updates
- Minimize full-screen redraws

### 3. Code Organization
- Separate UI creation into functions
- Use meaningful variable names
- Comment complex logic
- Group related objects together

### 4. Debugging
- Use Serial output for debugging
- Check LVGL log levels
- Monitor frame rate
- Test with simple examples first

---

## Additional Resources

### Official Documentation
- **LVGL**: https://docs.lvgl.io/
- **TFT_eSPI**: https://github.com/Bodmer/TFT_eSPI
- **ESP32**: https://docs.espressif.com/

### LVGL Widgets Reference
- Labels: `lv_label_create()`
- Buttons: `lv_btn_create()`
- Sliders: `lv_slider_create()`
- Charts: `lv_chart_create()`
- Lists: `lv_list_create()`
- And many more!

### Next Steps
1. Experiment with different widgets
2. Try creating custom themes
3. Implement animations
4. Add touch gestures
5. Build a complete application

---

## Summary

This guide has covered:
- ✅ Architecture of ESP32 + TFT_eSPI + LVGL
- ✅ Hardware connections and setup
- ✅ Software configuration
- ✅ Basic LVGL concepts
- ✅ Displaying information
- ✅ Creating and handling buttons
- ✅ Common patterns and best practices

**You're now ready to build your own embedded GUI applications!**

For hands-on learning, start with the example files in this directory and modify them to experiment with different features.
