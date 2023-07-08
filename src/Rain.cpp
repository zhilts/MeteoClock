#include <Arduino.h>
#include "Rain.h"
#include "BME.h"
#include "Log.h"

#define RAIN_HISTORY_LENGTH 6
#define RAIN_APPROX_LENGTH 10
int Pressure[RAIN_HISTORY_LENGTH];

int getApproxPressure() {
    long averPress = 0;

    for (byte i = 0; i < RAIN_APPROX_LENGTH; i++) {
        averPress += getBMEValue().pressure;
        delay(1);
    }
    averPress /= RAIN_APPROX_LENGTH;
    return averPress;
}

void setupRain() {
    int pressure = getApproxPressure();
    for (byte i = 0; i < RAIN_HISTORY_LENGTH; i++) {
        Pressure[i] = pressure;
    }
}

void rainTick() {
    int newPressure = getApproxPressure();
    for (byte i = 0; i < RAIN_HISTORY_LENGTH - 1; i++) {
        Pressure[i] = Pressure[i + 1];
    }
    Pressure[RAIN_HISTORY_LENGTH - 1] = newPressure;
}

int getRainValue() {
    uint32_t sumX = 0;
    uint32_t sumY = 0;
    uint32_t sumX2 = 0;
    uint32_t sumXY = 0;
    for (int i = 0; i < RAIN_HISTORY_LENGTH; i++) {
        sumX += i;
        sumY += (long) Pressure[i];
        sumX2 += i * i;
        sumXY += (long) i * Pressure[i];
    }
    float a = 0;
    a = (long) RAIN_HISTORY_LENGTH * sumXY;
    a = a - (long) sumX * sumY;
    a = (float) a / (RAIN_HISTORY_LENGTH * sumX2 - sumX * sumX);
    int delta = a * RAIN_HISTORY_LENGTH;
    int rainProbability = map(delta, -250, 250, 100, -100);
    log("[Rain] Delta: " + String(delta) + " probability: " + String(rainProbability));
    return rainProbability;
}
