/**
 * Example 2: Displaying Text and Information
 * 
 * This example demonstrates how to:
 * 1. Create text labels with LVGL
 * 2. Update text content dynamically
 * 3. Style text (colors, alignment, fonts)
 * 4. Display sensor data or system information
 * 
 * Learning Objectives:
 * - Understand label objects in LVGL
 * - Learn text formatting and styling
 * - See how to update UI elements in real-time
 * - Practice displaying dynamic information
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

// UI Objects (global so we can update them in loop())
lv_obj_t *title_label;
lv_obj_t *time_label;
lv_obj_t *counter_label;
lv_obj_t *heap_label;
lv_obj_t *status_label;

// Counter for demonstration
static uint32_t counter = 0;

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
// CREATE UI FUNCTION
// ============================================================================
/**
 * This function creates all the UI elements.
 * It's separated from setup() for better code organization.
 */
void create_ui() {
    // Get the active screen
    lv_obj_t *screen = lv_scr_act();
    
    // Set screen background to dark blue
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x001133), 0);
    
    // ------------------------------------------------------------------------
    // Example 1: Title Label (Static Text)
    // ------------------------------------------------------------------------
    title_label = lv_label_create(screen);
    lv_label_set_text(title_label, "ESP32 System Info");
    
    // Style the title
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), 0);  // White text
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_20, 0);   // Larger font
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);                   // Top center
    
    // ------------------------------------------------------------------------
    // Example 2: Time Label (Dynamic Text - Updates Every Second)
    // ------------------------------------------------------------------------
    time_label = lv_label_create(screen);
    lv_label_set_text(time_label, "Uptime: 0 ms");
    
    // Style: Yellow text, medium font
    lv_obj_set_style_text_color(time_label, lv_color_hex(0xFFFF00), 0);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_16, 0);
    lv_obj_align(time_label, LV_ALIGN_TOP_LEFT, 10, 50);
    
    // ------------------------------------------------------------------------
    // Example 3: Counter Label (Incrementing Number)
    // ------------------------------------------------------------------------
    counter_label = lv_label_create(screen);
    lv_label_set_text(counter_label, "Counter: 0");
    
    // Style: Green text
    lv_obj_set_style_text_color(counter_label, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(counter_label, &lv_font_montserrat_16, 0);
    lv_obj_align(counter_label, LV_ALIGN_TOP_LEFT, 10, 80);
    
    // ------------------------------------------------------------------------
    // Example 4: Heap Memory Label (System Information)
    // ------------------------------------------------------------------------
    heap_label = lv_label_create(screen);
    lv_label_set_text(heap_label, "Free Heap: 0 bytes");
    
    // Style: Cyan text
    lv_obj_set_style_text_color(heap_label, lv_color_hex(0x00FFFF), 0);
    lv_obj_set_style_text_font(heap_label, &lv_font_montserrat_14, 0);
    lv_obj_align(heap_label, LV_ALIGN_TOP_LEFT, 10, 110);
    
    // ------------------------------------------------------------------------
    // Example 5: Status Label with Background
    // ------------------------------------------------------------------------
    // Create a container (panel) for the status label
    lv_obj_t *status_panel = lv_obj_create(screen);
    lv_obj_set_size(status_panel, 280, 60);
    lv_obj_align(status_panel, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_style_bg_color(status_panel, lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(status_panel, 2, 0);
    lv_obj_set_style_border_color(status_panel, lv_color_hex(0x00AAFF), 0);
    lv_obj_set_style_radius(status_panel, 5, 0);
    
    // Create label inside the panel
    status_label = lv_label_create(status_panel);
    lv_label_set_text(status_label, "Status: Ready");
    lv_obj_set_style_text_color(status_label, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(status_label, &lv_font_montserrat_16, 0);
    lv_obj_center(status_label);
    
    // ------------------------------------------------------------------------
    // Example 6: Multi-line Text
    // ------------------------------------------------------------------------
    lv_obj_t *info_label = lv_label_create(screen);
    lv_label_set_text(info_label, "This is a\nmulti-line\ntext label");
    lv_obj_set_style_text_color(info_label, lv_color_hex(0xFFAA00), 0);
    lv_obj_set_style_text_font(info_label, &lv_font_montserrat_14, 0);
    lv_obj_align(info_label, LV_ALIGN_TOP_RIGHT, -10, 50);
    
    // Set text alignment within the label
    lv_obj_set_style_text_align(info_label, LV_TEXT_ALIGN_RIGHT, 0);
    
    // ------------------------------------------------------------------------
    // Example 7: Long Text with Scrolling
    // ------------------------------------------------------------------------
    lv_obj_t *scroll_label = lv_label_create(screen);
    lv_label_set_text(scroll_label, "This is a very long text that will scroll automatically if it doesn't fit in the available space. LVGL handles this automatically!");
    lv_obj_set_size(scroll_label, 150, 40);
    lv_obj_set_style_text_color(scroll_label, lv_color_hex(0xFF00FF), 0);
    lv_obj_set_style_text_font(scroll_label, &lv_font_montserrat_12, 0);
    lv_obj_align(scroll_label, LV_ALIGN_TOP_RIGHT, -10, 140);
    
    // Enable long mode: text will scroll if too long
    lv_label_set_long_mode(scroll_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
}

// ============================================================================
// UPDATE UI FUNCTION
// ============================================================================
/**
 * This function updates dynamic text labels.
 * Call this regularly to refresh displayed information.
 */
void update_ui() {
    static unsigned long lastUpdate = 0;
    unsigned long now = millis();
    
    // Update every 100ms for smooth counter
    if (now - lastUpdate >= 100) {
        // Update uptime
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Uptime: %lu ms", now);
        lv_label_set_text(time_label, buffer);
        
        // Update counter
        counter++;
        snprintf(buffer, sizeof(buffer), "Counter: %lu", counter);
        lv_label_set_text(counter_label, buffer);
        
        lastUpdate = now;
    }
    
    // Update heap memory every second (less frequent)
    static unsigned long lastHeapUpdate = 0;
    if (now - lastHeapUpdate >= 1000) {
        uint32_t freeHeap = ESP.getFreeHeap();
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Free Heap: %lu bytes", freeHeap);
        lv_label_set_text(heap_label, buffer);
        
        // Change color based on available memory
        if (freeHeap > 50000) {
            lv_obj_set_style_text_color(heap_label, lv_color_hex(0x00FF00), 0);  // Green
        } else if (freeHeap > 20000) {
            lv_obj_set_style_text_color(heap_label, lv_color_hex(0xFFFF00), 0);  // Yellow
        } else {
            lv_obj_set_style_text_color(heap_label, lv_color_hex(0xFF0000), 0);  // Red
        }
        
        lastHeapUpdate = now;
    }
    
    // Update status based on counter
    static uint32_t lastStatusUpdate = 0;
    if (counter != lastStatusUpdate) {
        if (counter % 10 == 0) {
            lv_label_set_text(status_label, "Status: Milestone!");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0x00FFFF), 0);
        } else {
            lv_label_set_text(status_label, "Status: Running");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0x00FF00), 0);
        }
        lastStatusUpdate = counter;
    }
}

// ============================================================================
// SETUP FUNCTION
// ============================================================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== LVGL Display Text Example ===");
    
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
    
    Serial.println("Setup complete! Display should show various text labels.");
}

// ============================================================================
// LOOP FUNCTION
// ============================================================================
void loop() {
    // Handle LVGL tasks
    lv_timer_handler();
    
    // Update dynamic text
    update_ui();
    
    // Small delay
    delay(5);
}

// ============================================================================
// NOTES FOR STUDENTS
// ============================================================================
/*
 * Key Concepts:
 * 
 * 1. Creating Labels:
 *    lv_obj_t *label = lv_label_create(parent);
 *    lv_label_set_text(label, "Hello World");
 * 
 * 2. Updating Text:
 *    - Use lv_label_set_text() to change text content
 *    - Can use sprintf/snprintf for formatted strings
 *    - Update in loop() for dynamic content
 * 
 * 3. Text Styling:
 *    - Color: lv_obj_set_style_text_color(label, color, 0)
 *    - Font: lv_obj_set_style_text_font(label, &font, 0)
 *    - Alignment: lv_obj_set_style_text_align(label, align, 0)
 * 
 * 4. Positioning:
 *    - lv_obj_align(obj, align_type, x_offset, y_offset)
 *    - Alignment types: LV_ALIGN_TOP_LEFT, LV_ALIGN_CENTER, etc.
 * 
 * 5. Long Text:
 *    - LV_LABEL_LONG_WRAP: Wrap text to multiple lines
 *    - LV_LABEL_LONG_SCROLL: Scroll text horizontally
 *    - LV_LABEL_LONG_SCROLL_CIRCULAR: Continuous scrolling
 * 
 * Common Patterns:
 * 
 * - Display sensor data:
 *   snprintf(buffer, size, "Temperature: %.1f°C", temp);
 *   lv_label_set_text(temp_label, buffer);
 * 
 * - Show status messages:
 *   lv_label_set_text(status_label, "Connected");
 *   lv_obj_set_style_text_color(status_label, lv_color_hex(0x00FF00), 0);
 * 
 * - Update counters:
 *   counter++;
 *   lv_label_set_text(counter_label, String(counter).c_str());
 * 
 * Try Modifying:
 * - Change text colors and fonts
 * - Add more information labels
 * - Display data from sensors (if available)
 * - Create a scrolling news ticker
 * - Add formatted numbers with units
 */
