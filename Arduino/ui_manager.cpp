#include "ui_manager.h"
#include "display_config.h"
#include <time.h>
#include <math.h>
#include <Arduino.h>

UIManager *UIManager::_instance = nullptr;

UIManager::UIManager() {
    _instance = this;
    _mainScreen = nullptr;
    _clockAnalogScreen = nullptr;
    _clockDigitalScreen = nullptr;
    _temperatureScreen = nullptr;
    _heartRateScreen = nullptr;
    _spo2Screen = nullptr;
    _settingsScreen = nullptr;
    _analogClock = nullptr;
    _hourHand = nullptr;
    _minuteHand = nullptr;
    _secondHand = nullptr;
    _digitalClockLabel = nullptr;
    _tempLabel = nullptr;
    _hrLabel = nullptr;
    _spo2Label = nullptr;
    _brightnessSlider = nullptr;
    _clockFormatSwitch = nullptr;
    _tempUnitSwitch = nullptr;
    _currentScreen = SCREEN_MAIN;
}

void UIManager::init() {
    Serial.println("[UI] Creating user interface screens...");
    
    Serial.print("[UI]   Creating main screen... ");
    createMainScreen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating analog clock screen... ");
    createClockAnalogScreen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating digital clock screen... ");
    createClockDigitalScreen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating temperature screen... ");
    createTemperatureScreen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating heart rate screen... ");
    createHeartRateScreen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating SpO2 screen... ");
    createSpO2Screen();
    Serial.println("OK");
    
    Serial.print("[UI]   Creating settings screen... ");
    createSettingsScreen();
    Serial.println("OK");
    
    Serial.print("[UI] Loading main screen... ");
    lv_scr_load(_mainScreen);
    _currentScreen = SCREEN_MAIN;
    Serial.println("OK");
    Serial.println("[UI] UI initialization complete - Main menu displayed");
}

void UIManager::createMainScreen() {
    _mainScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_mainScreen, lv_color_hex(0x000000), 0);
    
    // Title
    lv_obj_t *title = lv_label_create(_mainScreen);
    lv_label_set_text(title, "Health Monitor");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    
    // Clock Button
    lv_obj_t *clockBtn = lv_btn_create(_mainScreen);
    lv_obj_set_size(clockBtn, 200, 50);
    lv_obj_align(clockBtn, LV_ALIGN_CENTER, 0, -80);
    lv_obj_add_event_cb(clockBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_CLOCK_ANALOG);
    
    lv_obj_t *clockLabel = lv_label_create(clockBtn);
    lv_label_set_text(clockLabel, "Clock");
    lv_obj_center(clockLabel);
    
    // Temperature Button
    lv_obj_t *tempBtn = lv_btn_create(_mainScreen);
    lv_obj_set_size(tempBtn, 200, 50);
    lv_obj_align(tempBtn, LV_ALIGN_CENTER, 0, -20);
    lv_obj_add_event_cb(tempBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_TEMPERATURE);
    
    lv_obj_t *tempLabel = lv_label_create(tempBtn);
    lv_label_set_text(tempLabel, "Temperature");
    lv_obj_center(tempLabel);
    
    // Heart Rate Button
    lv_obj_t *hrBtn = lv_btn_create(_mainScreen);
    lv_obj_set_size(hrBtn, 200, 50);
    lv_obj_align(hrBtn, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(hrBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_HEART_RATE);
    
    lv_obj_t *hrLabel = lv_label_create(hrBtn);
    lv_label_set_text(hrLabel, "Heart Rate");
    lv_obj_center(hrLabel);
    
    // SpO2 Button
    lv_obj_t *spo2Btn = lv_btn_create(_mainScreen);
    lv_obj_set_size(spo2Btn, 200, 50);
    lv_obj_align(spo2Btn, LV_ALIGN_CENTER, 0, 100);
    lv_obj_add_event_cb(spo2Btn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_SPO2);
    
    lv_obj_t *spo2Label = lv_label_create(spo2Btn);
    lv_label_set_text(spo2Label, "Blood Oxygen");
    lv_obj_center(spo2Label);
    
    // Settings Button
    lv_obj_t *settingsBtn = lv_btn_create(_mainScreen);
    lv_obj_set_size(settingsBtn, 60, 60);
    lv_obj_align(settingsBtn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_add_event_cb(settingsBtn, settingsBtnEventHandler, LV_EVENT_CLICKED, NULL);
    
    lv_obj_t *settingsIcon = lv_label_create(settingsBtn);
    lv_label_set_text(settingsIcon, LV_SYMBOL_SETTINGS);
    lv_obj_center(settingsIcon);
}

void UIManager::createClockAnalogScreen() {
    _clockAnalogScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_clockAnalogScreen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_clockAnalogScreen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Switch to digital button
    lv_obj_t *switchBtn = lv_btn_create(_clockAnalogScreen);
    lv_obj_set_size(switchBtn, 100, 40);
    lv_obj_align(switchBtn, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(switchBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_CLOCK_DIGITAL);
    
    lv_obj_t *switchLabel = lv_label_create(switchBtn);
    lv_label_set_text(switchLabel, "Digital");
    lv_obj_center(switchLabel);
    
    // Analog clock container
    _analogClock = lv_obj_create(_clockAnalogScreen);
    lv_obj_set_size(_analogClock, 200, 200);
    lv_obj_align(_analogClock, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(_analogClock, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(_analogClock, 2, 0);
    lv_obj_set_style_border_color(_analogClock, lv_color_hex(0xFFFFFF), 0);
    lv_obj_clear_flag(_analogClock, LV_OBJ_FLAG_SCROLLABLE);
    
    // Clock center
    lv_obj_t *center = lv_obj_create(_analogClock);
    lv_obj_set_size(center, 10, 10);
    lv_obj_align(center, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(center, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(center, LV_RADIUS_CIRCLE, 0);
    lv_obj_clear_flag(center, LV_OBJ_FLAG_SCROLLABLE);
    
    // Hour hand
    _hourHand = lv_obj_create(_analogClock);
    lv_obj_set_size(_hourHand, 4, 50);
    lv_obj_align(_hourHand, LV_ALIGN_CENTER, 0, -25);
    lv_obj_set_style_bg_color(_hourHand, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(_hourHand, 2, 0);
    lv_obj_set_style_pad_all(_hourHand, 0, 0);
    lv_obj_clear_flag(_hourHand, LV_OBJ_FLAG_SCROLLABLE);
    
    // Minute hand
    _minuteHand = lv_obj_create(_analogClock);
    lv_obj_set_size(_minuteHand, 3, 70);
    lv_obj_align(_minuteHand, LV_ALIGN_CENTER, 0, -35);
    lv_obj_set_style_bg_color(_minuteHand, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(_minuteHand, 2, 0);
    lv_obj_clear_flag(_minuteHand, LV_OBJ_FLAG_SCROLLABLE);
    
    // Second hand
    _secondHand = lv_obj_create(_analogClock);
    lv_obj_set_size(_secondHand, 2, 80);
    lv_obj_align(_secondHand, LV_ALIGN_CENTER, 0, -40);
    lv_obj_set_style_bg_color(_secondHand, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_radius(_secondHand, 1, 0);
    lv_obj_clear_flag(_secondHand, LV_OBJ_FLAG_SCROLLABLE);
    
    // Hour markers
    for (int i = 0; i < 12; i++) {
        float angle = (i * 30.0 - 90.0) * 3.14159 / 180.0;
        int x = 100 + 85 * cos(angle);
        int y = 100 + 85 * sin(angle);
        
        lv_obj_t *marker = lv_obj_create(_analogClock);
        lv_obj_set_size(marker, 4, 4);
        lv_obj_set_pos(marker, x - 2, y - 2);
        lv_obj_set_style_bg_color(marker, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_radius(marker, LV_RADIUS_CIRCLE, 0);
        lv_obj_clear_flag(marker, LV_OBJ_FLAG_SCROLLABLE);
    }
}

void UIManager::createClockDigitalScreen() {
    _clockDigitalScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_clockDigitalScreen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_clockDigitalScreen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Switch to analog button
    lv_obj_t *switchBtn = lv_btn_create(_clockDigitalScreen);
    lv_obj_set_size(switchBtn, 100, 40);
    lv_obj_align(switchBtn, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(switchBtn, mainBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_CLOCK_ANALOG);
    
    lv_obj_t *switchLabel = lv_label_create(switchBtn);
    lv_label_set_text(switchLabel, "Analog");
    lv_obj_center(switchLabel);
    
    // Digital clock label
    _digitalClockLabel = lv_label_create(_clockDigitalScreen);
    lv_label_set_text(_digitalClockLabel, "00:00:00");
    lv_obj_set_style_text_color(_digitalClockLabel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(_digitalClockLabel, &lv_font_montserrat_48, 0);
    lv_obj_align(_digitalClockLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Date label
    lv_obj_t *dateLabel = lv_label_create(_clockDigitalScreen);
    lv_label_set_text(dateLabel, "Mon, Jan 01 2024");
    lv_obj_set_style_text_color(dateLabel, lv_color_hex(0xAAAAAA), 0);
    lv_obj_set_style_text_font(dateLabel, &lv_font_montserrat_18, 0);
    lv_obj_align(dateLabel, LV_ALIGN_CENTER, 0, 60);
}

void UIManager::createTemperatureScreen() {
    _temperatureScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_temperatureScreen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_temperatureScreen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Title
    lv_obj_t *title = lv_label_create(_temperatureScreen);
    lv_label_set_text(title, "Temperature");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 60);
    
    // Temperature label
    _tempLabel = lv_label_create(_temperatureScreen);
    lv_label_set_text(_tempLabel, "--.- °C");
    lv_obj_set_style_text_color(_tempLabel, lv_color_hex(0xFF6B00), 0);
    lv_obj_set_style_text_font(_tempLabel, &lv_font_montserrat_48, 0);
    lv_obj_align(_tempLabel, LV_ALIGN_CENTER, 0, 0);
}

void UIManager::createHeartRateScreen() {
    _heartRateScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_heartRateScreen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_heartRateScreen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Title
    lv_obj_t *title = lv_label_create(_heartRateScreen);
    lv_label_set_text(title, "Heart Rate");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 60);
    
    // Heart rate label
    _hrLabel = lv_label_create(_heartRateScreen);
    lv_label_set_text(_hrLabel, "-- BPM");
    lv_obj_set_style_text_color(_hrLabel, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_text_font(_hrLabel, &lv_font_montserrat_48, 0);
    lv_obj_align(_hrLabel, LV_ALIGN_CENTER, 0, 0);
    
    // Instruction label
    lv_obj_t *instruction = lv_label_create(_heartRateScreen);
    lv_label_set_text(instruction, "Place finger on sensor");
    lv_obj_set_style_text_color(instruction, lv_color_hex(0xAAAAAA), 0);
    lv_obj_set_style_text_font(instruction, &lv_font_montserrat_14, 0);
    lv_obj_align(instruction, LV_ALIGN_BOTTOM_MID, 0, -40);
}

void UIManager::createSpO2Screen() {
    _spo2Screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_spo2Screen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_spo2Screen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Title
    lv_obj_t *title = lv_label_create(_spo2Screen);
    lv_label_set_text(title, "Blood Oxygen");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 60);
    
    // SpO2 label
    _spo2Label = lv_label_create(_spo2Screen);
    lv_label_set_text(_spo2Label, "-- %");
    lv_obj_set_style_text_color(_spo2Label, lv_color_hex(0x00FF00), 0);
    lv_obj_set_style_text_font(_spo2Label, &lv_font_montserrat_48, 0);
    lv_obj_align(_spo2Label, LV_ALIGN_CENTER, 0, 0);
    
    // Instruction label
    lv_obj_t *instruction = lv_label_create(_spo2Screen);
    lv_label_set_text(instruction, "Place finger on sensor");
    lv_obj_set_style_text_color(instruction, lv_color_hex(0xAAAAAA), 0);
    lv_obj_set_style_text_font(instruction, &lv_font_montserrat_14, 0);
    lv_obj_align(instruction, LV_ALIGN_BOTTOM_MID, 0, -40);
}

void UIManager::createSettingsScreen() {
    _settingsScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(_settingsScreen, lv_color_hex(0x000000), 0);
    
    // Back button
    lv_obj_t *backBtn = lv_btn_create(_settingsScreen);
    lv_obj_set_size(backBtn, 60, 40);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, backBtnEventHandler, LV_EVENT_CLICKED, (void*)SCREEN_MAIN);
    
    lv_obj_t *backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    
    // Title
    lv_obj_t *title = lv_label_create(_settingsScreen);
    lv_label_set_text(title, "Settings");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    
    // Brightness slider
    lv_obj_t *brightnessLabel = lv_label_create(_settingsScreen);
    lv_label_set_text(brightnessLabel, "Brightness");
    lv_obj_set_style_text_color(brightnessLabel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(brightnessLabel, LV_ALIGN_TOP_LEFT, 20, 70);
    
    _brightnessSlider = lv_slider_create(_settingsScreen);
    lv_obj_set_width(_brightnessSlider, 200);
    lv_obj_align(_brightnessSlider, LV_ALIGN_TOP_LEFT, 20, 100);
    lv_slider_set_range(_brightnessSlider, 10, 100);
    lv_slider_set_value(_brightnessSlider, 80, LV_ANIM_OFF);
    lv_obj_add_event_cb(_brightnessSlider, brightnessChangeHandler, LV_EVENT_VALUE_CHANGED, NULL);
    
    // Clock format switch
    lv_obj_t *clockLabel = lv_label_create(_settingsScreen);
    lv_label_set_text(clockLabel, "Clock Format");
    lv_obj_set_style_text_color(clockLabel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(clockLabel, LV_ALIGN_TOP_LEFT, 20, 140);
    
    _clockFormatSwitch = lv_switch_create(_settingsScreen);
    lv_obj_align(_clockFormatSwitch, LV_ALIGN_TOP_RIGHT, -20, 140);
    lv_obj_add_event_cb(_clockFormatSwitch, clockFormatChangeHandler, LV_EVENT_VALUE_CHANGED, NULL);
    
    lv_obj_t *clockFormatLabel = lv_label_create(_settingsScreen);
    lv_label_set_text(clockFormatLabel, "Analog");
    lv_obj_set_style_text_color(clockFormatLabel, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(clockFormatLabel, LV_ALIGN_TOP_LEFT, 20, 160);
    
    // Temperature unit switch
    lv_obj_t *tempUnitLabel = lv_label_create(_settingsScreen);
    lv_label_set_text(tempUnitLabel, "Temperature Unit");
    lv_obj_set_style_text_color(tempUnitLabel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(tempUnitLabel, LV_ALIGN_TOP_LEFT, 20, 200);
    
    _tempUnitSwitch = lv_switch_create(_settingsScreen);
    lv_obj_align(_tempUnitSwitch, LV_ALIGN_TOP_RIGHT, -20, 200);
    lv_obj_add_event_cb(_tempUnitSwitch, tempUnitChangeHandler, LV_EVENT_VALUE_CHANGED, NULL);
    
    lv_obj_t *tempUnitText = lv_label_create(_settingsScreen);
    lv_label_set_text(tempUnitText, "Celsius");
    lv_obj_set_style_text_color(tempUnitText, lv_color_hex(0xAAAAAA), 0);
    lv_obj_align(tempUnitText, LV_ALIGN_TOP_LEFT, 20, 220);
}

void UIManager::showScreen(screen_id_t screen) {
    lv_obj_t *targetScreen = nullptr;
    const char* screenName = "";
    
    switch (screen) {
        case SCREEN_MAIN:
            targetScreen = _mainScreen;
            screenName = "Main Menu";
            break;
        case SCREEN_CLOCK_ANALOG:
            targetScreen = _clockAnalogScreen;
            screenName = "Analog Clock";
            break;
        case SCREEN_CLOCK_DIGITAL:
            targetScreen = _clockDigitalScreen;
            screenName = "Digital Clock";
            break;
        case SCREEN_TEMPERATURE:
            targetScreen = _temperatureScreen;
            screenName = "Temperature";
            break;
        case SCREEN_HEART_RATE:
            targetScreen = _heartRateScreen;
            screenName = "Heart Rate";
            break;
        case SCREEN_SPO2:
            targetScreen = _spo2Screen;
            screenName = "Blood Oxygen";
            break;
        case SCREEN_SETTINGS:
            targetScreen = _settingsScreen;
            screenName = "Settings";
            break;
    }
    
    if (targetScreen) {
        Serial.print("[UI] Screen change: ");
        switch (_currentScreen) {
            case SCREEN_MAIN: Serial.print("Main Menu"); break;
            case SCREEN_CLOCK_ANALOG: Serial.print("Analog Clock"); break;
            case SCREEN_CLOCK_DIGITAL: Serial.print("Digital Clock"); break;
            case SCREEN_TEMPERATURE: Serial.print("Temperature"); break;
            case SCREEN_HEART_RATE: Serial.print("Heart Rate"); break;
            case SCREEN_SPO2: Serial.print("Blood Oxygen"); break;
            case SCREEN_SETTINGS: Serial.print("Settings"); break;
        }
        Serial.print(" -> ");
        Serial.println(screenName);
        
        lv_scr_load(targetScreen);
        _currentScreen = screen;
    } else {
        Serial.print("[UI] Error: Invalid screen ID: ");
        Serial.println((int)screen);
    }
}

void UIManager::updateClock() {
    updateAnalogClock();
    updateDigitalClock();
}

void UIManager::updateAnalogClock() {
    if (!_analogClock || _currentScreen != SCREEN_CLOCK_ANALOG) {
        return;
    }
    
    time_t now = time(NULL);
    if (now < 0) return;  // Time not set yet
    
    struct tm *timeinfo = localtime(&now);
    if (!timeinfo) return;
    
    int hour = timeinfo->tm_hour % 12;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;
    
    // Calculate angles (in radians)
    float hourAngle = (hour * 30.0 + minute * 0.5 - 90.0) * 3.14159 / 180.0;
    float minuteAngle = (minute * 6.0 - 90.0) * 3.14159 / 180.0;
    float secondAngle = (second * 6.0 - 90.0) * 3.14159 / 180.0;
    
    // Update hour hand position and rotation
    lv_obj_set_style_transform_pivot_x(_hourHand, 2, 0);
    lv_obj_set_style_transform_pivot_y(_hourHand, 25, 0);
    lv_obj_set_style_transform_angle(_hourHand, (int16_t)(hourAngle * 57.3 + 90), 0);
    
    // Update minute hand position and rotation
    lv_obj_set_style_transform_pivot_x(_minuteHand, 1.5, 0);
    lv_obj_set_style_transform_pivot_y(_minuteHand, 35, 0);
    lv_obj_set_style_transform_angle(_minuteHand, (int16_t)(minuteAngle * 57.3 + 90), 0);
    
    // Update second hand position and rotation
    lv_obj_set_style_transform_pivot_x(_secondHand, 1, 0);
    lv_obj_set_style_transform_pivot_y(_secondHand, 40, 0);
    lv_obj_set_style_transform_angle(_secondHand, (int16_t)(secondAngle * 57.3 + 90), 0);
}

void UIManager::updateDigitalClock() {
    if (!_digitalClockLabel || _currentScreen != SCREEN_CLOCK_DIGITAL) {
        return;
    }
    
    time_t now = time(NULL);
    if (now < 0) {
        lv_label_set_text(_digitalClockLabel, "00:00:00");
        return;
    }
    
    struct tm *timeinfo = localtime(&now);
    if (!timeinfo) {
        lv_label_set_text(_digitalClockLabel, "00:00:00");
        return;
    }
    
    char timeStr[20];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", 
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    lv_label_set_text(_digitalClockLabel, timeStr);
}

void UIManager::updateTemperature(float temp) {
    static float lastLoggedTemp = -999;
    
    if (_tempLabel) {
        char tempStr[20];
        snprintf(tempStr, sizeof(tempStr), "%.1f °C", temp);
        lv_label_set_text(_tempLabel, tempStr);
        
        // Log temperature updates (only when value changes significantly)
        if (abs(temp - lastLoggedTemp) > 0.5) {
            Serial.print("[UI] Temperature updated: ");
            Serial.print(temp, 1);
            Serial.println("°C");
            lastLoggedTemp = temp;
        }
    }
}

void UIManager::updateHeartRate(uint8_t hr) {
    static uint8_t lastLoggedHR = 0;
    
    if (_hrLabel) {
        char hrStr[20];
        if (hr > 0) {
            snprintf(hrStr, sizeof(hrStr), "%d BPM", hr);
        } else {
            snprintf(hrStr, sizeof(hrStr), "-- BPM");
        }
        lv_label_set_text(_hrLabel, hrStr);
        
        // Log heart rate updates (only when value changes)
        if (hr != lastLoggedHR) {
            if (hr > 0) {
                Serial.print("[UI] Heart rate updated: ");
                Serial.print(hr);
                Serial.println(" BPM");
            } else if (lastLoggedHR > 0) {
                Serial.println("[UI] Heart rate: No valid reading (waiting for finger)");
            }
            lastLoggedHR = hr;
        }
    }
}

void UIManager::updateSpO2(uint8_t spo2) {
    static uint8_t lastLoggedSpO2 = 0;
    
    if (_spo2Label) {
        char spo2Str[20];
        if (spo2 > 0) {
            snprintf(spo2Str, sizeof(spo2Str), "%d %%", spo2);
        } else {
            snprintf(spo2Str, sizeof(spo2Str), "-- %%");
        }
        lv_label_set_text(_spo2Label, spo2Str);
        
        // Log SpO2 updates (only when value changes)
        if (spo2 != lastLoggedSpO2) {
            if (spo2 > 0) {
                Serial.print("[UI] SpO2 updated: ");
                Serial.print(spo2);
                Serial.println("%");
            } else if (lastLoggedSpO2 > 0) {
                Serial.println("[UI] SpO2: No valid reading (waiting for finger)");
            }
            lastLoggedSpO2 = spo2;
        }
    }
}

void UIManager::update() {
    // Update clock if on clock screen
    if (_currentScreen == SCREEN_CLOCK_ANALOG || _currentScreen == SCREEN_CLOCK_DIGITAL) {
        updateClock();
    }
}

void UIManager::mainBtnEventHandler(lv_event_t *e) {
    if (!_instance) return;
    screen_id_t screen = (screen_id_t)lv_event_get_user_data(e);
    _instance->showScreen(screen);
}

void UIManager::settingsBtnEventHandler(lv_event_t *e) {
    if (!_instance) return;
    _instance->showScreen(SCREEN_SETTINGS);
}

void UIManager::backBtnEventHandler(lv_event_t *e) {
    if (!_instance) return;
    screen_id_t targetScreen = (screen_id_t)lv_event_get_user_data(e);
    _instance->showScreen(targetScreen);
}

void UIManager::clockFormatChangeHandler(lv_event_t *e) {
    // Handle clock format change
}

void UIManager::brightnessChangeHandler(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    // Adjust display brightness
    analogWrite(DISPLAY_BL, map(value, 10, 100, 0, 255));
}

void UIManager::tempUnitChangeHandler(lv_event_t *e) {
    // Handle temperature unit change
}
