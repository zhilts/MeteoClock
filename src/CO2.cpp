#include "MHZ19.h"

#include "ConfigWTF.h"
#include "Log.h"
#include "Display1.h"
#include "Led.h"

MHZ19 mhz19;

HardwareSerial mySerial(2);

void setupCO2() {
#if (DEBUG == 1)
    rgbSetValue(1);
    lcdSetCursor(0, 0);
    lcdPrint(F("MHZ-19... "));
    log(F("MHZ-19... "));
#endif

    mySerial.begin(MHZ_BAUD);
    mhz19.begin(mySerial);
    mhz19.autoCalibration(false);
#if (DEBUG == 1)
    char mVersion[4];
    mhz19.getVersion(mVersion);
    delay(500);
    lcdPrint(mVersion);
    log("MHZ-19_FW_version: " + String(mVersion));
#endif
}

void co2LogStatus() {
    lcdSetCursor(16, 0);
    lcdPrint("  ");
    lcdSetCursor(16, 0);
    char mVersion[4];
    mhz19.getVersion(mVersion);
    lcdPrint(String(mVersion));
}