#include "Plot.h"
#include "Display.h"
#include "Button.h"


void drawPlot(byte pos, byte row, byte width, byte height, int min_val, int max_val, int *plot_array, String label) {
    int max_value = -32000;
    int min_value = 32000;

    for (byte i = 0; i < 15; i++) {
        if (plot_array[i] > max_value) max_value = plot_array[i];
        if (plot_array[i] < min_value) min_value = plot_array[i];
    }
    lcdSetCursor(16, 0);
    lcdPrint(String(max_value));
    lcdSetCursor(16, 1);
    lcdPrint(label);
    lcdSetCursor(16, 2);
    lcdPrint(String(plot_array[14]));
    lcdSetCursor(16, 3);
    lcdPrint(String(min_value));

    for (byte i = 0; i < width; i++) {
        int fill_val = plot_array[i];
        fill_val = constrain(fill_val, min_val, max_val);
        byte infill, fract;
        if (plot_array[i] > min_val)
            infill = floor((float) (plot_array[i] - min_val) / (max_val - min_val) * height * 10);
        else infill = 0;
        fract = (float) (infill % 10) * 8 / 10;
        infill = infill / 10;

        for (byte n = 0; n < height; n++) {
            if (n < infill && infill > 0) {
                lcdSetCursor(i, (row - n));
                lcdWrite(0);
            }
            if (n >= infill) {
                lcdSetCursor(i, (row - n));
                if (fract > 0) lcdWrite(fract);
                else lcdWrite(16);
                for (byte k = n + 1; k < height; k++) {
                    lcdSetCursor(i, (row - k));
                    lcdWrite(16);
                }
                break;
            }
        }
    }
}

void redrawPlot(METEO_MODE mode, AllSensors *hourly, AllSensors *daily) {
    lcdClear();
    lcdLoadPlot();
    int values[HISTORY_LENGTH];
    switch (mode) {
        case METEO_MODE_TEMP_HOURLY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = hourly[i].temperature;
            }
            drawPlot(0, 3, 15, 4, TEMP_MIN, TEMP_MAX, (int *) values, "t hr");
            break;
        case METEO_MODE_TEMP_DAILY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = daily[i].temperature;
            }
            drawPlot(0, 3, 15, 4, TEMP_MIN, TEMP_MAX, (int *) values, "t day");
            break;
        case METEO_MODE_HUM_HOURLY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = hourly[i].humidity;
            }
            drawPlot(0, 3, 15, 4, HUM_MIN, HUM_MAX, (int *) values, "h hr");
            break;
        case METEO_MODE_HUM_DAILY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = daily[i].humidity;
            }
            drawPlot(0, 3, 15, 4, HUM_MIN, HUM_MAX, (int *) values, "h day");
            break;
        case METEO_MODE_PRESS_HOURLY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = hourly[i].pressure;
            }
            drawPlot(0, 3, 15, 4, PRESS_MIN, PRESS_MAX, (int *) values, "p hr");
            break;
        case METEO_MODE_PRESS_DAILY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = daily[i].pressure;
            }
            drawPlot(0, 3, 15, 4, PRESS_MIN, PRESS_MAX, (int *) values, "p day");
            break;
        case METEO_MODE_CO2_HOURLY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = hourly[i].co2Value;
            }
            drawPlot(0, 3, 15, 4, CO2_MIN, CO2_MAX, (int *) values, "c hr");
            break;
        case METEO_MODE_CO2_DAILY:
            for (size_t i = 0; i < HISTORY_LENGTH; ++i) {
                values[i] = daily[i].co2Value;
            }
            drawPlot(0, 3, 15, 4, CO2_MIN, CO2_MAX, (int *) values, "c day");
            break;
        case METEO_MODE_CLOCK:
            break;
    }
}