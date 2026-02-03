/**
 * Example 1: Basic Setup
 * 
 * This example demonstrates the minimal code required to:
 * 1. Initialize the TFT display using TFT_eSPI
 * 2. Initialize LVGL graphics library
 * 3. Set up the display buffer and flush callback
 * 4. Create a simple screen with a colored rectangle
 * 
 * Learning Objectives:
 * - Understand the initialization sequence
 * - Learn about display buffers
 * - See how LVGL connects to the hardware
 */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <SPI.h>

// ============================================================================
// DISPLAY CONFIGURATION
// ============================================================================
// These should match your display_config.h or TFT_eSPI User_Setup.h
#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240
#define DISPLAY_BL     15  // Backlight pin

// Display buffer size (for LVGL)
// Larger buffer = smoother updates but more memory
#define DISPLAY_BUF_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 10)

// ============================================================================
// GLOBAL OBJECTS
// ============================================================================
TFT_eSPI tft = TFT_eSPI();  // TFT_eSPI display driver instance

// Display buffers for LVGL (double buffering for smooth updates)
static lv_color_t buf1[DISPLAY_BUF_SIZE];
static lv_color_t buf2[DISPLAY_BUF_SIZE];

// ============================================================================
// LVGL DISPLAY FLUSH CALLBACK
// ============================================================================
/**
 * This function is called by LVGL whenever it needs to update the display.
 * LVGL renders graphics into a buffer, then calls this function to send
 * the pixel data to the actual display hardware.
 * 
 * Parameters:
 *   - disp: LVGL display object
 *   - area: Region to update (x1, y1, x2, y2 coordinates)
 *   - px_map: Buffer containing pixel data (RGB565 format)
 */
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    // Calculate the width and height of the area to update
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    uint32_t pixelCount = w * h;
    
    // Start SPI transaction for display
    tft.startWrite();
    
    // Set the drawing window on the display
    // This tells the display where to draw the pixels
    tft.setAddrWindow(area->x1, area->y1, w, h);
    
    // Send pixel data to display
    // pushColors sends the pixel buffer to the display via SPI
    // Parameters: (pixel_data, count, is_swapped)
    tft.pushColors((uint16_t*)px_map, pixelCount, true);
    
    // End SPI transaction
    tft.endWrite();
    
    // IMPORTANT: Tell LVGL that flushing is complete
    // LVGL will wait for this before continuing
    lv_display_flush_ready(disp);
}

// ============================================================================
// SETUP FUNCTION
// ============================================================================
void setup() {
    // Initialize Serial for debugging
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== LVGL Basic Setup Example ===");
    
    // ------------------------------------------------------------------------
    // Step 1: Initialize TFT Display Hardware
    // ------------------------------------------------------------------------
    Serial.println("[1/4] Initializing TFT display...");
    
    // Initialize SPI bus (required for display communication)
    SPI.begin();
    
    // Initialize TFT_eSPI display
    // This sets up the display controller (ILI9341, ST7789, etc.)
    tft.init();
    
    // Configure display settings
    tft.setRotation(0);           // 0=portrait, 1=landscape, 2=inverted portrait, 3=inverted landscape
    tft.fillScreen(TFT_BLACK);     // Clear screen to black
    tft.setSwapBytes(true);        // Required for LVGL color format (RGB565 byte swap)
    
    Serial.println("    ✓ Display initialized");
    Serial.print("    ✓ Resolution: ");
    Serial.print(DISPLAY_WIDTH);
    Serial.print("x");
    Serial.println(DISPLAY_HEIGHT);
    
    // Initialize backlight
    pinMode(DISPLAY_BL, OUTPUT);
    analogWrite(DISPLAY_BL, 200);  // Set brightness (0-255)
    Serial.println("    ✓ Backlight enabled");
    
    // ------------------------------------------------------------------------
    // Step 2: Initialize LVGL Library
    // ------------------------------------------------------------------------
    Serial.println("[2/4] Initializing LVGL library...");
    
    // Initialize LVGL core
    // This sets up internal data structures and prepares LVGL for use
    lv_init();
    
    Serial.println("    ✓ LVGL core initialized");
    
    // ------------------------------------------------------------------------
    // Step 3: Create LVGL Display Object
    // ------------------------------------------------------------------------
    Serial.println("[3/4] Creating LVGL display object...");
    
    // Create a display object with specified dimensions
    lv_display_t *disp = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    
    // Set up double buffering
    // buf1 and buf2 are used alternately for smooth rendering
    // When LVGL is drawing to buf1, buf2 can be sent to display, and vice versa
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    
    // Register the flush callback function
    // LVGL will call display_flush() whenever it needs to update the display
    lv_display_set_flush_cb(disp, display_flush);
    
    Serial.println("    ✓ Display object created");
    Serial.print("    ✓ Buffer size: ");
    Serial.print(DISPLAY_BUF_SIZE);
    Serial.println(" pixels");
    
    // ------------------------------------------------------------------------
    // Step 4: Create a Simple UI Element
    // ------------------------------------------------------------------------
    Serial.println("[4/4] Creating UI elements...");
    
    // Get the default screen object
    // LVGL always has at least one screen (the active screen)
    lv_obj_t *screen = lv_scr_act();
    
    // Set screen background color
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x001122), 0);
    
    // Create a simple colored rectangle to verify everything works
    lv_obj_t *rect = lv_obj_create(screen);
    lv_obj_set_size(rect, 200, 100);                    // Width: 200px, Height: 100px
    lv_obj_center(rect);                                // Center on screen
    lv_obj_set_style_bg_color(rect, lv_color_hex(0x00AAFF), 0);  // Blue background
    lv_obj_set_style_radius(rect, 10, 0);               // Rounded corners (10px radius)
    lv_obj_set_style_border_width(rect, 3, 0);          // 3px border
    lv_obj_set_style_border_color(rect, lv_color_hex(0xFFFFFF), 0);  // White border
    
    Serial.println("    ✓ UI elements created");
    Serial.println("\n=== Setup Complete! ===");
    Serial.println("You should see a blue rectangle with white border on the display.");
}

// ============================================================================
// LOOP FUNCTION
// ============================================================================
void loop() {
    // CRITICAL: Call this regularly to handle LVGL tasks
    // This function:
    // - Processes user input (touch, mouse, etc.)
    // - Handles animations
    // - Updates the display when needed
    // - Manages timers and callbacks
    //
    // Should be called every 5-10ms for smooth operation
    // No delay() calls should block this for too long!
    lv_timer_handler();
    
    // Small delay to prevent overwhelming the CPU
    // In a real application, you might use FreeRTOS tasks instead
    delay(5);
}

// ============================================================================
// NOTES FOR STUDENTS
// ============================================================================
/*
 * Key Concepts Explained:
 * 
 * 1. TFT_eSPI vs LVGL:
 *    - TFT_eSPI: Low-level driver that talks directly to display hardware
 *    - LVGL: High-level graphics library that creates UI elements
 *    - LVGL uses TFT_eSPI to actually draw on the display
 * 
 * 2. Display Buffers:
 *    - LVGL renders graphics into memory buffers first
 *    - Then sends buffer contents to display via flush callback
 *    - Double buffering prevents flickering during updates
 * 
 * 3. Flush Callback:
 *    - Called automatically by LVGL when display needs updating
 *    - You don't call it directly
 *    - Must call lv_display_flush_ready() when done
 * 
 * 4. lv_timer_handler():
 *    - Must be called regularly in loop()
 *    - Handles all LVGL internal processing
 *    - Without it, nothing will update or respond
 * 
 * 5. Screen Object:
 *    - Every LVGL application has at least one screen
 *    - All UI elements are children of a screen
 *    - You can create multiple screens and switch between them
 * 
 * Try Modifying:
 * - Change the rectangle color, size, or position
 * - Add more rectangles
 * - Change the screen background color
 * - Experiment with different border styles
 */
