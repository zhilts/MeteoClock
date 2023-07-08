#ifndef METEO_CLOCK_BUTTON_H
#define METEO_CLOCK_BUTTON_H

void setupButton();
int buttonGetValue();

enum METEO_MODE {
    METEO_MODE_CLOCK = 0,
    METEO_MODE_TEMP_HOURLY = 1,
    METEO_MODE_TEMP_DAILY = 2,
    METEO_MODE_HUM_HOURLY = 3,
    METEO_MODE_HUM_DAILY = 4,
    METEO_MODE_PRESS_HOURLY = 5,
    METEO_MODE_PRESS_DAILY = 6,
    METEO_MODE_CO2_HOURLY = 7,
    METEO_MODE_CO2_DAILY = 8,
};

METEO_MODE getMeteoMode();

void setMeteoMode(METEO_MODE mode);

void buttonTick();

#endif //METEO_CLOCK_BUTTON_H
