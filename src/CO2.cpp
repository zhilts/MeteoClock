#include <SoftwareSerial.h>
#include "MHZ19.h"

#include "Config.h"
#include "Log.h"
#include "Display.h"
#include "Led.h"
#include "CO2.h"

MHZ19 mhz19;

HardwareSerial mySerial(2);

void setupCO2() {
    rgbSetValue(RGB_COLOR_RED);
    lcdSetCursor(0, 0);
    lcdPrint(F("MHZ-19... "));
    mySerial.begin(MHZ_BAUD);
    mhz19.begin(mySerial);
    mhz19.autoCalibration(false);
    lcdPrint(F("OK"));
    log(F("MHZ-19: OK"));
}

byte getCO2Status() {
    return mhz19.getPWMStatus();
}

int getCO2() {
    return mhz19.getCO2();
}

String getCO2DebugSting() {
    return "Status: " + String(getCO2Status()) + " CO2: " + String(getCO2()) + "ppm";
}

CO2_LEVEL getCO2Level() {
    int co2Value = getCO2();
    if (co2Value < 800) return CO2_LEVEL_GOOD;
    else if (co2Value < 1200) return CO2_LEVEL_WARNING;
    return CO2_LEVEL_ALERT;
}

void zeroPointCalibration() {
    byte command[9] = {0xff, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78};
    mySerial.write(command, 9);
    Serial.println("Zero Point Calibration Command Sent");
}