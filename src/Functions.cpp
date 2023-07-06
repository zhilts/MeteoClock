#include <Arduino.h>
#include "Config.h"
#include "Functions.h"
#include "CO2.h"
#include "Led.h"
#include "BME.h"
#include "Button.h"
#include "RTCTime.h"
#include "Display.h"

struct {
    CO2_LEVEL co2Level;
} AllSensors;

void updateCO2Led(bool tick) {
    switch (AllSensors.co2Level) {
        case CO2_LEVEL_GOOD:
            rgbSetValue(RGB_COLOR_GREEN);
            break;
        case CO2_LEVEL_WARNING:
            rgbSetValue(RGB_COLOR_YELLOW);
            break;
        case CO2_LEVEL_ALERT:
            rgbSetValue(tick ? RGB_COLOR_RED : RGB_COLOR_OFF);
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

uint8_t lastHour = 0;
uint8_t lastMin = -1;
uint8_t lastSec = -1;

void updateClock(bool dotFlag) {
    DateTime now = getNow();
    uint8_t hrs = now.hour();
    uint8_t mins = now.minute();
    uint8_t secs = now.second();
    if (lastHour != hrs || lastMin != mins) {
        lcdDrawClock(hrs, mins, 0, 0);
    }
    if (DISP_MODE == 2 && lastSec != secs) {
        lcdSetCursor(16, 1);
        if (secs < 10) lcdPrint("0");
        lcdPrint(String(secs));
    }

    drawdots(7, 0, dotFlag);

    lastHour = hrs;
    lastMin = mins;
    lastSec = secs;
}

boolean timerTickState = false;
void timerTick() {
    timerTickState = !timerTickState;
    METEO_MODE mode = getMeteoMode();
    if (mode == METEO_MODE_CLOCK) {
        updateClock(timerTickState);
    }
    updateCO2Led(timerTickState);
}

void readSensors() {
    AllSensors.co2Level = getCO2Level();
}