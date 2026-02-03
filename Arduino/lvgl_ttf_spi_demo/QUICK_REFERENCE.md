# LVGL Quick Reference Guide

A quick reference for common LVGL operations when working with ESP32 and TFT_eSPI.

## Table of Contents
- [Initialization](#initialization)
- [Creating Objects](#creating-objects)
- [Labels (Text)](#labels-text)
- [Buttons](#buttons)
- [Sliders](#sliders)
- [Bars (Progress)](#bars-progress)
- [Styling](#styling)
- [Events](#events)
- [Positioning](#positioning)
- [Colors](#colors)
- [Common Patterns](#common-patterns)

---

## Initialization

```cpp
// 1. Initialize LVGL
lv_init();

// 2. Create display
lv_display_t *disp = lv_display_create(width, height);
lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
lv_display_set_flush_cb(disp, display_flush);

// 3. Call in loop()
lv_timer_handler();
```

---

## Creating Objects

```cpp
// Create object
lv_obj_t *obj = lv_obj_create(parent);

// Common parent options:
lv_scr_act()        // Current screen
lv_obj_create(NULL) // New screen
any_obj             // Any existing object

// Set size
lv_obj_set_size(obj, width, height);

// Set position
lv_obj_set_pos(obj, x, y);

// Center object
lv_obj_center(obj);
```

---

## Labels (Text)

```cpp
// Create label
lv_obj_t *label = lv_label_create(parent);

// Set text
lv_label_set_text(label, "Hello World");

// Set text with formatting
char buffer[50];
snprintf(buffer, sizeof(buffer), "Value: %d", value);
lv_label_set_text(label, buffer);

// Long text modes
lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);           // Wrap text
lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);        // Scroll horizontally
lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); // Continuous scroll

// Text alignment
lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);
lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
```

---

## Buttons

```cpp
// Create button
lv_obj_t *btn = lv_btn_create(parent);

// Add label to button
lv_obj_t *label = lv_label_create(btn);
lv_label_set_text(label, "Click Me");
lv_obj_center(label);

// Event handler
void button_handler(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        // Button clicked
    }
}

// Register event
lv_obj_add_event_cb(btn, button_handler, LV_EVENT_CLICKED, NULL);
```

---

## Sliders

```cpp
// Create slider
lv_obj_t *slider = lv_slider_create(parent);

// Set range
lv_slider_set_range(slider, 0, 100);

// Get value
int32_t value = lv_slider_get_value(slider);

// Set value
lv_slider_set_value(slider, 50, LV_ANIM_ON);  // With animation
lv_slider_set_value(slider, 50, LV_ANIM_OFF); // Without animation

// Event handler
void slider_handler(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) {
        int32_t value = lv_slider_get_value(lv_event_get_target(e));
    }
}

// Register event
lv_obj_add_event_cb(slider, slider_handler, LV_EVENT_VALUE_CHANGED, NULL);
```

---

## Bars (Progress)

```cpp
// Create bar
lv_obj_t *bar = lv_bar_create(parent);

// Set range
lv_bar_set_range(bar, 0, 100);

// Set value
lv_bar_set_value(bar, 75, LV_ANIM_ON);

// Get value
int32_t value = lv_bar_get_value(bar);
```

---

## Styling

```cpp
// Background color
lv_obj_set_style_bg_color(obj, lv_color_hex(0xFF0000), 0);

// Border
lv_obj_set_style_border_width(obj, 2, 0);
lv_obj_set_style_border_color(obj, lv_color_hex(0xFFFFFF), 0);

// Radius (rounded corners)
lv_obj_set_style_radius(obj, 10, 0);

// Padding
lv_obj_set_style_pad_all(obj, 10, 0);

// Text color
lv_obj_set_style_text_color(obj, lv_color_hex(0xFFFFFF), 0);

// Font
lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, 0);

// Opacity
lv_obj_set_style_opa(obj, LV_OPA_50, 0);  // 50% opacity
```

---

## Events

```cpp
// Common event types
LV_EVENT_CLICKED        // Complete click (press + release)
LV_EVENT_PRESSED        // Button pressed
LV_EVENT_RELEASED       // Button released
LV_EVENT_LONG_PRESSED   // Long press
LV_EVENT_VALUE_CHANGED  // Value changed (sliders, etc.)
LV_EVENT_FOCUSED        // Object focused
LV_EVENT_DEFOCUSED      // Object unfocused

// Event handler
void event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    void *user_data = lv_event_get_user_data(e);
    
    switch(code) {
        case LV_EVENT_CLICKED:
            // Handle click
            break;
        case LV_EVENT_VALUE_CHANGED:
            // Handle value change
            break;
    }
}

// Register event
lv_obj_add_event_cb(obj, event_handler, LV_EVENT_CLICKED, user_data);
```

---

## Positioning

```cpp
// Align to parent
lv_obj_align(obj, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 10);
lv_obj_align(obj, LV_ALIGN_TOP_RIGHT, -10, 10);
lv_obj_align(obj, LV_ALIGN_BOTTOM_LEFT, 10, -10);
lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, -10);
lv_obj_align(obj, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
lv_obj_align(obj, LV_ALIGN_LEFT_MID, 10, 0);
lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
lv_obj_align(obj, LV_ALIGN_RIGHT_MID, -10, 0);

// Set absolute position
lv_obj_set_pos(obj, x, y);

// Get position
int32_t x = lv_obj_get_x(obj);
int32_t y = lv_obj_get_y(obj);
```

---

## Colors

```cpp
// Create color from hex
lv_color_t color = lv_color_hex(0xFF0000);  // Red

// Create color from RGB
lv_color_t color = lv_color_make(255, 0, 0);  // Red

// Predefined colors
lv_color_hex(0xFF0000)  // Red
lv_color_hex(0x00FF00)  // Green
lv_color_hex(0x0000FF)  // Blue
lv_color_hex(0xFFFFFF)  // White
lv_color_hex(0x000000)  // Black
lv_color_hex(0xFFFF00)  // Yellow
lv_color_hex(0xFF00FF)  // Magenta
lv_color_hex(0x00FFFF)  // Cyan

// Set color
lv_obj_set_style_bg_color(obj, color, 0);
lv_obj_set_style_text_color(obj, color, 0);
lv_obj_set_style_border_color(obj, color, 0);
```

---

## Common Patterns

### Update Text Periodically

```cpp
void loop() {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate >= 1000) {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Time: %lu", millis());
        lv_label_set_text(time_label, buffer);
        lastUpdate = millis();
    }
    lv_timer_handler();
}
```

### Toggle Button State

```cpp
static bool state = false;

void toggle_handler(lv_event_t *e) {
    state = !state;
    lv_obj_t *btn = lv_event_get_target(e);
    if (state) {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x00FF00), 0);
    } else {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF0000), 0);
    }
}
```

### Multiple Screens

```cpp
// Create screens
lv_obj_t *screen1 = lv_obj_create(NULL);
lv_obj_t *screen2 = lv_obj_create(NULL);

// Switch screen
lv_scr_load(screen1);

// Get current screen
lv_obj_t *current = lv_scr_act();
```

### Button with User Data

```cpp
// Pass data to event handler
int button_id = 1;
lv_obj_add_event_cb(btn, handler, LV_EVENT_CLICKED, (void*)button_id);

// In handler
void handler(lv_event_t *e) {
    int id = (int)lv_event_get_user_data(e);
    // Use id to identify which button
}
```

### Update Slider Label

```cpp
void slider_handler(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Value: %d", value);
    lv_label_set_text(value_label, buffer);
}
```

### Progress Bar with Percentage

```cpp
lv_obj_t *bar = lv_bar_create(parent);
lv_bar_set_range(bar, 0, 100);
lv_bar_set_value(bar, 75, LV_ANIM_ON);

// Show percentage
char buffer[10];
snprintf(buffer, sizeof(buffer), "%d%%", 75);
lv_label_set_text(percent_label, buffer);
```

### Disable/Enable Object

```cpp
// Disable
lv_obj_add_state(obj, LV_STATE_DISABLED);

// Enable
lv_obj_clear_state(obj, LV_STATE_DISABLED);

// Check if disabled
bool disabled = lv_obj_has_state(obj, LV_STATE_DISABLED);
```

### Delete Object

```cpp
// Delete object and all children
lv_obj_del(obj);

// Delete after delay
lv_obj_del_delayed(obj, 1000);  // Delete after 1 second
```

---

## Memory Management

```cpp
// Check free heap
uint32_t free = ESP.getFreeHeap();

// Static buffers (recommended)
static lv_color_t buf[BUFFER_SIZE];

// Dynamic allocation (use carefully)
lv_color_t *buf = (lv_color_t*)malloc(BUFFER_SIZE * sizeof(lv_color_t));
```

---

## Debugging Tips

```cpp
// Print object info
Serial.print("Object X: ");
Serial.println(lv_obj_get_x(obj));

// Check if object exists
if (obj != NULL) {
    // Object is valid
}

// Monitor LVGL tasks
// Call lv_timer_handler() regularly!
```

---

## Common Widgets Quick Reference

| Widget | Create Function | Key Functions |
|--------|----------------|---------------|
| Label | `lv_label_create()` | `lv_label_set_text()` |
| Button | `lv_btn_create()` | `lv_obj_add_event_cb()` |
| Slider | `lv_slider_create()` | `lv_slider_set_value()`, `lv_slider_get_value()` |
| Bar | `lv_bar_create()` | `lv_bar_set_value()`, `lv_bar_get_value()` |
| Switch | `lv_switch_create()` | `lv_obj_add_state()`, `lv_obj_clear_state()` |
| Checkbox | `lv_checkbox_create()` | `lv_checkbox_set_text()` |
| Dropdown | `lv_dropdown_create()` | `lv_dropdown_set_options()` |
| List | `lv_list_create()` | `lv_list_add_btn()` |
| Chart | `lv_chart_create()` | `lv_chart_add_series()`, `lv_chart_set_next_value()` |

---

## Fonts Available

```cpp
&lv_font_montserrat_12
&lv_font_montserrat_14
&lv_font_montserrat_16
&lv_font_montserrat_18
&lv_font_montserrat_20
&lv_font_montserrat_24
```

---

## Animation

```cpp
// Animate value change
lv_slider_set_value(slider, 50, LV_ANIM_ON);  // With animation
lv_slider_set_value(slider, 50, LV_ANIM_OFF); // Without animation

// Screen transition
lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
```

---

**Remember:**
- Always call `lv_timer_handler()` in `loop()`
- Use static buffers when possible
- Update UI elements in `loop()`, not in interrupt handlers
- Check memory usage during development
- Use Serial output for debugging
