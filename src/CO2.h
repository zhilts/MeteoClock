#ifndef METEO_CLOCK_CO2_H
#define METEO_CLOCK_CO2_H

#include <Arduino.h>

void setupCO2();
byte getCO2Status();
int getCO2();
String getCO2DebugSting();

enum CO2_LEVEL {
    CO2_LEVEL_GOOD, CO2_LEVEL_WARNING, CO2_LEVEL_ALERT,
};

CO2_LEVEL getCO2Level();

#endif //METEO_CLOCK_CO2_H
