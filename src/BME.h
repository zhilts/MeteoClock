#ifndef METEO_CLOCK_TEMPERATURE_H
#define METEO_CLOCK_TEMPERATURE_H

//#include <Arduino.h>

void setupBME();

struct BMEValue {
    float pressure;
    float temperature;
    byte humidity;
};

BMEValue getBMEValue();

String bmeGetDebugString();

#endif //METEO_CLOCK_TEMPERATURE_H
