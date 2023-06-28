#ifndef METEO_CLOCK_LED_H
#define METEO_CLOCK_LED_H

const int RGB_OFF = 0;
const int RGB_RED = 1;
const int RGB_GREEN = 2;
const int RGB_BLUE = 3;
const int RGB_YELLOW = 4;

void setupRGB();
int rgbGetValue();
void rgbSetValue(int color);

#endif //METEO_CLOCK_LED_H
