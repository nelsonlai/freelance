/**
 * Example 4: Complete UI Application
 * 
 * This example combines all concepts into a functional application:
 * 1. Multiple screens with navigation
 * 2. Various UI widgets (buttons, labels, sliders, bars)
 * 3. Real-time data updates
 * 4. Interactive controls
 * 5. State management
 * 
 * Learning Objectives:
 * - Build a complete application
 * - Manage multiple screens
 * - Combine different widgets
 * - Handle complex interactions
 * - Organize code for larger projects
 */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <SPI.h>

// ============================================================================
// DISPLAY CONFIGURATION
// ============================================================================
#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240
#define DISPLAY_BL     15
#define DISPLAY_BUF_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 10)

// ============================================================================
// GLOBAL OBJECTS
// ============================================================================
TFT_eSPI tft = TFT_eSPI();
static lv_color_t buf1[DISPLAY_BUF_SIZE];
static lv_color_t buf2[DISPLAY_BUF_SIZE];

// Screen objects
lv_obj_t *main_screen;
lv_obj_t *settings_screen;
lv_obj_t *info_screen;

// Main screen widgets
lv_obj_t *temp_label;
lv_obj_t *humidity_label;
lv_obj_t *pressure_label;
lv_obj_t *status_bar;
lv_obj_t *progress_bar;

// Settings screen widgets
lv_obj_t *brightness_slider;
lv_obj_t *brightness_label;
lv_obj_t *volume_slider;
lv_obj_t *volume_label;

// Application state
static float temperature = 22.5;
static float humidity = 45.0;
static float pressure = 1013.25;
static uint8_t brightness = 80;
static uint8_t volume = 50;
static uint32_t progress = 0;

// ============================================================================
// LVGL DISPLAY FLUSH CALLBACK
// ============================================================================
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    uint32_t pixelCount = w * h;
    
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)px_map, pixelCount, true);
    tft.endWrite();
    
    lv_display_flush_ready(disp);
}

// ============================================================================
// EVENT HANDLERS
// ============================================================================

/**
 * Navigation: Switch to main screen
 */
void show_main_screen(lv_event_t *e) {
    lv_scr_load(main_screen);
    Serial.println("Switched to main screen");
}

/**
 * Navigation: Switch to settings screen
 */
void show_settings_screen(lv_event_t *e) {
    lv_scr_load(settings_screen);
    Serial.println("Switched to settings screen");
}

/**
 * Navigation: Switch to info screen
 */
void show_info_screen(lv_event_t *e) {
    lv_scr_load(info_screen);
    Serial.println("Switched to info screen");
}

/**
 * Brightness slider event handler
 */
void brightness_slider_handler(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    brightness = value;
    
    // Update label
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Brightness: %d%%", brightness);
    lv_label_set_text(brightness_label, buffer);
    
    // Update actual backlight (if connected)
    analogWrite(DISPLAY_BL, map(brightness, 0, 100, 0, 255));
    
    Serial.print("Brightness changed to: ");
    Serial.print(brightness);
    Serial.println("%");
}

/**
 * Volume slider event handler
 */
void volume_slider_handler(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    volume = value;
    
    // Update label
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Volume: %d%%", volume);
    lv_label_set_text(volume_label, buffer);
    
    Serial.print("Volume changed to: ");
    Serial.print(volume);
    Serial.println("%");
}

/**
 * Refresh data button handler
 */
void refresh_data_handler(lv_event_t *e) {
    // Simulate reading sensor data
    temperature += (random(-10, 11) / 10.0);
    humidity += (random(-5, 6) / 10.0);
    pressure += (random(-5, 6) / 10.0);
    
    // Clamp values
    if (temperature < 15) temperature = 15;
    if (temperature > 30) temperature = 30;
    if (humidity < 20) humidity = 20;
    if (humidity > 80) humidity = 80;
    if (pressure < 980) pressure = 980;
    if (pressure > 1050) pressure = 1050;
    
    update_sensor_display();
    Serial.println("Data refreshed");
}

/**
 * Reset button handler
 */
void reset_handler(lv_event_t *e) {
    temperature = 22.5;
    humidity = 45.0;
    pressure = 1013.25;
    progress = 0;
    
    update_sensor_display();
    lv_bar_set_value(progress_bar, 0, LV_ANIM_ON);
    
    Serial.println("Data reset");
}

// ============================================================================
// UI CREATION FUNCTIONS
// ============================================================================

/**
 * Create navigation bar (common to all screens)
 */
void create_nav_bar(lv_obj_t *screen) {
    // Create container for navigation buttons
    lv_obj_t *nav_bar = lv_obj_create(screen);
    lv_obj_set_size(nav_bar, DISPLAY_WIDTH, 35);
    lv_obj_align(nav_bar, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(nav_bar, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(nav_bar, 0, 0);
    lv_obj_set_style_pad_all(nav_bar, 5, 0);
    lv_obj_clear_flag(nav_bar, LV_OBJ_FLAG_SCROLLABLE);
    
    // Main button
    lv_obj_t *main_btn = lv_btn_create(nav_bar);
    lv_obj_set_size(main_btn, 90, 25);
    lv_obj_align(main_btn, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_set_style_bg_color(main_btn, lv_color_hex(0x0066FF), 0);
    lv_obj_t *main_label = lv_label_create(main_btn);
    lv_label_set_text(main_label, "Main");
    lv_obj_center(main_label);
    lv_obj_add_event_cb(main_btn, show_main_screen, LV_EVENT_CLICKED, NULL);
    
    // Settings button
    lv_obj_t *settings_btn = lv_btn_create(nav_bar);
    lv_obj_set_size(settings_btn, 90, 25);
    lv_obj_align(settings_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(settings_btn, lv_color_hex(0x666666), 0);
    lv_obj_t *settings_label = lv_label_create(settings_btn);
    lv_label_set_text(settings_label, "Settings");
    lv_obj_center(settings_label);
    lv_obj_add_event_cb(settings_btn, show_settings_screen, LV_EVENT_CLICKED, NULL);
    
    // Info button
    lv_obj_t *info_btn = lv_btn_create(nav_bar);
    lv_obj_set_size(info_btn, 90, 25);
    lv_obj_align(info_btn, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_set_style_bg_color(info_btn, lv_color_hex(0x666666), 0);
    lv_obj_t *info_label = lv_label_create(info_btn);
    lv_label_set_text(info_label, "Info");
    lv_obj_center(info_label);
    lv_obj_add_event_cb(info_btn, show_info_screen, LV_EVENT_CLICKED, NULL);
}

/**
 * Create main screen with sensor data
 */
void create_main_screen() {
    main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0x001122), 0);
    
    // Title
    lv_obj_t *title = lv_label_create(main_screen);
    lv_label_set_text(title, "Sensor Monitor");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);
    
    // Temperature display
    lv_obj_t *temp_container = lv_obj_create(main_screen);
    lv_obj_set_size(temp_container, 140, 50);
    lv_obj_align(temp_container, LV_ALIGN_TOP_LEFT, 10, 35);
    lv_obj_set_style_bg_color(temp_container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(temp_container, 2, 0);
    lv_obj_set_style_border_color(temp_container, lv_color_hex(0xFF6600), 0);
    
    lv_obj_t *temp_title = lv_label_create(temp_container);
    lv_label_set_text(temp_title, "Temperature");
    lv_obj_set_style_text_color(temp_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(temp_title, LV_ALIGN_TOP_LEFT, 5, 2);
    
    temp_label = lv_label_create(temp_container);
    lv_obj_set_style_text_color(temp_label, lv_color_hex(0xFF6600), 0);
    lv_obj_set_style_text_font(temp_label, &lv_font_montserrat_16, 0);
    lv_obj_align(temp_label, LV_ALIGN_BOTTOM_LEFT, 5, -2);
    
    // Humidity display
    lv_obj_t *humidity_container = lv_obj_create(main_screen);
    lv_obj_set_size(humidity_container, 140, 50);
    lv_obj_align(humidity_container, LV_ALIGN_TOP_RIGHT, -10, 35);
    lv_obj_set_style_bg_color(humidity_container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(humidity_container, 2, 0);
    lv_obj_set_style_border_color(humidity_container, lv_color_hex(0x0066FF), 0);
    
    lv_obj_t *humidity_title = lv_label_create(humidity_container);
    lv_label_set_text(humidity_title, "Humidity");
    lv_obj_set_style_text_color(humidity_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(humidity_title, LV_ALIGN_TOP_LEFT, 5, 2);
    
    humidity_label = lv_label_create(humidity_container);
    lv_obj_set_style_text_color(humidity_label, lv_color_hex(0x0066FF), 0);
    lv_obj_set_style_text_font(humidity_label, &lv_font_montserrat_16, 0);
    lv_obj_align(humidity_label, LV_ALIGN_BOTTOM_LEFT, 5, -2);
    
    // Pressure display
    lv_obj_t *pressure_container = lv_obj_create(main_screen);
    lv_obj_set_size(pressure_container, 140, 50);
    lv_obj_align(pressure_container, LV_ALIGN_TOP_LEFT, 10, 95);
    lv_obj_set_style_bg_color(pressure_container, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(pressure_container, 2, 0);
    lv_obj_set_style_border_color(pressure_container, lv_color_hex(0x00FF00), 0);
    
    lv_obj_t *pressure_title = lv_label_create(pressure_container);
    lv_label_set_text(pressure_title, "Pressure");
    lv_obj_set_style_text_color(pressure_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(pressure_title, LV_ALIGN_TOP_LEFT, 5, 2);
    
    pressure_label = lv_label_create(pressure_container);
    lv_obj_set_style_text_color(pressure_label, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(pressure_label, &lv_font_montserrat_16, 0);
    lv_obj_align(pressure_label, LV_ALIGN_BOTTOM_LEFT, 5, -2);
    
    // Progress bar
    lv_obj_t *progress_title = lv_label_create(main_screen);
    lv_label_set_text(progress_title, "Progress");
    lv_obj_set_style_text_color(progress_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(progress_title, LV_ALIGN_TOP_LEFT, 10, 155);
    
    progress_bar = lv_bar_create(main_screen);
    lv_obj_set_size(progress_bar, 280, 20);
    lv_obj_align(progress_bar, LV_ALIGN_TOP_LEFT, 10, 175);
    lv_bar_set_range(progress_bar, 0, 100);
    lv_bar_set_value(progress_bar, 0, LV_ANIM_ON);
    lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0x00AAFF), LV_PART_INDICATOR);
    
    // Control buttons
    lv_obj_t *refresh_btn = lv_btn_create(main_screen);
    lv_obj_set_size(refresh_btn, 130, 30);
    lv_obj_align(refresh_btn, LV_ALIGN_TOP_RIGHT, -10, 95);
    lv_obj_set_style_bg_color(refresh_btn, lv_color_hex(0x00AA00), 0);
    lv_obj_t *refresh_label = lv_label_create(refresh_btn);
    lv_label_set_text(refresh_label, "Refresh");
    lv_obj_center(refresh_label);
    lv_obj_add_event_cb(refresh_btn, refresh_data_handler, LV_EVENT_CLICKED, NULL);
    
    lv_obj_t *reset_btn = lv_btn_create(main_screen);
    lv_obj_set_size(reset_btn, 130, 30);
    lv_obj_align(reset_btn, LV_ALIGN_TOP_RIGHT, -10, 130);
    lv_obj_set_style_bg_color(reset_btn, lv_color_hex(0xAA0000), 0);
    lv_obj_t *reset_label = lv_label_create(reset_btn);
    lv_label_set_text(reset_label, "Reset");
    lv_obj_center(reset_label);
    lv_obj_add_event_cb(reset_btn, reset_handler, LV_EVENT_CLICKED, NULL);
    
    // Navigation bar
    create_nav_bar(main_screen);
    
    // Initial update
    update_sensor_display();
}

/**
 * Create settings screen
 */
void create_settings_screen() {
    settings_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(settings_screen, lv_color_hex(0x001122), 0);
    
    // Title
    lv_obj_t *title = lv_label_create(settings_screen);
    lv_label_set_text(title, "Settings");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);
    
    // Brightness control
    lv_obj_t *brightness_title = lv_label_create(settings_screen);
    lv_label_set_text(brightness_title, "Brightness");
    lv_obj_set_style_text_color(brightness_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(brightness_title, LV_ALIGN_TOP_LEFT, 10, 35);
    
    brightness_slider = lv_slider_create(settings_screen);
    lv_obj_set_size(brightness_slider, 280, 20);
    lv_obj_align(brightness_slider, LV_ALIGN_TOP_LEFT, 10, 55);
    lv_slider_set_range(brightness_slider, 0, 100);
    lv_slider_set_value(brightness_slider, brightness, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(brightness_slider, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_color(brightness_slider, lv_color_hex(0xFFFF00), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(brightness_slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
    lv_obj_add_event_cb(brightness_slider, brightness_slider_handler, LV_EVENT_VALUE_CHANGED, NULL);
    
    brightness_label = lv_label_create(settings_screen);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Brightness: %d%%", brightness);
    lv_label_set_text(brightness_label, buffer);
    lv_obj_set_style_text_color(brightness_label, lv_color_hex(0xFFFF00), 0);
    lv_obj_align(brightness_label, LV_ALIGN_TOP_LEFT, 10, 80);
    
    // Volume control
    lv_obj_t *volume_title = lv_label_create(settings_screen);
    lv_label_set_text(volume_title, "Volume");
    lv_obj_set_style_text_color(volume_title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(volume_title, LV_ALIGN_TOP_LEFT, 10, 110);
    
    volume_slider = lv_slider_create(settings_screen);
    lv_obj_set_size(volume_slider, 280, 20);
    lv_obj_align(volume_slider, LV_ALIGN_TOP_LEFT, 10, 130);
    lv_slider_set_range(volume_slider, 0, 100);
    lv_slider_set_value(volume_slider, volume, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(volume_slider, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_color(volume_slider, lv_color_hex(0x00AAFF), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(volume_slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
    lv_obj_add_event_cb(volume_slider, volume_slider_handler, LV_EVENT_VALUE_CHANGED, NULL);
    
    volume_label = lv_label_create(settings_screen);
    snprintf(buffer, sizeof(buffer), "Volume: %d%%", volume);
    lv_label_set_text(volume_label, buffer);
    lv_obj_set_style_text_color(volume_label, lv_color_hex(0x00AAFF), 0);
    lv_obj_align(volume_label, LV_ALIGN_TOP_LEFT, 10, 155);
    
    // Navigation bar
    create_nav_bar(settings_screen);
}

/**
 * Create info screen
 */
void create_info_screen() {
    info_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(info_screen, lv_color_hex(0x001122), 0);
    
    // Title
    lv_obj_t *title = lv_label_create(info_screen);
    lv_label_set_text(title, "System Information");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);
    
    // System info labels
    lv_obj_t *info_container = lv_obj_create(info_screen);
    lv_obj_set_size(info_container, 300, 150);
    lv_obj_align(info_container, LV_ALIGN_TOP_MID, 0, 35);
    lv_obj_set_style_bg_color(info_container, lv_color_hex(0x222222), 0);
    lv_obj_set_style_border_width(info_container, 2, 0);
    lv_obj_set_style_border_color(info_container, lv_color_hex(0x00AAFF), 0);
    lv_obj_clear_flag(info_container, LV_OBJ_FLAG_SCROLLABLE);
    
    // Info text
    lv_obj_t *info_text = lv_label_create(info_container);
    lv_label_set_text(info_text, 
        "ESP32 + LVGL Demo\n\n"
        "Platform: ESP32\n"
        "Framework: Arduino\n"
        "Display: TFT_eSPI\n"
        "Graphics: LVGL 8.3\n\n"
        "This is a complete UI\nexample demonstrating\nmultiple screens and\ninteractive widgets.");
    lv_obj_set_style_text_color(info_text, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(info_text, &lv_font_montserrat_14, 0);
    lv_obj_align(info_text, LV_ALIGN_TOP_LEFT, 10, 10);
    
    // Navigation bar
    create_nav_bar(info_screen);
}

/**
 * Update sensor data display
 */
void update_sensor_display() {
    char buffer[30];
    
    snprintf(buffer, sizeof(buffer), "%.1f°C", temperature);
    lv_label_set_text(temp_label, buffer);
    
    snprintf(buffer, sizeof(buffer), "%.1f%%", humidity);
    lv_label_set_text(humidity_label, buffer);
    
    snprintf(buffer, sizeof(buffer), "%.2f hPa", pressure);
    lv_label_set_text(pressure_label, buffer);
}

// ============================================================================
// SETUP FUNCTION
// ============================================================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== LVGL Complete UI Example ===");
    
    // Initialize display
    SPI.begin();
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    
    pinMode(DISPLAY_BL, OUTPUT);
    analogWrite(DISPLAY_BL, map(brightness, 0, 100, 0, 255));
    
    // Initialize LVGL
    lv_init();
    
    // Create display object
    lv_display_t *disp = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, display_flush);
    
    // Create all screens
    create_main_screen();
    create_settings_screen();
    create_info_screen();
    
    // Load main screen
    lv_scr_load(main_screen);
    
    Serial.println("Setup complete! Application ready.");
}

// ============================================================================
// LOOP FUNCTION
// ============================================================================
void loop() {
    // Handle LVGL tasks
    lv_timer_handler();
    
    // Simulate sensor data updates
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate >= 2000) {  // Update every 2 seconds
        // Small random variations
        temperature += (random(-5, 6) / 10.0);
        humidity += (random(-3, 4) / 10.0);
        pressure += (random(-2, 3) / 10.0);
        
        // Clamp values
        if (temperature < 15) temperature = 15;
        if (temperature > 30) temperature = 30;
        if (humidity < 20) humidity = 20;
        if (humidity > 80) humidity = 80;
        if (pressure < 980) pressure = 980;
        if (pressure > 1050) pressure = 1050;
        
        // Update display if on main screen
        if (lv_scr_act() == main_screen) {
            update_sensor_display();
        }
        
        // Update progress bar
        progress = (progress + 1) % 101;
        lv_bar_set_value(progress_bar, progress, LV_ANIM_ON);
        
        lastUpdate = millis();
    }
    
    delay(5);
}

// ============================================================================
// NOTES FOR STUDENTS
// ============================================================================
/*
 * This example demonstrates:
 * 
 * 1. Multiple Screens:
 *    - Create screens: lv_obj_create(NULL)
 *    - Switch screens: lv_scr_load(screen)
 *    - Get current screen: lv_scr_act()
 * 
 * 2. Sliders:
 *    - Create: lv_slider_create(parent)
 *    - Set range: lv_slider_set_range(slider, min, max)
 *    - Get value: lv_slider_get_value(slider)
 *    - Set value: lv_slider_set_value(slider, value, anim)
 * 
 * 3. Progress Bars:
 *    - Create: lv_bar_create(parent)
 *    - Set range: lv_bar_set_range(bar, min, max)
 *    - Set value: lv_bar_set_value(bar, value, anim)
 * 
 * 4. Code Organization:
 *    - Separate functions for each screen
 *    - Event handlers in separate functions
 *    - State management with global variables
 *    - Update functions for dynamic content
 * 
 * 5. Real-time Updates:
 *    - Update in loop() based on time
 *    - Only update visible screen
 *    - Use animations for smooth transitions
 * 
 * Advanced Topics:
 * 
 * - State Management:
 *   Use structs to organize application state
 *   Save/load settings from EEPROM or SPIFFS
 * 
 * - Screen Transitions:
 *   Use animations for screen changes
 *   lv_scr_load_anim(screen, anim_type, time, delay, auto_del)
 * 
 * - Widget Styling:
 *   Create custom themes
 *   Use style properties for consistent look
 * 
 * - Data Binding:
 *   Connect widgets to data sources
 *   Update multiple widgets from one data change
 * 
 * Try Adding:
 * - More screens (alarms, logs, etc.)
 * - Charts for data visualization
 * - Lists for settings options
 * - Keyboard for text input
 * - More interactive widgets
 */
