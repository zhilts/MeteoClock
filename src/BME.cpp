#include "Adafruit_BME280.h"

#include "BME.h"
#include "Log.h"
#include "Led.h"
#include "Display1.h"
#include "ConfigWTF.h"

Adafruit_BME280 bme;

uint32_t pressure_array[6];
byte time_array[6];

void setupBME() {
#if (DEBUG == 1)
    rgbSetValue(3);
    lcdSetCursor(0, 2);
    lcdPrint(F("BME280... "));
    log(F("BME280... "));
    delay(50);
#endif
    bool status = bme.begin(BME280_ADDRESS, &Wire);
#if (DEBUG == 1)
    if (status) {
        lcdPrint(F("OK"));
        log(F("OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("ERROR"));
    }
#endif

    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);

    bme.takeForcedMeasurement();
    uint32_t Pressure = bme.readPressure();
    for (byte i = 0; i < 6; i++) {
        pressure_array[i] = Pressure;
        time_array[i] = i;
    }
}