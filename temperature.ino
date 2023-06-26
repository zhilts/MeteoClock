#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setupBME(){
#if (DEBUG == 1)
    setLED(3);
    lcdSetCursor(0, 2);
    lcdPrint(F("BME280... "));
    log(F("BME280... "));
    delay(50);
#endif
    bool status = bme.begin(&Wire);
#if (DEBUG == 1)
    if (status) {
        lcdPrint(F("OK"));
        log(F("OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("ERROR"));
    }
#endif
}