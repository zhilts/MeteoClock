#include <Adafruit_BME280.h>

#include "BME.h"
#include "Config.h"
#include "Log.h"
#include "Led.h"
#include "Display.h"
#include "Config.h"

Adafruit_BME280 bme;

void setupBME() {
    rgbSetValue(RGB_COLOR_BLUE);
    lcdSetCursor(0, 2);
    lcdPrint(F("BME280... "));
    log("Starting BME at " + String(BME280_ADDRESS));
    bool status = bme.begin(BME280_ADDRESS, &Wire);
    if (status) {
        lcdPrint(F("OK"));
        log(F("BME280: OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("BME280: ERROR"));
        return;
    }

    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);
}

BMEValue getBMEValue() {
    bme.takeForcedMeasurement();
    BMEValue result;
    result.pressure = bme.readPressure();
    result.temperature = bme.readTemperature();
    result.humidity = bme.readHumidity();
    return result;
}

//void readBMEValues() {
//    bme.takeForcedMeasurement();
//}
//
//float getPressure() {
//    return bme.readPressure();
//}
//
//float getTemperature() {
//    return bme.readTemperature();
//}
//
//byte getHumidity() {
//    return bme.readHumidity();
//}

String bmeGetDebugString() {
    BMEValue value = getBMEValue();
    return "Pressure: " + String(value.pressure) + " Temp: " + String(value.temperature) + " Hum: " +
           String(value.humidity);
}