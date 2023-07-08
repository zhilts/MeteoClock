#ifndef METEO_CLOCK_DATA_H
#define METEO_CLOCK_DATA_H

#include "CO2.h"

struct AllSensors {
    CO2_LEVEL co2Level = CO2_LEVEL_UNDEFINED;
    int co2Value = 0;
    float pressure = 0;
    float temperature = 0;
    byte humidity = 0;
    int rain = 0;
};

#endif //METEO_CLOCK_DATA_H
