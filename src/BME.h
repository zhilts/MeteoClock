#ifndef METEO_CLOCK_TEMPERATURE_H
#define METEO_CLOCK_TEMPERATURE_H

void setupBME();

struct BMEValue {
    float pressure;
    float temperature;
    byte humidity;
};

BMEValue getBMEValue();

String bmeGetDebugString();

enum PressureUnit {
    PRESSURE_UNIT_PA,
    PRESSURE_UNIT_MM,
};

float convertPressure(float value, PressureUnit unit);

#endif //METEO_CLOCK_TEMPERATURE_H
