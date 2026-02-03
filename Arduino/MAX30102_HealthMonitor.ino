/*
 * MAX30102 Health Monitor with ESP32 and LVGL
 * 
 * Features:
 * - Clock display (Analog and Digital)
 * - Temperature monitoring
 * - Heart Rate monitoring
 * - Blood Oxygen (SpO2) monitoring
 * - Settings menu
 */

#include <lvgl.h>
#include <Wire.h>
#include <time.h>
#include "MAX30102_Driver.h"
#include "HeartRateAlgorithm.h"
#include "SpO2Algorithm.h"
#include "display_driver.h"
#include "display_config.h"
#include "ui_manager.h"

// Global objects
MAX30102 max30102;
HeartRateAlgorithm hrAlgorithm;
SpO2Algorithm spo2Algorithm;
DisplayDriver displayDriver;
UIManager uiManager;

// Display buffer for LVGL
static lv_display_t *display;
static lv_color_t *buf1;
static lv_color_t *buf2;

// Timing
unsigned long lastSensorRead = 0;
unsigned long lastClockUpdate = 0;
unsigned long lastTempRead = 0;
const unsigned long SENSOR_READ_INTERVAL = 10;  // 10ms for 100Hz
const unsigned long CLOCK_UPDATE_INTERVAL = 1000;  // 1 second
const unsigned long TEMP_READ_INTERVAL = 5000;  // 5 seconds

// Sensor data
float currentTemperature = 0.0;
uint8_t currentHeartRate = 0;
uint8_t currentSpO2 = 0;

// Settings
bool useCelsius = true;
bool useAnalogClock = true;

// Forward declarations
void setupLVGL();
void updateSensors();
void handleUIEvents();

void setManualTime() {
    struct tm tm;
    tm.tm_year = 2026 - 1900;  // Year since 1900
    tm.tm_mon  = 0;            // Month (0 = January)
    tm.tm_mday = 10;           // Day
    tm.tm_hour = 14;           // Hour (24h format)
    tm.tm_min  = 30;           // Minute
    tm.tm_sec  = 0;            // Second

    time_t t = mktime(&tm);

    struct timeval now = { .tv_sec = t };
    settimeofday(&now, NULL);
}
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n========================================");
    Serial.println("MAX30102 Health Monitor - Starting Up");
    Serial.println("========================================\n");
    
    Serial.println("[SETUP] Step 1/6: Initializing Serial Communication");
    Serial.print("[SETUP] Serial baud rate: 115200");
    Serial.println(" - OK");
    
    // Initialize I2C for MAX30102
    Serial.println("[SETUP] Step 2/6: Initializing I2C Bus");
    Serial.print("[SETUP] I2C SDA pin: GPIO ");
    Serial.print(I2C_SDA);
    Serial.print(", SCL pin: GPIO ");
    Serial.print(I2C_SCL);
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.println(" - OK");
    
    // Initialize MAX30102
    Serial.println("[SETUP] Step 3/6: Initializing MAX30102 Sensor");
    Serial.print("[SETUP] Checking device at I2C address 0x");
    Serial.print(MAX30102_ADDRESS, HEX);
    Serial.print("... ");
    if (!max30102.begin(Wire)) {
        Serial.println("FAILED");
        Serial.println("[ERROR] MAX30102 not found on I2C bus!");
        Serial.println("[ERROR] Please check:");
        Serial.println("[ERROR]   - I2C connections (SDA/SCL)");
        Serial.println("[ERROR]   - Power supply (1.8V for VDD, 3.3V for LED)");
        Serial.println("[ERROR]   - I2C address (should be 0xAE)");
        while(1) {
            delay(1000);
            Serial.println("[ERROR] System halted - fix MAX30102 connection");
        }
    }
    Serial.println("OK");
    Serial.println("[SETUP] MAX30102 initialized successfully");
    Serial.println("[SETUP]   - Mode: SpO2 (Red + IR LEDs)");
    Serial.println("[SETUP]   - Sample rate: 100 Hz");
    Serial.println("[SETUP]   - LED pulse width: 411 μs");
    Serial.println("[SETUP]   - ADC range: 4096 nA");
    Serial.println("[SETUP]   - LED current: Red=6.4mA, IR=6.4mA");
    
    // Initialize display
    Serial.println("[SETUP] Step 4/6: Initializing Display");
    if (!displayDriver.init()) {
        Serial.println("[ERROR] Display initialization failed!");
        Serial.println("[ERROR] Please check:");
        Serial.println("[ERROR]   - SPI connections (MOSI, SCLK, CS, DC, RST)");
        Serial.println("[ERROR]   - TFT_eSPI User_Setup.h configuration");
        Serial.println("[ERROR]   - Display power supply");
        while(1) {
            delay(1000);
            Serial.println("[ERROR] System halted - fix display connection");
        }
    }
    Serial.println("[SETUP] Display initialized successfully");
    Serial.print("[SETUP]   - Resolution: ");
    Serial.print(DISPLAY_WIDTH);
    Serial.print("x");
    Serial.println(DISPLAY_HEIGHT);
    Serial.println("[SETUP]   - Backlight: 80%");
    
    // Setup LVGL
    Serial.println("[SETUP] Step 5/6: Initializing LVGL Graphics Library");
    setupLVGL();
    
    // Initialize UI
    Serial.println("[SETUP] Step 6/6: Creating User Interface");
    Serial.println("[SETUP] Creating UI screens...");
    uiManager.init();
    Serial.println("[SETUP] UI initialization complete");
    Serial.println("[SETUP]   - Main menu screen created");
    Serial.println("[SETUP]   - Clock screens (analog/digital) created");
    Serial.println("[SETUP]   - Sensor display screens created");
    Serial.println("[SETUP]   - Settings screen created");
    
    // Configure time (NTP requires WiFi connection)
    Serial.println("\n[TIME] Configuring time system...");
    Serial.println("[TIME] Note: NTP requires WiFi connection");
    Serial.println("[TIME] To enable time sync, uncomment WiFi code in setup()");
    
    
    #include <WiFi.h>
    const char* ssid = "YOUR_SSID";
    const char* password = "YOUR_PASSWORD";
    
    Serial.print("[TIME] Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int wifiRetries = 0;
    while (WiFi.status() != WL_CONNECTED && wifiRetries < 20) {
        delay(500);
        Serial.print(".");
        wifiRetries++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[TIME] WiFi connected!");
        Serial.print("[TIME] IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n[TIME] WiFi connection failed");
    }
    
    
    // Configure NTP (only works if WiFi is connected)
    setManualTime();
    // configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    // setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);  // America/Toronto
    setenv("TZ", "HKT-8", 1);       // HK Time is GMT+8
    tzset();
    Serial.println("[TIME] NTP servers configured");
    Serial.println("[TIME] Timezone: EST5EDT (Eastern Time)");
    
    // Wait for time to be set
    time_t now = time(nullptr);
    int retries = 0;
    Serial.print("[TIME] Waiting for time sync");
    while (now < 1000000000 && retries < 10) {
        delay(1000);
        now = time(nullptr);
        retries++;
        Serial.print(".");
    }
    Serial.println();
    
    if (now >= 1000000000) {
        struct tm *timeinfo = localtime(&now);
        Serial.print("[TIME] Time synchronized: ");
        Serial.print(timeinfo->tm_hour);
        Serial.print(":");
        Serial.print(timeinfo->tm_min);
        Serial.print(":");
        Serial.println(timeinfo->tm_sec);
    } else {
        Serial.println("[TIME] Warning: Time not synchronized (WiFi not connected)");
        Serial.println("[TIME] Clock will show 00:00:00 until WiFi is connected");
    }
    
    Serial.println("\n========================================");
    Serial.println("Setup Complete - Entering Main Loop");
    Serial.println("========================================\n");
    Serial.println("[LOOP] System ready - monitoring sensors...");
    Serial.println("[LOOP] Sensor read interval: 10ms (100 Hz)");
    Serial.println("[LOOP] Clock update interval: 1000ms (1 Hz)");
    Serial.println("[LOOP] Temperature read interval: 5000ms (0.2 Hz)");
    Serial.println();
}

void loop() {
    // Handle LVGL tasks
    lv_timer_handler();
    
    // Update sensors
    unsigned long currentMillis = millis();
    if (currentMillis - lastSensorRead >= SENSOR_READ_INTERVAL) {
        updateSensors();
        lastSensorRead = currentMillis;
    }
    
    // Update clock
    if (currentMillis - lastClockUpdate >= CLOCK_UPDATE_INTERVAL) {
        static bool firstClockUpdate = true;
        if (firstClockUpdate) {
            Serial.println("[CLOCK] Starting clock updates (1 Hz)");
            firstClockUpdate = false;
        }
        uiManager.updateClock();
        lastClockUpdate = currentMillis;
    }
    
    // Read temperature periodically
    if (currentMillis - lastTempRead >= TEMP_READ_INTERVAL) {
        Serial.print("[TEMP] Reading temperature... ");
        unsigned long tempStartTime = millis();
        currentTemperature = max30102.readTemperature();
        unsigned long tempReadTime = millis() - tempStartTime;
        
        Serial.print(currentTemperature, 2);
        Serial.print("°C (read time: ");
        Serial.print(tempReadTime);
        Serial.println("ms)");
        
        uiManager.updateTemperature(currentTemperature);
        lastTempRead = currentMillis;
    }
    
    // Update UI with sensor data
    uiManager.updateHeartRate(currentHeartRate);
    uiManager.updateSpO2(currentSpO2);
    
    // Handle UI events
    handleUIEvents();
    
    delay(5);
}

void setupLVGL() {
    Serial.print("[LVGL] Initializing LVGL core... ");
    // Initialize LVGL
    lv_init();
    Serial.println("OK");
    
    // Allocate display buffers
    size_t buffer_size = DISPLAY_WIDTH * DISPLAY_HEIGHT / 10;
    Serial.print("[LVGL] Allocating display buffers... ");
    Serial.print("Buffer size: ");
    Serial.print(buffer_size);
    Serial.print(" pixels (");
    Serial.print(buffer_size * sizeof(lv_color_t));
    Serial.println(" bytes per buffer)");
    
    buf1 = (lv_color_t*)heap_caps_malloc(buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    buf2 = (lv_color_t*)heap_caps_malloc(buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    
    if (!buf1 || !buf2) {
        Serial.println("[ERROR] Failed to allocate display buffers!");
        Serial.println("[ERROR] Insufficient DMA-capable memory");
        Serial.print("[ERROR] Required: ");
        Serial.print(buffer_size * sizeof(lv_color_t) * 2);
        Serial.println(" bytes");
        while(1) delay(1000);
    }
    Serial.println("[LVGL] Buffers allocated successfully (DMA-capable memory)");
    
    // Create display
    Serial.print("[LVGL] Creating display object (");
    Serial.print(DISPLAY_WIDTH);
    Serial.print("x");
    Serial.print(DISPLAY_HEIGHT);
    Serial.print(")... ");
    display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_display_set_flush_cb(display, display_flush);
    lv_display_set_buffers(display, buf1, buf2, buffer_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
    Serial.println("OK");
    
    // Create input device (touch)
    Serial.print("[LVGL] Creating input device (touch)... ");
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchpad_read);
    Serial.println("OK");
    
    Serial.println("[LVGL] LVGL initialized successfully");
    Serial.println("[LVGL]   - Rendering mode: Partial (only updates changed areas)");
    Serial.println("[LVGL]   - Double buffering: Enabled");
    Serial.println("[LVGL]   - Touch input: Configured");
}

void updateSensors() {
    static uint32_t sampleCount = 0;
    static unsigned long lastLogTime = 0;
    static uint32_t fifoErrorCount = 0;
    
    uint32_t red, ir;
    
    if (max30102.readFIFO(&red, &ir)) {
        sampleCount++;
        
        // Add samples to algorithms
        hrAlgorithm.addSample(ir);
        spo2Algorithm.addSample(red, ir);
        
        // Get calculated values
        uint8_t prevHR = currentHeartRate;
        uint8_t prevSpO2 = currentSpO2;
        
        if (hrAlgorithm.isDataReady()) {
            currentHeartRate = hrAlgorithm.getHeartRate();
        }
        
        if (spo2Algorithm.isDataReady()) {
            currentSpO2 = spo2Algorithm.getSpO2();
        }
        
        // Log detailed sensor data every 100 samples (1 second at 100Hz)
        if (sampleCount % 100 == 0) {
            unsigned long currentTime = millis();
            Serial.print("[SENSOR] Sample #");
            Serial.print(sampleCount);
            Serial.print(" | Red: ");
            Serial.print(red);
            Serial.print(" | IR: ");
            Serial.print(ir);
            
            if (hrAlgorithm.isDataReady()) {
                Serial.print(" | HR: ");
                if (currentHeartRate > 0) {
                    Serial.print(currentHeartRate);
                    Serial.print(" BPM");
                } else {
                    Serial.print("-- (calculating...)");
                }
            } else {
                Serial.print(" | HR: -- (buffering...)");
            }
            
            if (spo2Algorithm.isDataReady()) {
                Serial.print(" | SpO2: ");
                if (currentSpO2 > 0) {
                    Serial.print(currentSpO2);
                    Serial.print("%");
                } else {
                    Serial.print("-- (calculating...)");
                }
            } else {
                Serial.print(" | SpO2: -- (buffering...)");
            }
            
            // Check for value changes
            if (prevHR != currentHeartRate && currentHeartRate > 0) {
                Serial.print(" | HR CHANGED: ");
                Serial.print(prevHR);
                Serial.print(" -> ");
                Serial.print(currentHeartRate);
            }
            
            if (prevSpO2 != currentSpO2 && currentSpO2 > 0) {
                Serial.print(" | SpO2 CHANGED: ");
                Serial.print(prevSpO2);
                Serial.print(" -> ");
                Serial.print(currentSpO2);
            }
            
            // Check FIFO status
            uint8_t writePtr = max30102.getWritePointer();
            uint8_t readPtr = max30102.getReadPointer();
            uint8_t ovfCount = max30102.getOVFCounter();
            
            Serial.print(" | FIFO: W=");
            Serial.print(writePtr);
            Serial.print(" R=");
            Serial.print(readPtr);
            Serial.print(" OVF=");
            Serial.print(ovfCount);
            
            if (ovfCount > 0) {
                Serial.print(" [WARNING: FIFO overflow detected!]");
            }
            
            Serial.println();
            
            // Performance metrics
            if (lastLogTime > 0) {
                unsigned long elapsed = currentTime - lastLogTime;
                float actualRate = 1000.0 / elapsed * 100.0;  // samples per second
                Serial.print("[PERF] Actual sample rate: ");
                Serial.print(actualRate);
                Serial.print(" Hz (target: 100 Hz)");
                if (actualRate < 90) {
                    Serial.print(" [WARNING: Sample rate too low!]");
                }
                Serial.println();
            }
            lastLogTime = currentTime;
        }
        
        // Log raw values every 1000 samples (10 seconds) for debugging
        if (sampleCount % 1000 == 0) {
            Serial.print("[DEBUG] Raw values - Red: ");
            Serial.print(red);
            Serial.print(" (0x");
            Serial.print(red, HEX);
            Serial.print("), IR: ");
            Serial.print(ir);
            Serial.print(" (0x");
            Serial.print(ir, HEX);
            Serial.println(")");
        }
    } else {
        fifoErrorCount++;
        if (fifoErrorCount % 10 == 0) {
            Serial.print("[ERROR] Failed to read FIFO (error count: ");
            Serial.print(fifoErrorCount);
            Serial.println(")");
            Serial.println("[ERROR] Check I2C connection and MAX30102 power");
        }
    }
}

void handleUIEvents() {
    // This function can be expanded to handle custom UI events
    // For now, event handling is done through LVGL callbacks
}

// LVGL tick function (call this from a timer interrupt for better performance)
void lv_tick() {
    lv_tick_inc(5);  // 5ms tick
}
