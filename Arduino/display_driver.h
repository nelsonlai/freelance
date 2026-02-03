#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include <lvgl.h>
#include "display_config.h"

class DisplayDriver {
public:
    DisplayDriver();
    bool init();
    void flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
    void setBrightness(uint8_t brightness);
    
private:
    void initDisplay();
    void initTouch();
};

// LVGL display flush callback
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

// LVGL input device callback
void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);

#endif
