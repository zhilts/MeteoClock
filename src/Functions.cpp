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
    int co2Value;
    float pressure;
    float temperature;
    byte humidity;
} AllSensors;

static const char *dayNames[] = {
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat",
};

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

uint8_t lastHour = -1;
uint8_t lastMin = -1;
uint8_t lastSec = -1;

void updateDate(DateTime now) {
    lcdSetCursor(15, 0);
    int day = now.day();
    int month = now.month();
    if (day < 10) lcdPrint("0");
    lcdPrint(String(day));
    lcdPrint(".");
    if (month < 10) lcdPrint("0");
    lcdPrint(String(month));

    if (DISP_MODE == 0) {
        lcdSetCursor(16, 1);
        lcdPrint(String(now.year()));
    } else if (DISP_MODE == 1) {
        lcdSetCursor(16, 1);
        int dayofweek = now.dayOfTheWeek();
        lcdPrint(dayNames[dayofweek]);
    }
}

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
    if (lastHour != hrs) {
        updateDate(now);
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

void drawSensors() {
    lcdSetCursor(0, 2);
    lcdPrint(String(AllSensors.temperature, 1));
    lcdWrite(223);
    lcdSetCursor(6, 2);
    lcdPrint(" " + String(AllSensors.humidity) + "%  ");

    if (AllSensors.co2Value < 1000) lcdPrint(" ");
    lcdPrint(String(AllSensors.co2Value) + " ppm");

    lcdSetCursor(0, 3);
    lcdPrint(String((int)AllSensors.pressure) + " mm  rain ");
    lcdPrint(F("       "));
    lcdSetCursor(13, 3);
//    lcdPrint(String(dispRain) + "%");
    lcdPrint("50 %");
}

void updateSensors() {
    AllSensors.co2Level = getCO2Level();
    AllSensors.co2Value = getCO2();
    BMEValue bmeValue = getBMEValue();
    AllSensors.pressure = convertPressure(bmeValue.pressure, PRESSURE_UNIT_MM);
    AllSensors.temperature = bmeValue.temperature;
    AllSensors.humidity = bmeValue.humidity;

    METEO_MODE mode = getMeteoMode();
    if (mode == METEO_MODE_CLOCK) drawSensors();
}