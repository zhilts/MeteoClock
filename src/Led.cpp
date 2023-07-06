#include <Arduino.h>
#include "Led.h"

#include "Config.h"

#if (LED_MODE == 0)
const int LED_ON = 255;
const int LED_OFF = 0;
#else
int LED_ON = 0;
int LED_OFF = 255;
#endif

RGB_COLOR currentValue;

void rgbSetValue(RGB_COLOR color) {
    switch (color) {
        case RGB_COLOR_OFF:
            analogWrite(LED_R, LED_OFF);
            analogWrite(LED_G, LED_OFF);
            analogWrite(LED_B, LED_OFF);
            break;
        case RGB_COLOR_RED:
            analogWrite(LED_R, LED_ON);
            analogWrite(LED_G, LED_OFF);
            analogWrite(LED_B, LED_OFF);
            break;
        case RGB_COLOR_GREEN:
            analogWrite(LED_R, LED_OFF);
            analogWrite(LED_G, LED_ON);
            analogWrite(LED_B, LED_OFF);
            break;
        case RGB_COLOR_BLUE:
            analogWrite(LED_R, LED_OFF);
            analogWrite(LED_G, LED_OFF);
            analogWrite(LED_B, LED_ON);
            break;
        case RGB_COLOR_YELLOW:
            analogWrite(LED_R, LED_ON);
            analogWrite(LED_G, LED_ON);
            analogWrite(LED_B, LED_OFF);
            break;
    }
    currentValue = color;
}

RGB_COLOR rgbGetValue() {
    return currentValue;
}

void setupRGB() {
    pinMode(LED_COM, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
#if (LED_MODE == 0)
    analogWrite(LED_COM, 0);
#else
    analogWrite(LED_COM, 255);
#endif
    rgbSetValue(RGB_COLOR_OFF);
}