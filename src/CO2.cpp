#include <SoftwareSerial.h>
#include "MHZ19.h"

#include "Config.h"
#include "Log.h"
#include "Display.h"
#include "Led.h"

MHZ19 mhz19;

HardwareSerial mySerial(2);

void setupCO2() {
#if (DEBUG == 1)
    rgbSetValue(1);
    lcdSetCursor(0, 0);
    lcdPrint(F("MHZ-19... "));
#endif
    mySerial.begin(MHZ_BAUD);
    mhz19.begin(mySerial);
    mhz19.autoCalibration(false);
#if (DEBUG == 1)
    lcdPrint(F("OK"));
    log(F("MHZ-19: OK"));
#endif
}

byte getCo2Status() {
    return mhz19.getPWMStatus();
}

int getCO2() {
    return mhz19.getCO2();
}

String getCo2DebugSting() {
    return "Status: " + String(getCo2Status()) + " CO2: " + String(getCO2()) + "ppm";
}