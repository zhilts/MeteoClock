#include <Arduino.h>
#include "Config.h"

void setupButton() {
    pinMode(TOUCH_PIN, INPUT);
}

int buttonGetValue() {
    return digitalRead(TOUCH_PIN);
}