#include <Arduino.h>
#include "Config.h"
#include "Functions.h"
#include "CO2.h"
#include "Led.h"
#include "BME.h"
#include "Button.h"
#include "RTCTime.h"
#include "Display.h"

void updateCO2() {
    CO2_LEVEL co2Level = getCO2Level();
    switch (co2Level) {
        case CO2_LEVEL_GOOD:
            rgbSetValue(RGB_COLOR_GREEN);
            break;
        case CO2_LEVEL_WARNING:
            rgbSetValue(RGB_COLOR_YELLOW);
            break;
        case CO2_LEVEL_ALERT:
            rgbSetValue(RGB_COLOR_RED);
            break;
    }
}

void drawdots(byte x, byte y, boolean state) {
    byte code;
    if (state) code = 165;
    else code = 32;
    lcdSetCursor(x, y);
    lcdWrite(code);
    lcdSetCursor(x, y + 1);
    lcdWrite(code);
}

boolean dotFlag = false;
uint8_t lastHour = 0;
uint8_t lastMin = -1;
uint8_t lastSec = -1;

void clockTick() {
    METEO_MODE mode = getMeteoMode();
    DateTime now = getNow();
    dotFlag = !dotFlag;
    uint8_t hrs = now.hour();
    uint8_t mins = now.minute();
    uint8_t secs = now.second();
    if (lastHour != hrs || lastMin != mins) {
        if (mode == METEO_MODE_CLOCK) lcdDrawClock(hrs, mins, 0, 0);
    }
    if (DISP_MODE == 2 && mode == METEO_MODE_CLOCK && lastSec != secs) {
        lcdSetCursor(16, 1);
        if (secs < 10) lcdPrint("0");
        lcdPrint(String(secs));
    }
    if (mode == METEO_MODE_CLOCK) drawdots(7, 0, dotFlag);

    lastHour = hrs;
    lastMin = mins;
    lastSec = secs;
    // todo: blink on red
}

void readSensors() {
    updateCO2();
}