#include "display_driver.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Arduino.h>

// TFT_eSPI instance
TFT_eSPI tft = TFT_eSPI();

// Static instance for callback
static DisplayDriver *g_displayDriver = nullptr;

DisplayDriver::DisplayDriver() {
    g_displayDriver = this;
}

bool DisplayDriver::init() {
    Serial.print("[DISPLAY] Initializing SPI... ");
    // Initialize SPI with custom pins
    // Note: TFT_eSPI typically uses User_Setup.h for pin configuration
    SPI.begin();
    Serial.println("OK");
    
    Serial.print("[DISPLAY] Initializing TFT_eSPI display... ");
    // Initialize TFT_eSPI display
    // Note: Make sure User_Setup.h in TFT_eSPI library is configured for your display
    tft.init();
    Serial.println("OK");
    
    Serial.print("[DISPLAY] Configuring display... ");
    tft.setRotation(0);  // 0 = portrait, 1 = landscape, 2 = inverted portrait, 3 = inverted landscape
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);  // Required for LVGL color format
    Serial.println("OK");
    Serial.print("[DISPLAY]   Rotation: Portrait (0)");
    Serial.print(" | Color format: RGB565 with byte swap");
    Serial.println();
    
    Serial.print("[DISPLAY] Initializing backlight (GPIO ");
    Serial.print(DISPLAY_BL);
    Serial.print(")... ");
    // Initialize backlight
    pinMode(DISPLAY_BL, OUTPUT);
    setBrightness(80);
    Serial.println("OK");
    Serial.println("[DISPLAY]   Backlight: 80%");
    
    // Initialize touch (if available)
    Serial.print("[DISPLAY] Initializing touch input... ");
    initTouch();
    Serial.println("OK (placeholder - implement if using touch)");
    
    Serial.println("[DISPLAY] Display initialization complete");
    return true;
}

void DisplayDriver::initDisplay() {
    // Display initialization is done in init()
    // TFT_eSPI is initialized in init() method
}

void DisplayDriver::initTouch() {
    // Touch initialization if using touch screen
    // This is a placeholder - adjust based on your touch controller
}

void DisplayDriver::flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    static uint32_t flushCount = 0;
    static unsigned long lastFlushLogTime = 0;
    static uint32_t totalPixels = 0;
    
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    uint32_t pixelCount = w * h;
    
    // TFT_eSPI flush implementation
    unsigned long flushStart = micros();
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)px_map, pixelCount, true);
    tft.endWrite();
    unsigned long flushTime = micros() - flushStart;
    
    flushCount++;
    totalPixels += pixelCount;
    
    // Log flush statistics every 100 flushes or every 5 seconds
    unsigned long currentTime = millis();
    if (flushCount % 100 == 0 || (currentTime - lastFlushLogTime) >= 5000) {
        float avgPixels = (float)totalPixels / flushCount;
        float fps = 1000.0 / ((float)(currentTime - lastFlushLogTime) / flushCount);
        
        Serial.print("[DISPLAY] Flush stats: Count=");
        Serial.print(flushCount);
        Serial.print(" | Avg pixels/flush=");
        Serial.print(avgPixels, 0);
        Serial.print(" | Last flush time=");
        Serial.print(flushTime / 1000.0, 2);
        Serial.print("ms | Est. FPS=");
        Serial.print(fps, 1);
        Serial.println();
        
        lastFlushLogTime = currentTime;
        totalPixels = 0;
    }
    
    // Tell LVGL that flushing is done
    lv_display_flush_ready(disp);
}

void DisplayDriver::setBrightness(uint8_t brightness) {
    static uint8_t lastBrightness = 255;  // Initialize to invalid value
    
    uint8_t pwmValue = map(brightness, 0, 100, 0, 255);
    analogWrite(DISPLAY_BL, pwmValue);
    
    // Log brightness changes
    if (brightness != lastBrightness) {
        Serial.print("[DISPLAY] Brightness changed: ");
        Serial.print(lastBrightness);
        Serial.print("% -> ");
        Serial.print(brightness);
        Serial.print("% (PWM: ");
        Serial.print(pwmValue);
        Serial.println(")");
        lastBrightness = brightness;
    }
}

// LVGL callbacks
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    if (g_displayDriver) {
        g_displayDriver->flush(disp, area, px_map);
    }
}

void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    // Touch input handling
    // This is a placeholder - implement based on your touch controller
    data->state = LV_INDEV_STATE_RELEASED;
}
