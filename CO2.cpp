#include <MHZ19_uart.h>

#include "Config.h"
#include "Log.h"
#include "Display.h"
#include "Led.h"

MHZ19_uart mhz19;

void setupCO2() {
#if (DEBUG == 1)
    rgbSetValue(1);
    lcdSetCursor(0, 0);
    lcdPrint(F("MHZ-19... "));
#endif
    mhz19.begin(MHZ_TX, MHZ_RX);
    mhz19.setAutoCalibration(false);
#if (DEBUG == 1)
    mhz19.getStatus();
    delay(500);
    if (mhz19.getStatus() == 0) {
        lcdPrint(F("OK"));
        log(F("MHZ-19: OK"));
    } else {
        lcdPrint(F("ERROR"));
        log(F("MHZ-19: ERROR"));
    }
#endif
}

int getCo2Status() {
    return mhz19.getStatus();
}

int getCO2() {
    return mhz19.getPPM();
}

String getCo2DebugSting() {
    return "Status: " + String(mhz19.getStatus()) + " CO2: " + String(getCO2()) + "ppm";
}
