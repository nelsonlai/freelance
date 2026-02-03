# Serial Logging System Documentation

## Overview

The codebase includes comprehensive serial logging throughout all components to help users understand code execution and facilitate debugging. All logs use a consistent format with component tags in square brackets.

## Log Format

All log messages follow this format:
```
[COMPONENT] Message details
```

### Component Tags

- `[SETUP]` - System initialization
- `[MAX30102]` - MAX30102 sensor operations
- `[DISPLAY]` - Display/TFT operations
- `[LVGL]` - LVGL graphics library
- `[UI]` - User interface updates
- `[SENSOR]` - Sensor data readings
- `[HR_ALGORITHM]` - Heart rate calculation
- `[SPO2_ALGORITHM]` - SpO2 calculation
- `[TEMP]` - Temperature readings
- `[CLOCK]` - Clock updates
- `[TIME]` - Time synchronization
- `[LOOP]` - Main loop information
- `[PERF]` - Performance metrics
- `[ERROR]` - Error conditions
- `[DEBUG]` - Debug information

## Logging Levels

### 1. Startup/Initialization Logs

**Frequency:** Once during setup

**Examples:**
```
[SETUP] Step 1/6: Initializing Serial Communication
[SETUP] Serial baud rate: 115200 - OK
[MAX30102] Device detected, initializing...
[DISPLAY] Initializing SPI... OK
[LVGL] Initializing LVGL core... OK
```

### 2. Runtime Status Logs

**Frequency:** Periodic (every 1-10 seconds)

**Examples:**
```
[SENSOR] Sample #100 | Red: 12345 | IR: 23456 | HR: 72 BPM | SpO2: 98%
[PERF] Actual sample rate: 99.5 Hz (target: 100 Hz)
```

### 3. Event-Based Logs

**Frequency:** When events occur

**Examples:**
```
[UI] Screen change: Main Menu -> Heart Rate
[HR_ALGORITHM] Peak detected #5 | Interval: 60 samples (600ms)
[UI] Heart rate updated: 72 BPM
```

### 4. Error/Warning Logs

**Frequency:** When errors occur

**Examples:**
```
[ERROR] MAX30102 not found on I2C bus!
[ERROR] Failed to read FIFO (error count: 10)
[WARNING] FIFO overflow detected!
```

## Detailed Log Categories

### Setup Phase Logs

**Location:** `MAX30102_HealthMonitor.ino` - `setup()`

**What's Logged:**
- Serial communication initialization
- I2C bus setup with pin numbers
- MAX30102 detection and configuration
- Display initialization steps
- LVGL setup (buffers, display object)
- UI screen creation
- Time synchronization status

**Example Output:**
```
========================================
MAX30102 Health Monitor - Starting Up
========================================

[SETUP] Step 1/6: Initializing Serial Communication
[SETUP] Serial baud rate: 115200 - OK
[SETUP] Step 2/6: Initializing I2C Bus
[SETUP] I2C SDA pin: GPIO 21, SCL pin: GPIO 22 - OK
[SETUP] Step 3/6: Initializing MAX30102 Sensor
[MAX30102] Device detected, initializing...
[MAX30102] Resetting device... OK
[MAX30102] Configuring registers...
[MAX30102]   FIFO Config (0x4F): OK - Sample averaging=4, Rollover enabled
...
```

### Sensor Reading Logs

**Location:** `MAX30102_HealthMonitor.ino` - `updateSensors()`

**What's Logged:**
- Every 100 samples (1 second):
  - Sample count
  - Raw Red and IR values
  - Current heart rate (if available)
  - Current SpO2 (if available)
  - Value changes
  - FIFO status (write/read pointers, overflow count)
  - Performance metrics (actual sample rate)

**Example Output:**
```
[SENSOR] Sample #100 | Red: 12345 | IR: 23456 | HR: 72 BPM | SpO2: 98% | FIFO: W=15 R=10 OVF=0
[PERF] Actual sample rate: 99.5 Hz (target: 100 Hz)
[SENSOR] Sample #200 | Red: 12400 | IR: 23500 | HR: 73 BPM | HR CHANGED: 72 -> 73 | SpO2: 98% | FIFO: W=20 R=15 OVF=0
```

### Algorithm Logs

**Heart Rate Algorithm:**
- Buffer ready notification
- Peak detection (every 5th peak)
- Heart rate calculation with details
- Warnings for invalid values

**SpO2 Algorithm:**
- Buffer ready notification
- SpO2 calculation with ratio and AC/DC components
- Warnings for invalid ratios

**Example Output:**
```
[HR_ALGORITHM] Buffer filled - Heart rate calculation ready
[HR_ALGORITHM] Peak detected #5 | Interval: 60 samples (600ms)
[HR_ALGORITHM] Heart rate calculated: 72 BPM (from 5 intervals, avg: 60.0 samples)

[SPO2_ALGORITHM] Buffer filled - SpO2 calculation ready
[SPO2_ALGORITHM] SpO2 calculated: 98% | Ratio: 0.480 | Red AC/DC: 0.0123 | IR AC/DC: 0.0256
```

### UI Logs

**Location:** `ui_manager.cpp`

**What's Logged:**
- Screen creation during initialization
- Screen navigation (from -> to)
- Value updates (temperature, heart rate, SpO2)
- Only logs when values change significantly

**Example Output:**
```
[UI] Creating user interface screens...
[UI]   Creating main screen... OK
[UI]   Creating analog clock screen... OK
...
[UI] Screen change: Main Menu -> Heart Rate
[UI] Heart rate updated: 72 BPM
[UI] Temperature updated: 25.3°C
```

### Display Logs

**Location:** `display_driver.cpp`

**What's Logged:**
- Initialization steps
- Brightness changes
- Flush statistics (every 100 flushes or 5 seconds):
  - Flush count
  - Average pixels per flush
  - Flush time
  - Estimated FPS

**Example Output:**
```
[DISPLAY] Initializing SPI... OK
[DISPLAY] Initializing TFT_eSPI display... OK
[DISPLAY] Configuring display... OK
[DISPLAY]   Rotation: Portrait (0) | Color format: RGB565 with byte swap
[DISPLAY] Brightness changed: 80% -> 90% (PWM: 230)
[DISPLAY] Flush stats: Count=100 | Avg pixels/flush=7680 | Last flush time=5.23ms | Est. FPS=58.2
```

### MAX30102 Driver Logs

**Location:** `MAX30102_Driver.cpp`

**What's Logged:**
- Device detection
- Reset operation
- Register configuration details
- Temperature readings (when significantly different)
- FIFO read errors

**Example Output:**
```
[MAX30102] Device detected, initializing...
[MAX30102] Resetting device... OK
[MAX30102] Configuring registers...
[MAX30102]   FIFO Config (0x4F): OK - Sample averaging=4, Rollover enabled
[MAX30102]   Mode Config (SpO2): OK - SpO2 mode (Red + IR LEDs)
[MAX30102]   SpO2 Config: OK - Sample rate=100Hz, Pulse width=411μs, ADC range=4096nA (0x57)
[MAX30102] Temperature: 25 + 5/16 = 25.313°C
```

## Performance Monitoring

The logging system includes performance metrics:

1. **Sample Rate Monitoring:**
   - Logs actual sample rate vs target (100 Hz)
   - Warns if rate drops below 90 Hz

2. **Display Performance:**
   - Tracks flush times
   - Calculates estimated FPS
   - Monitors average pixels per flush

3. **FIFO Status:**
   - Tracks write/read pointers
   - Monitors overflow counter
   - Warns on data loss

## Error Handling

All error conditions are logged with detailed information:

1. **Device Not Found:**
   - Lists possible causes
   - Provides troubleshooting steps

2. **FIFO Read Errors:**
   - Counts consecutive errors
   - Logs every 10th error to avoid spam

3. **Invalid Calculations:**
   - Heart rate out of range (40-200 BPM)
   - SpO2 invalid ratio
   - Provides context for debugging

## Debugging Tips

### 1. Understanding Startup Issues

If the system doesn't start:
- Check for `[ERROR]` messages
- Verify all `[SETUP]` steps complete
- Look for device detection failures

### 2. Sensor Reading Problems

If no sensor data:
- Check `[SENSOR]` logs for sample counts
- Verify FIFO pointers are incrementing
- Look for `[ERROR]` messages about FIFO reads
- Check if algorithms show "buffering..." status

### 3. Algorithm Issues

If heart rate/SpO2 not calculating:
- Check `[HR_ALGORITHM]` or `[SPO2_ALGORITHM]` buffer status
- Verify peak detection is occurring
- Check for warnings about invalid values
- Ensure finger is properly placed on sensor

### 4. Display Problems

If display not working:
- Check `[DISPLAY]` initialization logs
- Verify flush statistics show activity
- Check for SPI communication errors

### 5. Performance Issues

If system is slow:
- Check `[PERF]` logs for sample rate
- Monitor `[DISPLAY]` flush times
- Look for FIFO overflow warnings

## Log Filtering

To reduce log volume, you can:

1. **Comment out verbose logs** in source files
2. **Increase logging intervals** (change modulo values)
3. **Disable specific component logs** by removing Serial.println() calls

## Example: Typical Startup Sequence

```
========================================
MAX30102 Health Monitor - Starting Up
========================================

[SETUP] Step 1/6: Initializing Serial Communication
[SETUP] Serial baud rate: 115200 - OK
[SETUP] Step 2/6: Initializing I2C Bus
[SETUP] I2C SDA pin: GPIO 21, SCL pin: GPIO 22 - OK
[SETUP] Step 3/6: Initializing MAX30102 Sensor
[SETUP] Checking device at I2C address 0xAE... OK
[MAX30102] Device detected, initializing...
[MAX30102] Resetting device... OK
[MAX30102] Configuring registers...
...
[SETUP] MAX30102 initialized successfully
[SETUP] Step 4/6: Initializing Display
[DISPLAY] Initializing SPI... OK
...
[SETUP] Display initialized successfully
[SETUP] Step 5/6: Initializing LVGL Graphics Library
[LVGL] Initializing LVGL core... OK
...
[SETUP] Step 6/6: Creating User Interface
[UI] Creating user interface screens...
...
========================================
Setup Complete - Entering Main Loop
========================================

[LOOP] System ready - monitoring sensors...
```

## Example: Typical Runtime Output

```
[SENSOR] Sample #100 | Red: 12345 | IR: 23456 | HR: -- (buffering...) | SpO2: -- (buffering...) | FIFO: W=15 R=10 OVF=0
[PERF] Actual sample rate: 99.8 Hz (target: 100 Hz)
[HR_ALGORITHM] Buffer filled - Heart rate calculation ready
[SPO2_ALGORITHM] Buffer filled - SpO2 calculation ready
[SENSOR] Sample #200 | Red: 12400 | IR: 23500 | HR: 72 BPM | SpO2: 98% | FIFO: W=20 R=15 OVF=0
[HR_ALGORITHM] Peak detected #5 | Interval: 60 samples (600ms)
[HR_ALGORITHM] Heart rate calculated: 72 BPM (from 5 intervals, avg: 60.0 samples)
[UI] Heart rate updated: 72 BPM
[SPO2_ALGORITHM] SpO2 calculated: 98% | Ratio: 0.480 | Red AC/DC: 0.0123 | IR AC/DC: 0.0256
[UI] SpO2 updated: 98%
[TEMP] Reading temperature... 25.3°C (read time: 102ms)
[UI] Temperature updated: 25.3°C
[CLOCK] Starting clock updates (1 Hz)
```

This comprehensive logging system provides full visibility into system operation, making debugging and understanding the code execution much easier.
