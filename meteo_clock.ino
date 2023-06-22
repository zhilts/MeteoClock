#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoOTA.h>
#include <esp_task_wdt.h>
#include "Config.h"
#include "Secrets.h"
#include "Pins.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, I2C_A, I2C_B);

void setupLCD() {
    lcd.init();
    lcd.backlight();
}

void setupOTA() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    ArduinoOTA
            .onError([](ota_error_t error) {
                esp_restart();
            });

    ArduinoOTA.setHostname(RIG_IDENTIFIER);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();
}

void setup() {
    setupLCD();
    setupOTA();
    pinMode(TOUCH_PIN, INPUT);
}

void loop() {
    ArduinoOTA.handle();
    int touchValue = digitalRead(TOUCH_PIN);

    if (touchValue == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("Touch Detected");
    } else {
        lcd.clear();
    }
}
