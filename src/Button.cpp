#include <Arduino.h>
#include "Config.h"
#include "Button.h"

void setupButton() {
    pinMode(TOUCH_PIN, INPUT);
}

int buttonGetValue() {
    return digitalRead(TOUCH_PIN);
}

METEO_MODE currentMode = METEO_MODE_CLOCK;

METEO_MODE getMeteoMode() {
    return currentMode;
}