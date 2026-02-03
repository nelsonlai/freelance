# Code Execution Flow - Detailed Technical Documentation

This document provides a comprehensive explanation of how the MAX30102 Health Monitor code executes from startup to runtime, covering every component and detail.

## Table of Contents

1. [System Startup Sequence](#system-startup-sequence)
2. [Component Initialization](#component-initialization)
3. [Main Loop Execution](#main-loop-execution)
4. [Sensor Reading Process](#sensor-reading-process)
5. [Algorithm Processing](#algorithm-processing)
6. [UI Update Mechanisms](#ui-update-mechanisms)
7. [Event Handling System](#event-handling-system)
8. [Memory Management](#memory-management)
9. [Timing and Scheduling](#timing-and-scheduling)
10. [Data Flow Diagrams](#data-flow-diagrams)

---

## System Startup Sequence

### 1. Arduino Framework Initialization

When the ESP32 powers on or resets, the Arduino framework performs the following in order:

```
Power On/Reset
    ↓
ESP32 Bootloader
    ↓
Arduino Core Initialization
    ↓
Global Variable Initialization
    ↓
setup() Function Execution
```

**Global Objects Created (Before setup()):**
- `MAX30102 max30102` - Sensor driver instance
- `HeartRateAlgorithm hrAlgorithm` - HR calculation algorithm
- `SpO2Algorithm spo2Algorithm` - SpO2 calculation algorithm
- `DisplayDriver displayDriver` - Display controller
- `UIManager uiManager` - UI management system

**Static Variables Initialized:**
- `lv_display_t *display` - LVGL display object (null initially)
- `lv_color_t *buf1, *buf2` - Display buffers (null initially)
- Timing variables: `lastSensorRead`, `lastClockUpdate`, `lastTempRead` (all 0)
- Sensor data: `currentTemperature`, `currentHeartRate`, `currentSpO2` (all 0)

---

## Component Initialization

### 2. setup() Function - Step by Step

#### 2.1 Serial Communication Setup
```cpp
Serial.begin(115200);
delay(1000);
```
**What happens:**
- Initializes UART0 at 115200 baud
- Waits 1 second for serial monitor connection
- Enables debug output to Serial Monitor

**Timing:** ~1 second

---

#### 2.2 I2C Bus Initialization
```cpp
Wire.begin(I2C_SDA, I2C_SCL);
```
**What happens:**
- Initializes I2C peripheral on ESP32
- Configures GPIO 21 (SDA) and GPIO 22 (SCL) for I2C
- Sets I2C clock speed (default: 100kHz)
- Prepares bus for MAX30102 communication

**Hardware:** I2C bus ready for device communication

---

#### 2.3 MAX30102 Sensor Initialization

**Step 2.3.1: begin() Method**
```cpp
max30102.begin(Wire)
```

**Internal Process:**
1. **Store I2C reference:**
   ```cpp
   _wire = &wire;  // Store Wire instance reference
   ```

2. **Initialize I2C (if not already):**
   ```cpp
   _wire->begin();  // Ensure I2C is started
   ```

3. **Check Device Connection:**
   ```cpp
   isConnected()
   ```
   - Sends I2C START condition
   - Transmits device address (0xAE)
   - Checks for ACK response
   - Returns `true` if device responds, `false` otherwise

4. **Reset Device:**
   ```cpp
   reset()
   ```
   - Writes `MODE_RESET` (0x40) to `REG_MODE_CONFIG` (0x09)
   - Waits 100ms for reset to complete
   - Device enters known state

5. **Configure Device:**
   ```cpp
   setup()
   ```
   - **FIFO Configuration (0x08):**
     - Value: `0x4F`
     - Bits: `0100 1111`
     - Sample averaging: 4 samples
     - FIFO rollover: Enabled
     - FIFO almost full: 17 samples
   
   - **Mode Configuration (0x09):**
     - Value: `MODE_SPO2` (0x03)
     - Enables both Red and IR LEDs
     - Sets SpO2 measurement mode
   
   - **SpO2 Configuration (0x0A):**
     - Value: `SPO2_SR_100 | LED_PW_411 | SPO2_ADC_RGE_4096`
     - Sample rate: 100 Hz
     - LED pulse width: 411 μs
     - ADC range: 4096 nA
   
   - **LED Current (0x0C, 0x0D):**
     - Red LED: `0x1F` (6.4mA)
     - IR LED: `0x1F` (6.4mA)
   
   - **Clear FIFO:**
     - Resets FIFO write pointer to 0
     - Resets FIFO read pointer to 0
     - Resets overflow counter to 0

**Timing:** ~200ms total
**Result:** MAX30102 ready to collect data

---

#### 2.4 Display Initialization

**Step 2.4.1: displayDriver.init()**

**Internal Process:**
1. **SPI Initialization:**
   ```cpp
   SPI.begin();
   ```
   - Initializes SPI peripheral
   - Configures pins (MOSI, SCLK, CS, DC, RST from `display_config.h`)
   - Sets SPI mode and speed

2. **TFT_eSPI Initialization:**
   ```cpp
   tft.init();
   ```
   - Sends initialization sequence to display controller
   - Configures display parameters (from User_Setup.h)
   - Sets display to active state

3. **Display Configuration:**
   ```cpp
   tft.setRotation(0);  // Portrait mode
   tft.fillScreen(TFT_BLACK);  // Clear screen
   tft.setSwapBytes(true);  // LVGL color format
   ```
   - Sets display orientation
   - Clears screen to black
   - Configures byte swapping for LVGL's RGB565 format

4. **Backlight Setup:**
   ```cpp
   pinMode(DISPLAY_BL, OUTPUT);
   setBrightness(80);  // 80% brightness
   ```
   - Configures backlight pin as output
   - Sets PWM duty cycle: `map(80, 0, 100, 0, 255) = 204`

**Timing:** ~100-200ms
**Result:** Display ready, showing black screen

---

#### 2.5 LVGL Graphics Library Setup

**Step 2.5.1: setupLVGL() Function**

**Process:**
1. **Initialize LVGL Core:**
   ```cpp
   lv_init();
   ```
   - Initializes LVGL internal structures
   - Sets up memory management
   - Prepares graphics rendering system

2. **Allocate Display Buffers:**
   ```cpp
   buffer_size = DISPLAY_WIDTH * DISPLAY_HEIGHT / 10;
   // For 320x240: 320 * 240 / 10 = 7680 pixels
   
   buf1 = heap_caps_malloc(buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
   buf2 = heap_caps_malloc(buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
   ```
   - Calculates buffer size (10% of screen)
   - Allocates from DMA-capable memory (faster SPI transfers)
   - Creates double buffer for smooth rendering
   - Each buffer: 7680 * 2 bytes = 15,360 bytes

3. **Create LVGL Display Object:**
   ```cpp
   display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
   ```
   - Creates display object (320x240)
   - Sets up internal display structures

4. **Configure Display Callbacks:**
   ```cpp
   lv_display_set_flush_cb(display, display_flush);
   ```
   - Registers flush callback function
   - LVGL calls this when screen area needs updating

5. **Set Display Buffers:**
   ```cpp
   lv_display_set_buffers(display, buf1, buf2, buffer_size, 
                          LV_DISPLAY_RENDER_MODE_PARTIAL);
   ```
   - Assigns buffers to display
   - Sets partial rendering mode (only updates changed areas)
   - Enables double buffering

6. **Create Input Device:**
   ```cpp
   lv_indev_t *indev = lv_indev_create();
   lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
   lv_indev_set_read_cb(indev, touchpad_read);
   ```
   - Creates touch input device
   - Sets type to pointer (touch/mouse)
   - Registers touch read callback

**Memory Usage:**
- Buffer 1: 15,360 bytes
- Buffer 2: 15,360 bytes
- LVGL internal: ~50-100 KB
- **Total:** ~80-130 KB

**Timing:** ~50-100ms
**Result:** LVGL ready to render graphics

---

#### 2.6 UI System Initialization

**Step 2.6.1: uiManager.init()**

**Process:**
1. **Set Static Instance:**
   ```cpp
   UIManager::_instance = this;
   ```
   - Stores instance pointer for static callbacks

2. **Create All Screens:**
   ```cpp
   createMainScreen();
   createClockAnalogScreen();
   createClockDigitalScreen();
   createTemperatureScreen();
   createHeartRateScreen();
   createSpO2Screen();
   createSettingsScreen();
   ```
   
   **Each screen creation:**
   - Creates LVGL screen object (`lv_obj_create(NULL)`)
   - Sets background color
   - Creates UI widgets (buttons, labels, etc.)
   - Registers event callbacks
   - Positions elements

3. **Load Main Screen:**
   ```cpp
   lv_scr_load(_mainScreen);
   _currentScreen = SCREEN_MAIN;
   ```
   - Makes main screen active
   - LVGL renders screen to display buffer
   - Display flush callback sends data to TFT

**Screen Structure Created:**
- **Main Screen:** 6 buttons (Clock, Temperature, HR, SpO2, Settings, Back)
- **Analog Clock:** Clock face with hands, markers, switch button
- **Digital Clock:** Time label, date label, switch button
- **Temperature:** Title, value label
- **Heart Rate:** Title, value label, instruction
- **SpO2:** Title, value label, instruction
- **Settings:** Brightness slider, format switch, unit switch

**Timing:** ~200-500ms (depends on screen complexity)
**Result:** UI visible on display, main menu shown

---

#### 2.7 Time Configuration

**Step 2.7.1: NTP Time Setup**
```cpp
configTime(0, 0, "pool.ntp.org", "time.nist.gov");
setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);
tzset();
```

**Process:**
1. **Configure NTP:**
   - Sets timezone offset (0 = UTC)
   - Sets DST offset (0 = no DST)
   - Sets NTP server addresses
   - **Note:** Requires WiFi connection (commented out by default)

2. **Set Timezone:**
   - Configures timezone string
   - Format: `EST5EDT,M3.2.0,M11.1.0`
   - EST = Eastern Standard Time
   - 5 = UTC-5 offset
   - EDT = Eastern Daylight Time
   - M3.2.0 = DST starts 2nd Sunday of March
   - M11.1.0 = DST ends 1st Sunday of November

3. **Wait for Time Sync:**
   ```cpp
   time_t now = time(nullptr);
   int retries = 0;
   while (now < 1000000000 && retries < 10) {
       delay(1000);
       now = time(nullptr);
       retries++;
   }
   ```
   - Checks if time is valid (> year 2001)
   - Retries up to 10 times
   - If WiFi not connected, time remains invalid

**Timing:** 0-10 seconds (depends on WiFi/NTP)
**Result:** System time configured (or invalid if no WiFi)

---

#### 2.8 Setup Complete

**Final State:**
- ✅ Serial communication active
- ✅ I2C bus initialized
- ✅ MAX30102 configured and ready
- ✅ Display initialized and showing UI
- ✅ LVGL rendering system active
- ✅ All UI screens created
- ✅ Main menu displayed
- ⚠️ Time may be invalid (if WiFi not connected)

**Total Setup Time:** ~1-2 seconds

---

## Main Loop Execution

### 3. loop() Function - Continuous Execution

The `loop()` function runs continuously after `setup()` completes. It executes approximately every 5ms (due to `delay(5)` at the end).

#### 3.1 LVGL Task Handler
```cpp
lv_timer_handler();
```

**What happens:**
1. **Process LVGL Internal Tasks:**
   - Handles animations
   - Processes input events
   - Updates dirty regions
   - Renders changed screen areas
   - Calls flush callback for updated regions

2. **Event Processing:**
   - Checks for button clicks
   - Processes touch input
   - Handles widget interactions
   - Executes registered callbacks

3. **Rendering:**
   - Marks changed screen areas as "dirty"
   - Renders dirty regions to display buffers
   - Calls `display_flush()` for each dirty region

**Execution Time:** ~1-5ms (depends on UI activity)
**Frequency:** Every loop iteration (~200 times/second)

---

#### 3.2 Sensor Reading (10ms Interval)

```cpp
if (currentMillis - lastSensorRead >= SENSOR_READ_INTERVAL) {
    updateSensors();
    lastSensorRead = currentMillis;
}
```

**Condition Check:**
- Compares elapsed time since last read
- `SENSOR_READ_INTERVAL = 10ms` (100 Hz sampling rate)
- Executes when 10ms have passed

**updateSensors() Function:**

**Step 3.2.1: Read FIFO Data**
```cpp
max30102.readFIFO(&red, &ir)
```

**Internal Process:**
1. **Read 6 Bytes from FIFO:**
   ```cpp
   readRegisters(REG_FIFO_DATA, temp, 6);
   ```
   - Reads from register 0x07 (FIFO_DATA)
   - Reads 6 consecutive bytes (3 for red, 3 for IR)
   - I2C transaction: START → Address(0xAE) → 0x07 → REPEAT START → Address(0xAF) → Read 6 bytes → STOP

2. **Parse Data:**
   ```cpp
   *red = ((uint32_t)temp[0] << 16) | ((uint32_t)temp[1] << 8) | temp[2];
   *ir = ((uint32_t)temp[3] << 16) | ((uint32_t)temp[4] << 8) | temp[5];
   ```
   - Red: 24-bit value from bytes 0-2
   - IR: 24-bit value from bytes 3-5
   - Masks to 18 bits: `& 0x03FFFF`

3. **FIFO Pointer Management:**
   - MAX30102 automatically increments read pointer
   - If FIFO full, new data overwrites oldest
   - Overflow counter tracks lost samples

**Step 3.2.2: Process Heart Rate**
```cpp
hrAlgorithm.addSample(ir);
```

**Internal Process:**
1. **Add Sample to Buffer:**
   ```cpp
   _buffer[_bufferIndex] = irValue;
   _bufferIndex = (_bufferIndex + 1) % HR_ALGORITHM_BUFFER_SIZE;
   ```
   - Stores IR value in circular buffer (100 samples)
   - Updates buffer index (wraps at 100)

2. **Check Data Ready:**
   ```cpp
   if (!_dataReady && _bufferIndex == 0) {
       _dataReady = true;  // Buffer filled once
   }
   ```
   - Marks data ready after first full buffer cycle

3. **Peak Detection:**
   ```cpp
   if (detectPeak(_buffer[currIdx], _buffer[prevIdx], _buffer[nextIdx])) {
       // Record peak interval
   }
   ```
   - Compares current sample with neighbors
   - Checks if value > average * 1.1
   - Records time between peaks

4. **Calculate Heart Rate:**
   ```cpp
   if (hrAlgorithm.isDataReady()) {
       currentHeartRate = hrAlgorithm.getHeartRate();
   }
   ```
   - Averages peak intervals
   - Converts to BPM: `6000 / avgInterval` (100 Hz = 6000 samples/min)
   - Validates range (40-200 BPM)

**Step 3.2.3: Process SpO2**
```cpp
spo2Algorithm.addSample(red, ir);
```

**Internal Process:**
1. **Store Samples:**
   ```cpp
   _redBuffer[_bufferIndex] = red;
   _irBuffer[_bufferIndex] = ir;
   _bufferIndex = (_bufferIndex + 1) % SPO2_BUFFER_SIZE;
   ```
   - Stores red and IR in separate buffers (100 samples each)

2. **Calculate AC/DC Components:**
   ```cpp
   float redAC = calculateACComponent(_redBuffer);
   float redDC = calculateDCComponent(_redBuffer);
   float irAC = calculateACComponent(_irBuffer);
   float irDC = calculateDCComponent(_irBuffer);
   ```
   - **DC Component:** Mean value of buffer
   - **AC Component:** Standard deviation (RMS of differences from mean)

3. **Calculate Ratio:**
   ```cpp
   float ratio = (redAC / redDC) / (irAC / irDC);
   ```
   - Normalizes AC by DC for both channels
   - Divides red ratio by IR ratio

4. **Calculate SpO2:**
   ```cpp
   float spo2 = 110.0 - 25.0 * ratio;
   ```
   - Uses empirical formula
   - Clamps to 0-100% range

**Execution Time:** ~2-5ms
**Frequency:** 100 Hz (every 10ms)
**Data Rate:** 100 samples/second for each algorithm

---

#### 3.3 Clock Update (1 Second Interval)

```cpp
if (currentMillis - lastClockUpdate >= CLOCK_UPDATE_INTERVAL) {
    uiManager.updateClock();
    lastClockUpdate = currentMillis;
}
```

**updateClock() Function:**

**For Analog Clock:**
1. **Get Current Time:**
   ```cpp
   time_t now = time(NULL);
   struct tm *timeinfo = localtime(&now);
   ```
   - Gets Unix timestamp
   - Converts to local time structure

2. **Calculate Hand Angles:**
   ```cpp
   float hourAngle = (hour * 30.0 + minute * 0.5 - 90.0) * PI / 180.0;
   float minuteAngle = (minute * 6.0 - 90.0) * PI / 180.0;
   float secondAngle = (second * 6.0 - 90.0) * PI / 180.0;
   ```
   - Hour: 30° per hour + 0.5° per minute
   - Minute: 6° per minute
   - Second: 6° per second
   - Subtract 90° (12 o'clock = 0° in math, but top of screen = -90°)

3. **Update Hand Positions:**
   ```cpp
   lv_obj_set_style_transform_angle(_hourHand, (int16_t)(hourAngle * 57.3 + 90), 0);
   ```
   - Sets rotation angle for each hand
   - LVGL rotates object around pivot point
   - Converts radians to degrees (57.3 = 180/π)

**For Digital Clock:**
```cpp
snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", 
         timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
lv_label_set_text(_digitalClockLabel, timeStr);
```
- Formats time as HH:MM:SS
- Updates label text
- LVGL automatically redraws label

**Execution Time:** ~1-2ms
**Frequency:** 1 Hz (every 1000ms)

---

#### 3.4 Temperature Reading (5 Second Interval)

```cpp
if (currentMillis - lastTempRead >= TEMP_READ_INTERVAL) {
    currentTemperature = max30102.readTemperature();
    uiManager.updateTemperature(currentTemperature);
    lastTempRead = currentMillis;
}
```

**readTemperature() Function:**

1. **Enable Temperature Reading:**
   ```cpp
   writeRegister(REG_TEMP_CONFIG, 0x01);
   delay(100);
   ```
   - Writes to temperature configuration register
   - Waits for conversion (100ms)

2. **Read Temperature Data:**
   ```cpp
   uint8_t tempInt = readRegister(REG_TEMP_DATA);
   uint8_t tempFrac = readRegister(REG_TEMP_FRAC);
   ```
   - Reads integer part (register 0x1F)
   - Reads fractional part (register 0x20)
   - Fractional part: 0.0625°C per LSB

3. **Calculate Temperature:**
   ```cpp
   float temperature = tempInt + (tempFrac * 0.0625);
   ```
   - Combines integer and fractional parts

4. **Update UI:**
   ```cpp
   snprintf(tempStr, sizeof(tempStr), "%.1f °C", temp);
   lv_label_set_text(_tempLabel, tempStr);
   ```
   - Formats as "XX.X °C"
   - Updates label

**Execution Time:** ~100-150ms (includes delay)
**Frequency:** 0.2 Hz (every 5000ms)

---

#### 3.5 UI Data Updates

```cpp
uiManager.updateHeartRate(currentHeartRate);
uiManager.updateSpO2(currentSpO2);
```

**These functions:**
- Check if labels exist
- Format values as strings
- Update label text
- LVGL automatically redraws if screen is active

**Execution Time:** <1ms
**Frequency:** Every loop iteration (~200 Hz)

---

#### 3.6 Event Handling

```cpp
handleUIEvents();
```

**Current Implementation:**
- Placeholder function
- Actual event handling done through LVGL callbacks
- Registered during screen creation

**Future Expansion:**
- Custom event queue
- State machine management
- Advanced navigation logic

---

#### 3.7 Loop Delay

```cpp
delay(5);
```

**Purpose:**
- Prevents CPU from running at 100%
- Allows other tasks to run
- Gives LVGL time to process
- Reduces power consumption

**Effect:**
- Loop runs approximately every 5ms
- Effective loop frequency: ~200 Hz
- Total loop time: ~5-10ms

---

## Sensor Reading Process

### 4. MAX30102 Data Collection

#### 4.1 FIFO Operation

**FIFO Structure:**
- 32 sample pairs (Red + IR)
- Each sample: 3 bytes (18-bit value)
- Total FIFO: 192 bytes
- Auto-incrementing pointers

**Reading Process:**
```
FIFO Write Pointer (MAX30102)
    ↓
New samples added automatically
    ↓
FIFO Read Pointer (Our code)
    ↓
Read 6 bytes (1 sample pair)
    ↓
Pointer auto-increments
```

**Overflow Handling:**
- If FIFO full, new data overwrites oldest
- Overflow counter increments
- Can detect data loss

#### 4.2 I2C Communication Details

**Read FIFO Transaction:**
```
START
  ↓
0xAE (Write Address) + ACK
  ↓
0x07 (FIFO_DATA Register) + ACK
  ↓
REPEAT START
  ↓
0xAF (Read Address) + ACK
  ↓
Read Byte 0 (Red MSB) + ACK
  ↓
Read Byte 1 (Red Middle) + ACK
  ↓
Read Byte 2 (Red LSB) + ACK
  ↓
Read Byte 3 (IR MSB) + ACK
  ↓
Read Byte 4 (IR Middle) + ACK
  ↓
Read Byte 5 (IR LSB) + NACK
  ↓
STOP
```

**Timing:**
- I2C clock: 100kHz (default)
- Transaction time: ~0.6ms
- With overhead: ~1-2ms total

---

## Algorithm Processing

### 5. Heart Rate Algorithm

#### 5.1 Data Flow

```
IR Sample (18-bit value)
    ↓
Circular Buffer (100 samples)
    ↓
Peak Detection Algorithm
    ↓
Peak Intervals Array (10 intervals)
    ↓
Average Interval Calculation
    ↓
BPM = 6000 / avgInterval
    ↓
Validation (40-200 BPM)
    ↓
currentHeartRate
```

#### 5.2 Peak Detection Logic

**Algorithm:**
1. Compare sample with previous and next
2. Check if sample > average * 1.1
3. Ensure minimum distance between peaks (30 samples = 0.3s)
4. Record interval between peaks

**Example:**
```
Buffer: [100, 105, 110, 115, 120, 118, 115, 112, ...]
         ↑                    ↑
      Previous            Current Peak
      
Average: 110
Current: 120
120 > 110 * 1.1 = 121? No, not a peak

Next sample: 125
125 > 110 * 1.1 = 121? Yes, potential peak
Check neighbors: 120 < 125 > 118? Yes, confirmed peak
```

#### 5.3 Heart Rate Calculation

**Formula:**
```
BPM = (6000 samples/min) / (average_interval samples)
```

**Example:**
- Sample rate: 100 Hz
- Average interval: 60 samples
- BPM = 6000 / 60 = 100 BPM

**Validation:**
- Minimum: 40 BPM (150 samples interval)
- Maximum: 200 BPM (30 samples interval)
- Invalid values return 0

---

### 6. SpO2 Algorithm

#### 6.1 Data Flow

```
Red Sample + IR Sample
    ↓
Separate Circular Buffers (100 samples each)
    ↓
Calculate DC Component (Mean)
    ↓
Calculate AC Component (Std Dev)
    ↓
Normalize: AC/DC for each channel
    ↓
Calculate Ratio: (Red AC/DC) / (IR AC/IR)
    ↓
SpO2 = 110 - 25 * ratio
    ↓
Clamp to 0-100%
    ↓
currentSpO2
```

#### 6.2 AC/DC Component Calculation

**DC Component (Mean):**
```cpp
float sum = 0;
for (int i = 0; i < 100; i++) {
    sum += buffer[i];
}
float dc = sum / 100;
```

**AC Component (RMS):**
```cpp
float sumSqDiff = 0;
for (int i = 0; i < 100; i++) {
    float diff = buffer[i] - dc;
    sumSqDiff += diff * diff;
}
float ac = sqrt(sumSqDiff / 100);
```

#### 6.3 SpO2 Formula

**Empirical Formula:**
```
SpO2 = 110 - 25 * R

Where R = (Red_AC/Red_DC) / (IR_AC/IR_DC)
```

**Rationale:**
- Ratio R typically ranges from 0.4 to 1.2
- Higher ratio = lower SpO2 (more red absorption)
- Linear approximation of calibration curve
- **Note:** Real implementations use lookup tables

**Example:**
- Red AC/DC = 0.05
- IR AC/DC = 0.10
- R = 0.05 / 0.10 = 0.5
- SpO2 = 110 - 25 * 0.5 = 97.5%

---

## UI Update Mechanisms

### 7. LVGL Rendering System

#### 7.1 Rendering Pipeline

```
Widget State Change
    ↓
Mark Region as Dirty
    ↓
lv_timer_handler() called
    ↓
Render Dirty Regions to Buffer
    ↓
Call display_flush() callback
    ↓
TFT_eSPI pushColors()
    ↓
SPI Transfer to Display
    ↓
Screen Updated
```

#### 7.2 Partial Rendering

**Why Partial Rendering:**
- Only updates changed areas
- Reduces CPU usage
- Faster updates
- Lower power consumption

**How It Works:**
1. LVGL tracks which screen regions changed
2. Only renders those regions to buffer
3. Flush callback sends only changed areas to display
4. Display controller updates only those pixels

**Example:**
- Clock second hand moves
- Only second hand area marked dirty
- Only that region rendered and sent to display
- Rest of screen unchanged

#### 7.3 Display Flush Process

**display_flush() Callback:**

```cpp
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)px_map, w * h, true);
    tft.endWrite();
    
    lv_display_flush_ready(disp);
}
```

**Step by Step:**
1. **Calculate Region Size:**
   - Width: `x2 - x1 + 1`
   - Height: `y2 - y1 + 1`

2. **Start SPI Transaction:**
   ```cpp
   tft.startWrite();
   ```
   - Locks SPI bus
   - Sets CS low
   - Prepares for data transfer

3. **Set Display Window:**
   ```cpp
   tft.setAddrWindow(area->x1, area->y1, w, h);
   ```
   - Sends command to set column/row addresses
   - Tells display where to write pixels

4. **Send Pixel Data:**
   ```cpp
   tft.pushColors((uint16_t*)px_map, w * h, true);
   ```
   - Sends pixel data via SPI
   - Format: RGB565 (16-bit per pixel)
   - `true` = swap bytes (endianness)

5. **End Transaction:**
   ```cpp
   tft.endWrite();
   ```
   - Sets CS high
   - Releases SPI bus

6. **Notify LVGL:**
   ```cpp
   lv_display_flush_ready(disp);
   ```
   - Tells LVGL flush is complete
   - LVGL can now use buffer for next frame

**Timing:**
- Small region (100x100): ~5-10ms
- Full screen (320x240): ~50-100ms
- Depends on SPI speed and display controller

---

## Event Handling System

### 8. LVGL Event System

#### 8.1 Event Registration

**During Screen Creation:**
```cpp
lv_obj_add_event_cb(clockBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_CLOCK_ANALOG);
```

**Parameters:**
- `clockBtn`: Widget that triggers event
- `mainBtnEventHandler`: Callback function
- `LV_EVENT_CLICKED`: Event type
- `(void*)SCREEN_CLOCK_ANALOG`: User data (screen ID)

#### 8.2 Event Processing Flow

```
User Interaction (Touch/Click)
    ↓
LVGL Input Driver Detects
    ↓
touchpad_read() called
    ↓
LVGL Processes Input
    ↓
Finds Widget Under Touch
    ↓
Checks Event Callbacks
    ↓
Calls Registered Callback
    ↓
mainBtnEventHandler() executes
    ↓
Screen Navigation Occurs
```

#### 8.3 Callback Implementation

**mainBtnEventHandler():**
```cpp
void UIManager::mainBtnEventHandler(lv_event_t *e) {
    if (!_instance) return;
    screen_id_t screen = (screen_id_t)lv_event_get_user_data(e);
    _instance->showScreen(screen);
}
```

**Process:**
1. Check if instance exists (safety check)
2. Extract user data (screen ID)
3. Cast to screen_id_t enum
4. Call showScreen() with target screen

**showScreen():**
```cpp
void UIManager::showScreen(screen_id_t screen) {
    lv_obj_t *targetScreen = getScreenObject(screen);
    if (targetScreen) {
        lv_scr_load(targetScreen);
        _currentScreen = screen;
    }
}
```

**Result:**
- New screen loaded
- LVGL renders new screen
- Display updates
- User sees new screen

---

## Memory Management

### 9. Memory Allocation

#### 9.1 Static Memory

**Global Objects:**
- `MAX30102 max30102`: ~100 bytes
- `HeartRateAlgorithm hrAlgorithm`: ~500 bytes (buffers)
- `SpO2Algorithm spo2Algorithm`: ~1000 bytes (buffers)
- `DisplayDriver displayDriver`: ~50 bytes
- `UIManager uiManager`: ~200 bytes (pointers)

**Total Static:** ~1.8 KB

#### 9.2 Dynamic Memory (Heap)

**LVGL Buffers:**
- `buf1`: 15,360 bytes
- `buf2`: 15,360 bytes
- **Total:** 30,720 bytes (~30 KB)

**LVGL Internal:**
- Widget objects: ~50-100 KB
- Font data: ~10-20 KB
- Style data: ~5-10 KB
- **Total:** ~65-130 KB

**Algorithm Buffers:**
- Heart rate buffer: 400 bytes (100 * 4 bytes)
- SpO2 buffers: 800 bytes (100 * 4 bytes * 2)
- **Total:** 1,200 bytes

**Total Heap Usage:** ~97-162 KB

#### 9.3 ESP32 Memory

**Typical ESP32:**
- Total RAM: 520 KB
- Available for user: ~300-400 KB
- Our usage: ~100-160 KB
- **Remaining:** ~140-300 KB (plenty of headroom)

#### 9.4 Memory Allocation Details

**DMA-Capable Memory:**
```cpp
heap_caps_malloc(size, MALLOC_CAP_DMA);
```
- Allocates from DMA-capable memory region
- Required for efficient SPI transfers
- ESP32 has separate DMA memory pool

**Why Double Buffering:**
- While one buffer is being sent to display
- LVGL can render to other buffer
- Prevents flickering
- Smooth animation

---

## Timing and Scheduling

### 10. Timing Diagram

```
Time (ms)    Activity
─────────────────────────────────────────
0            setup() starts
1            Serial.begin()
100          I2C initialized
200          MAX30102 configured
300          Display initialized
400          LVGL initialized
600          UI created
700          setup() complete
─────────────────────────────────────────
700          loop() starts
705          lv_timer_handler() (1ms)
710          updateSensors() (2ms) ← 10ms interval
715          lv_timer_handler() (1ms)
720          updateSensors() (2ms) ← 10ms interval
...
1700         updateClock() (1ms) ← 1000ms interval
...
5700         readTemperature() (100ms) ← 5000ms interval
...
```

### 10.1 Task Priorities

**High Priority (Every Loop):**
- LVGL task handler
- UI updates

**Medium Priority (10ms):**
- Sensor reading
- Algorithm processing

**Low Priority (1000ms):**
- Clock updates

**Very Low Priority (5000ms):**
- Temperature reading

### 10.2 Timing Constraints

**Critical Paths:**
- Sensor reading: Must complete in <10ms
- LVGL rendering: Should complete in <16ms (60 FPS)
- Display flush: Should complete in <50ms

**Actual Performance:**
- Sensor read: ~2-5ms ✅
- LVGL render: ~1-5ms ✅
- Display flush: ~5-50ms ✅ (depends on region size)

---

## Data Flow Diagrams

### 11. Complete System Data Flow

```
┌─────────────┐
│   MAX30102  │
│   Sensor    │
└──────┬──────┘
       │ I2C (100 Hz)
       ↓
┌─────────────┐
│ MAX30102    │
│  Driver     │
└──────┬──────┘
       │ FIFO Data
       ↓
┌─────────────┐      ┌─────────────┐
│   Heart     │      │    SpO2     │
│   Rate      │      │  Algorithm   │
│ Algorithm   │      └──────┬──────┘
└──────┬──────┘             │
       │                     │
       ↓                     ↓
┌─────────────┐      ┌─────────────┐
│ currentHR    │      │ currentSpO2 │
└──────┬──────┘      └──────┬──────┘
       │                    │
       └────────┬───────────┘
                ↓
         ┌─────────────┐
         │ UI Manager  │
         └──────┬──────┘
                │
                ↓
         ┌─────────────┐
         │    LVGL     │
         └──────┬──────┘
                │
                ↓
         ┌─────────────┐
         │ TFT_eSPI    │
         └──────┬──────┘
                │ SPI
                ↓
         ┌─────────────┐
         │   Display   │
         └─────────────┘
```

### 11. UI Navigation Flow

```
Main Screen
    │
    ├─→ Clock Button → Analog Clock Screen
    │                      │
    │                      ├─→ Digital Button → Digital Clock Screen
    │                      │                      │
    │                      │                      └─→ Back → Main Screen
    │                      │
    │                      └─→ Back → Main Screen
    │
    ├─→ Temperature Button → Temperature Screen
    │                           │
    │                           └─→ Back → Main Screen
    │
    ├─→ Heart Rate Button → Heart Rate Screen
    │                          │
    │                          └─→ Back → Main Screen
    │
    ├─→ SpO2 Button → SpO2 Screen
    │                    │
    │                    └─→ Back → Main Screen
    │
    └─→ Settings Button → Settings Screen
                              │
                              └─→ Back → Main Screen
```

---

## Summary

### Execution Summary

**Startup (setup):**
1. Initialize communication (Serial, I2C)
2. Configure MAX30102 sensor
3. Initialize display hardware
4. Setup LVGL graphics system
5. Create all UI screens
6. Configure time system
7. **Total time:** ~1-2 seconds

**Runtime (loop):**
1. Process LVGL tasks (~200 Hz)
2. Read sensors every 10ms (100 Hz)
3. Update clock every 1000ms (1 Hz)
4. Read temperature every 5000ms (0.2 Hz)
5. Update UI with latest data
6. Handle user interactions
7. **Loop time:** ~5-10ms per iteration

**Key Characteristics:**
- Non-blocking design
- Event-driven UI
- Real-time sensor processing
- Efficient memory usage
- Smooth 60 FPS graphics

This architecture ensures responsive UI, accurate sensor readings, and efficient resource usage.
