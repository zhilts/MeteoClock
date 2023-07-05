#ifndef METEO_CLOCK_TEMPERATURE_H
#define METEO_CLOCK_TEMPERATURE_H

void setupBME();
float getPressure();
float getTemperature();
byte getHumidity();

String bmeGetDebugString();

#endif //METEO_CLOCK_TEMPERATURE_H
