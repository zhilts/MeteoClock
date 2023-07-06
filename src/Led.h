#ifndef METEO_CLOCK_LED_H
#define METEO_CLOCK_LED_H

enum RGB_COLOR {
    RGB_COLOR_OFF = 0,
    RGB_COLOR_RED = 1,
    RGB_COLOR_GREEN = 2,
    RGB_COLOR_BLUE = 3,
    RGB_COLOR_YELLOW = 4,
};

void setupRGB();
RGB_COLOR rgbGetValue();
void rgbSetValue(RGB_COLOR color);

#endif //METEO_CLOCK_LED_H
