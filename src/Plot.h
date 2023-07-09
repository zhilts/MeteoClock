#ifndef METEO_CLOCK_PLOT_H
#define METEO_CLOCK_PLOT_H

#include "Data.h"
#include "Button.h"

#define HISTORY_LENGTH 15
#define TEMP_MIN 15
#define TEMP_MAX 35
#define HUM_MIN 0
#define HUM_MAX 100
#define PRESS_MIN (-100)
#define PRESS_MAX 100
#define CO2_MIN 300
#define CO2_MAX 2000
#define RAIN_MIN -100
#define RAIN_MAX 100

void redrawPlot(METEO_MODE mode, AllSensors *hourly, AllSensors *daily);

#endif //METEO_CLOCK_PLOT_H
