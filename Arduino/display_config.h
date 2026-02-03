#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

// Display Configuration
// Adjust these based on your display hardware
#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240
#define DISPLAY_MOSI   23
#define DISPLAY_SCLK   18
#define DISPLAY_CS     5
#define DISPLAY_DC     2
#define DISPLAY_RST    4
#define DISPLAY_BL     15

// Touch Configuration (if using touch screen)
#define TOUCH_SDA      21
#define TOUCH_SCL      22
#define TOUCH_INT      0

// I2C Configuration for MAX30102
#define I2C_SDA        21
#define I2C_SCL        22

#endif
