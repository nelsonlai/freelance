#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <lvgl.h>

// Screen IDs
typedef enum {
    SCREEN_MAIN,
    SCREEN_CLOCK_ANALOG,
    SCREEN_CLOCK_DIGITAL,
    SCREEN_TEMPERATURE,
    SCREEN_HEART_RATE,
    SCREEN_SPO2,
    SCREEN_SETTINGS
} screen_id_t;

class UIManager {
public:
    UIManager();
    void init();
    void update();
    void showScreen(screen_id_t screen);
    void updateClock();
    void updateTemperature(float temp);
    void updateHeartRate(uint8_t hr);
    void updateSpO2(uint8_t spo2);
    screen_id_t getCurrentScreen() { return _currentScreen; }
    
private:
    static UIManager *_instance;
    lv_obj_t *_mainScreen;
    lv_obj_t *_clockAnalogScreen;
    lv_obj_t *_clockDigitalScreen;
    lv_obj_t *_temperatureScreen;
    lv_obj_t *_heartRateScreen;
    lv_obj_t *_spo2Screen;
    lv_obj_t *_settingsScreen;
    
    // Clock widgets
    lv_obj_t *_analogClock;
    lv_obj_t *_hourHand;
    lv_obj_t *_minuteHand;
    lv_obj_t *_secondHand;
    lv_obj_t *_digitalClockLabel;
    
    // Data display labels
    lv_obj_t *_tempLabel;
    lv_obj_t *_hrLabel;
    lv_obj_t *_spo2Label;
    
    // Settings widgets
    lv_obj_t *_brightnessSlider;
    lv_obj_t *_clockFormatSwitch;
    lv_obj_t *_tempUnitSwitch;
    
    screen_id_t _currentScreen;
    
    void createMainScreen();
    void createClockAnalogScreen();
    void createClockDigitalScreen();
    void createTemperatureScreen();
    void createHeartRateScreen();
    void createSpO2Screen();
    void createSettingsScreen();
    
    static void mainBtnEventHandler(lv_event_t *e);
    static void settingsBtnEventHandler(lv_event_t *e);
    static void backBtnEventHandler(lv_event_t *e);
    static void clockFormatChangeHandler(lv_event_t *e);
    static void brightnessChangeHandler(lv_event_t *e);
    static void tempUnitChangeHandler(lv_event_t *e);
    
    void drawAnalogClock();
    void updateAnalogClock();
    void updateDigitalClock();
};

#endif
