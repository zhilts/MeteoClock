#include <MHZ19_uart.h>

MHZ19_uart mhz19;

void setupCO2() {
#if (DEBUG == 1)
    setLED(1);
    lcdSetCursor(0, 0);
    lcdPrint(F("MHZ-19... "));
    log(F("MHZ-19... "));
#endif
    mhz19.begin(MHZ_TX, MHZ_RX);
    mhz19.setAutoCalibration(false);
#if (DEBUG == 1)
    mhz19.getStatus();
    delay(500);
    if (mhz19.getStatus() == 0) {
        lcdPrint(F("OK"));
        log(F("OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("ERROR"));
    }
#endif
}

void co2LogStatus() {
    log("mhz19 status: " + String(mhz19.getStatus()));
}