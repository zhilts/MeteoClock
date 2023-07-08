#include <Arduino.h>
#include <GyverButton.h>
#include "Config.h"
#include "Button.h"
#include "Log.h"

#define LOW_PULL 1
#define NORM_OPEN 0

GButton button(TOUCH_PIN, LOW_PULL, NORM_OPEN);

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

void setMeteoMode(METEO_MODE mode) {
    currentMode = static_cast<METEO_MODE>(mode % METE_MODE_LENGTH);
    log("[Button] Set mode: " + String(currentMode));
}

void buttonTick() {
    button.tick();
    if (button.isClick()) {
        METEO_MODE newMode = static_cast<METEO_MODE>(getMeteoMode() + 1);
        setMeteoMode(newMode);
    }
    if (button.isHolded()) {
        setMeteoMode(METEO_MODE_CLOCK);
    }
}