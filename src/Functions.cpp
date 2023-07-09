#include <Arduino.h>
#include <GyverTimer.h>
#include "Config.h"
#include "Functions.h"
#include "CO2.h"
#include "Led.h"
#include "BME.h"
#include "Button.h"
#include "RTCTime.h"
#include "Display.h"
#include "Plot.h"
#include "Data.h"
#include "Rain.h"
#include "MQTT.h"

AllSensors CurrentSensors;

AllSensors historyHourly[HISTORY_LENGTH], historyDaily[HISTORY_LENGTH];

static const char *dayNames[] = {
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat",
};

enum DisplayMode {
    DISPLAY_MODE_YEAR = 0,
    DISPLAY_MODE_DAY_OF_WEEK = 1,
    DISPLAY_MODE_SECONDS = 2,
};
GTimer_ms hourPlotTimer((long) 4 * 60 * 1000);         // 4 minutes
GTimer_ms dayPlotTimer((long) 1.6 * 60 * 60 * 1000);   // 1.6 hours

void updateCO2Led(bool tick) {
    switch (CurrentSensors.co2Level) {
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

DateTime lastDateTime = DateTime();

void updateDate(uint16_t year, uint8_t month, uint8_t day, uint8_t dayOfTheWeek) {
    lcdSetCursor(15, 0);
    if (day < 10) lcdPrint("0");
    lcdPrint(String(day));
    lcdPrint(".");
    if (month < 10) lcdPrint("0");
    lcdPrint(String(month));

    if (DISP_MODE == DISPLAY_MODE_YEAR) {
        lcdSetCursor(16, 1);
        lcdPrint(String(year));
    } else if (DISP_MODE == DISPLAY_MODE_DAY_OF_WEEK) {
        lcdSetCursor(16, 1);
        lcdPrint(dayNames[dayOfTheWeek]);
    }
}

uint8_t lastYear = -1;
uint8_t lastMonth = -1;
uint8_t lastDay = -1;
uint8_t lastHour = -1;
uint8_t lastMinute = -1;
uint8_t lastSecond = -1;
uint8_t lastDayOfTheWeek = -1;

void updateClock(bool dotFlag) {
    DateTime now = getNow();
    uint16_t year = now.year();
    uint8_t month = now.month();
    uint8_t day = now.day();
    uint8_t hour = now.hour();
    uint8_t minute = now.minute();
    uint8_t second = now.second();
    uint8_t dayOfTheWeek = now.dayOfTheWeek();
    lcdLoadClock();
    if (lastHour != hour || lastMinute != minute) {
        lcdDrawClock(hour, minute, 0, 0);
    }
    if (DISP_MODE == DISPLAY_MODE_SECONDS && lastSecond != second) {
        lcdSetCursor(16, 1);
        if (second < 10) lcdPrint("0");
        lcdPrint(String(second));
    }

    if (lastYear != year
        || lastMonth != month
        || lastDay != day
        || lastDayOfTheWeek != dayOfTheWeek) {
        updateDate(year, month, day, dayOfTheWeek);
    }

    drawdots(7, 0, dotFlag);

    lastYear = year;
    lastMonth = month;
    lastDay = day;
    lastHour = hour;
    lastMinute = minute;
    lastSecond = second;
    lastDayOfTheWeek = dayOfTheWeek;
}

void drawSensors() {
    lcdSetCursor(0, 2);
    lcdPrint(String(CurrentSensors.temperature, 1));
    lcdWrite(223);
    lcdSetCursor(6, 2);
    lcdPrint(" " + String(CurrentSensors.humidity) + "%  ");

    if (CurrentSensors.co2Value < 1000) lcdPrint(" ");
    lcdPrint(String(CurrentSensors.co2Value) + " ppm");

    lcdSetCursor(0, 3);
    lcdPrint(String((int) CurrentSensors.pressure) + " mm  rain ");
    lcdPrint(F("       "));
    lcdSetCursor(13, 3);
    lcdPrint(String(CurrentSensors.rain) + "%");
}

boolean timerTickState = false;
METEO_MODE lastMode = METEO_MODE_CLOCK;

void timerTick() {
    timerTickState = !timerTickState;
    METEO_MODE mode = getMeteoMode();
    if (mode == METEO_MODE_CLOCK) {
        updateClock(timerTickState);
    }
    if (mode != lastMode) {
        if (mode == METEO_MODE_CLOCK) {
            drawSensors();
        } else {
            redrawPlot(mode, historyHourly, historyDaily);
        }
    }
    updateCO2Led(timerTickState);
    lastMode = mode;
}


void copyStructure(const AllSensors &source, AllSensors &destination) {
    memcpy(&destination, &source, sizeof(AllSensors));
}

void publishValue(AllSensors value) {
    mqttPublish("co2", String(value.co2Value));
    mqttPublish("temperature", String(value.temperature));
    mqttPublish("pressure", String(value.pressure));
    mqttPublish("humidity", String(value.humidity));
    mqttPublish("rain", String(value.rain));
}

void publishToMqtt() {
    if (mqttIfReconnect()) {
        publishValue(CurrentSensors);
    }
}

void updateSensors() {
    AllSensors newValues;
    newValues.co2Level = getCO2Level();
    newValues.co2Value = getCO2();
    BMEValue bmeValue = getBMEValue();
    newValues.pressure = convertPressure(bmeValue.pressure, PRESSURE_UNIT_MM);
    newValues.temperature = bmeValue.temperature;
    newValues.humidity = bmeValue.humidity;
    newValues.rain = getRainValue();

    copyStructure(newValues, CurrentSensors);

    if (hourPlotTimer.isReady()) {
        for (byte i = 0; i < HISTORY_LENGTH - 1; i++) {
            historyHourly[i] = historyHourly[i + 1];
        }
        copyStructure(newValues, historyHourly[HISTORY_LENGTH - 1]);
    }

    if (dayPlotTimer.isReady()) {
        long averTemp = 0, averHum = 0, averPress = 0, averCO2 = 0;

        for (byte i = 0; i < 15; i++) {
            averTemp += historyHourly[i].temperature;
            averHum += historyHourly[i].humidity;
            averPress += historyHourly[i].pressure;
            averCO2 += historyHourly[i].co2Value;
        }
        AllSensors lastDayAverage;
        lastDayAverage.temperature = averTemp / HISTORY_LENGTH;
        lastDayAverage.humidity = averHum / HISTORY_LENGTH;
        lastDayAverage.pressure = averPress / HISTORY_LENGTH;
        lastDayAverage.co2Value = averCO2 / HISTORY_LENGTH;

        for (byte i = 0; i < HISTORY_LENGTH - 1; i++) {
            historyDaily[i] = historyDaily[i + 1];
        }
        copyStructure(lastDayAverage, historyDaily[HISTORY_LENGTH - 1]);
    }

    METEO_MODE mode = getMeteoMode();
    if (mode == METEO_MODE_CLOCK) drawSensors();
}