/**
 * Example 3: Creating Buttons and Handling Clicks
 * 
 * This example demonstrates how to:
 * 1. Create different types of buttons
 * 2. Style buttons (colors, sizes, shapes)
 * 3. Handle button click events
 * 4. Update UI based on button interactions
 * 5. Create button groups and navigation
 * 
 * Learning Objectives:
 * - Understand event-driven programming in LVGL
 * - Learn how to create and style buttons
 * - Master event callbacks and event handling
 * - Practice creating interactive interfaces
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

// UI Objects
lv_obj_t *status_label;
lv_obj_t *counter_label;
lv_obj_t *led_button;
lv_obj_t *reset_button;
lv_obj_t *color_button;

// Application state
static uint32_t click_count = 0;
static bool led_state = false;
static uint8_t color_index = 0;
static const uint32_t colors[] = {
    0xFF0000,  // Red
    0x00FF00,  // Green
    0x0000FF,  // Blue
    0xFFFF00,  // Yellow
    0xFF00FF,  // Magenta
    0x00FFFF,  // Cyan
};

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
// EVENT HANDLER FUNCTIONS
// ============================================================================

/**
 * Example 1: Simple Button Click Handler
 * This function is called when the LED toggle button is clicked.
 */
void led_button_handler(lv_event_t *e) {
    // Get the event code (what type of event occurred)
    lv_event_code_t code = lv_event_get_code(e);
    
    // Check if it's a click event
    if (code == LV_EVENT_CLICKED) {
        // Toggle LED state
        led_state = !led_state;
        
        // Get the button object that triggered the event
        lv_obj_t *btn = lv_event_get_target(e);
        
        // Update button appearance based on state
        if (led_state) {
            // LED ON: Green background
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), 0);
            lv_label_set_text(lv_obj_get_child(btn, 0), "LED: ON");
            Serial.println("LED turned ON");
        } else {
            // LED OFF: Red background
            lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), 0);
            lv_label_set_text(lv_obj_get_child(btn, 0), "LED: OFF");
            Serial.println("LED turned OFF");
        }
        
        // Update status label
        lv_label_set_text(status_label, led_state ? "Status: LED ON" : "Status: LED OFF");
    }
}

/**
 * Example 2: Counter Button Handler
 * Increments a counter and updates display.
 */
void counter_button_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_CLICKED) {
        click_count++;
        
        // Update counter label
        char buffer[30];
        snprintf(buffer, sizeof(buffer), "Clicks: %lu", click_count);
        lv_label_set_text(counter_label, buffer);
        
        // Update status
        snprintf(buffer, sizeof(buffer), "Status: Button clicked %lu times", click_count);
        lv_label_set_text(status_label, buffer);
        
        Serial.print("Button clicked! Count: ");
        Serial.println(click_count);
    }
}

/**
 * Example 3: Reset Button Handler
 * Resets the counter to zero.
 */
void reset_button_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_CLICKED) {
        click_count = 0;
        
        // Update labels
        lv_label_set_text(counter_label, "Clicks: 0");
        lv_label_set_text(status_label, "Status: Counter reset");
        
        Serial.println("Counter reset!");
    }
}

/**
 * Example 4: Color Change Button Handler
 * Cycles through different colors.
 */
void color_button_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_CLICKED) {
        // Cycle to next color
        color_index = (color_index + 1) % (sizeof(colors) / sizeof(colors[0]));
        
        // Get button and update color
        lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_set_style_bg_color(btn, lv_color_hex(colors[color_index]), 0);
        
        // Update status with color name
        const char* color_names[] = {"Red", "Green", "Blue", "Yellow", "Magenta", "Cyan"};
        char buffer[30];
        snprintf(buffer, sizeof(buffer), "Color: %s", color_names[color_index]);
        lv_label_set_text(status_label, buffer);
        
        Serial.print("Color changed to: ");
        Serial.println(color_names[color_index]);
    }
}

/**
 * Example 5: Button with Multiple Event Types
 * Handles different events (pressed, released, long pressed).
 */
void multi_event_button_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    
    switch (code) {
        case LV_EVENT_PRESSED:
            // Button is being pressed (finger down)
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x888888), 0);
            Serial.println("Button pressed");
            break;
            
        case LV_EVENT_RELEASED:
            // Button was released (finger up)
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x0066FF), 0);
            Serial.println("Button released");
            break;
            
        case LV_EVENT_LONG_PRESSED:
            // Button was held for a long time
            lv_label_set_text(status_label, "Status: Long press detected!");
            Serial.println("Long press!");
            break;
            
        case LV_EVENT_CLICKED:
            // Complete click (press + release)
            lv_label_set_text(status_label, "Status: Clicked!");
            Serial.println("Button clicked");
            break;
    }
}

// ============================================================================
// CREATE UI FUNCTION
// ============================================================================
void create_ui() {
    lv_obj_t *screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x001122), 0);
    
    // ------------------------------------------------------------------------
    // Title Label
    // ------------------------------------------------------------------------
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Button Examples");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);
    
    // ------------------------------------------------------------------------
    // Status Label (shows current status)
    // ------------------------------------------------------------------------
    status_label = lv_label_create(screen);
    lv_label_set_text(status_label, "Status: Ready");
    lv_obj_set_style_text_color(status_label, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(status_label, &lv_font_montserrat_14, 0);
    lv_obj_align(status_label, LV_ALIGN_TOP_MID, 0, 30);
    
    // ------------------------------------------------------------------------
    // Counter Label
    // ------------------------------------------------------------------------
    counter_label = lv_label_create(screen);
    lv_label_set_text(counter_label, "Clicks: 0");
    lv_obj_set_style_text_color(counter_label, lv_color_hex(0xFFFF00), 0);
    lv_obj_set_style_text_font(counter_label, &lv_font_montserrat_16, 0);
    lv_obj_align(counter_label, LV_ALIGN_TOP_LEFT, 10, 60);
    
    // ------------------------------------------------------------------------
    // Example 1: Simple Toggle Button (LED ON/OFF)
    // ------------------------------------------------------------------------
    led_button = lv_btn_create(screen);
    lv_obj_set_size(led_button, 120, 40);
    lv_obj_align(led_button, LV_ALIGN_TOP_LEFT, 10, 90);
    
    // Style the button
    lv_obj_set_style_bg_color(led_button, lv_color_hex(0xFF0000), 0);  // Start red (OFF)
    lv_obj_set_style_radius(led_button, 5, 0);
    
    // Add label to button
    lv_obj_t *led_label = lv_label_create(led_button);
    lv_label_set_text(led_label, "LED: OFF");
    lv_obj_center(led_label);
    lv_obj_set_style_text_color(led_label, lv_color_hex(0xFFFFFF), 0);
    
    // Register event handler
    lv_obj_add_event_cb(led_button, led_button_handler, LV_EVENT_CLICKED, NULL);
    
    // ------------------------------------------------------------------------
    // Example 2: Counter Button
    // ------------------------------------------------------------------------
    lv_obj_t *counter_btn = lv_btn_create(screen);
    lv_obj_set_size(counter_btn, 120, 40);
    lv_obj_align(counter_btn, LV_ALIGN_TOP_RIGHT, -10, 90);
    
    lv_obj_set_style_bg_color(counter_btn, lv_color_hex(0x0066FF), 0);
    lv_obj_set_style_radius(counter_btn, 5, 0);
    
    lv_obj_t *counter_btn_label = lv_label_create(counter_btn);
    lv_label_set_text(counter_btn_label, "Click Me!");
    lv_obj_center(counter_btn_label);
    lv_obj_set_style_text_color(counter_btn_label, lv_color_hex(0xFFFFFF), 0);
    
    lv_obj_add_event_cb(counter_btn, counter_button_handler, LV_EVENT_CLICKED, NULL);
    
    // ------------------------------------------------------------------------
    // Example 3: Reset Button
    // ------------------------------------------------------------------------
    reset_button = lv_btn_create(screen);
    lv_obj_set_size(reset_button, 100, 35);
    lv_obj_align(reset_button, LV_ALIGN_TOP_LEFT, 10, 140);
    
    lv_obj_set_style_bg_color(reset_button, lv_color_hex(0xFF6600), 0);
    lv_obj_set_style_radius(reset_button, 5, 0);
    
    lv_obj_t *reset_label = lv_label_create(reset_button);
    lv_label_set_text(reset_label, "Reset");
    lv_obj_center(reset_label);
    lv_obj_set_style_text_color(reset_label, lv_color_hex(0xFFFFFF), 0);
    
    lv_obj_add_event_cb(reset_button, reset_button_handler, LV_EVENT_CLICKED, NULL);
    
    // ------------------------------------------------------------------------
    // Example 4: Color Change Button
    // ------------------------------------------------------------------------
    color_button = lv_btn_create(screen);
    lv_obj_set_size(color_button, 100, 35);
    lv_obj_align(color_button, LV_ALIGN_TOP_RIGHT, -10, 140);
    
    lv_obj_set_style_bg_color(color_button, lv_color_hex(colors[0]), 0);  // Start with red
    lv_obj_set_style_radius(color_button, 5, 0);
    
    lv_obj_t *color_label = lv_label_create(color_button);
    lv_label_set_text(color_label, "Color");
    lv_obj_center(color_label);
    lv_obj_set_style_text_color(color_label, lv_color_hex(0xFFFFFF), 0);
    
    lv_obj_add_event_cb(color_button, color_button_handler, LV_EVENT_CLICKED, NULL);
    
    // ------------------------------------------------------------------------
    // Example 5: Multi-Event Button (handles multiple event types)
    // ------------------------------------------------------------------------
    lv_obj_t *multi_btn = lv_btn_create(screen);
    lv_obj_set_size(multi_btn, 200, 35);
    lv_obj_align(multi_btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    
    lv_obj_set_style_bg_color(multi_btn, lv_color_hex(0x0066FF), 0);
    lv_obj_set_style_radius(multi_btn, 5, 0);
    
    lv_obj_t *multi_label = lv_label_create(multi_btn);
    lv_label_set_text(multi_label, "Press, Release, Long Press");
    lv_obj_center(multi_label);
    lv_obj_set_style_text_color(multi_label, lv_color_hex(0xFFFFFF), 0);
    
    // Register multiple event types
    lv_obj_add_event_cb(multi_btn, multi_event_button_handler, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(multi_btn, multi_event_button_handler, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(multi_btn, multi_event_button_handler, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(multi_btn, multi_event_button_handler, LV_EVENT_CLICKED, NULL);
}

// ============================================================================
// SETUP FUNCTION
// ============================================================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== LVGL Button Examples ===");
    
    // Initialize display
    SPI.begin();
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    
    pinMode(DISPLAY_BL, OUTPUT);
    analogWrite(DISPLAY_BL, 200);
    
    // Initialize LVGL
    lv_init();
    
    // Create display object
    lv_display_t *disp = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, display_flush);
    
    // Create UI
    create_ui();
    
    Serial.println("Setup complete! Try clicking the buttons.");
    Serial.println("Watch Serial monitor for event messages.");
}

// ============================================================================
// LOOP FUNCTION
// ============================================================================
void loop() {
    // Handle LVGL tasks (required for event processing)
    lv_timer_handler();
    
    delay(5);
}

// ============================================================================
// NOTES FOR STUDENTS
// ============================================================================
/*
 * Key Concepts:
 * 
 * 1. Creating Buttons:
 *    lv_obj_t *btn = lv_btn_create(parent);
 *    lv_obj_set_size(btn, width, height);
 * 
 * 2. Adding Labels to Buttons:
 *    lv_obj_t *label = lv_label_create(btn);
 *    lv_label_set_text(label, "Button Text");
 *    lv_obj_center(label);
 * 
 * 3. Event Callbacks:
 *    lv_obj_add_event_cb(btn, handler_function, event_type, user_data);
 * 
 * 4. Common Event Types:
 *    - LV_EVENT_CLICKED: Complete click (press + release)
 *    - LV_EVENT_PRESSED: Button pressed (finger down)
 *    - LV_EVENT_RELEASED: Button released (finger up)
 *    - LV_EVENT_LONG_PRESSED: Long press detected
 *    - LV_EVENT_VALUE_CHANGED: Value changed (for sliders, etc.)
 * 
 * 5. Event Handler Function:
 *    void handler(lv_event_t *e) {
 *        lv_event_code_t code = lv_event_get_code(e);
 *        lv_obj_t *target = lv_event_get_target(e);
 *        // Your code here
 *    }
 * 
 * 6. Getting Button Child (Label):
 *    lv_obj_t *label = lv_obj_get_child(btn, 0);
 *    lv_label_set_text(label, "New Text");
 * 
 * Button Styling:
 * 
 * - Background color: lv_obj_set_style_bg_color(btn, color, 0)
 * - Border: lv_obj_set_style_border_width(btn, width, 0)
 * - Radius (rounded corners): lv_obj_set_style_radius(btn, radius, 0)
 * - Padding: lv_obj_set_style_pad_all(btn, padding, 0)
 * 
 * Advanced Patterns:
 * 
 * 1. Button with State:
 *    - Store state in global variable or user_data
 *    - Update button appearance based on state
 *    - Toggle state on click
 * 
 * 2. Button Groups:
 *    - Create multiple buttons
 *    - Use same event handler with user_data to identify which button
 *    - Or create separate handlers for each button
 * 
 * 3. Disabled Buttons:
 *    - lv_obj_add_state(btn, LV_STATE_DISABLED)
 *    - lv_obj_clear_state(btn, LV_STATE_DISABLED)
 * 
 * 4. Button with Icon:
 *    - Use lv_img_create() instead of label
 *    - Or combine label and icon
 * 
 * Try Modifying:
 * - Change button colors and sizes
 * - Add more buttons with different functions
 * - Create a button that changes screen
 * - Add button animations
 * - Create a keyboard with multiple buttons
 * - Implement button debouncing logic
 */
