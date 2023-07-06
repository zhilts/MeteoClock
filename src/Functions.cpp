#include "Functions.h"
#include "CO2.h"
#include "Led.h"

void updateCO2() {
    CO2_LEVEL co2Level = getCO2Level();
    switch (co2Level) {
        case CO2_LEVEL_GOOD:
            rgbSetValue(RGB_COLOR_GREEN);
            break;
        case CO2_LEVEL_WARNING:
            rgbSetValue(RGB_COLOR_YELLOW);
            break;
        case CO2_LEVEL_ALERT:
            rgbSetValue(RGB_COLOR_RED);
            break;
    }
}