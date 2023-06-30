#include "ConfigWTF.h"

#include "Log.h"
#include "WiFiConnection.h"
#include "OTA.h"
#include "Led.h"
#include "Time1.h"
#include "Display1.h"
#include "WebDashboard.h"
#include "Photo.h"
#include "BME.h"
#include "CO2.h"
#include "Button.h"


void setup() {
    connectWifi();
    log("Starting");
    setupOTA();
    setupLCD();
    setupButton();
    setupRGB();
    setupServer();
    setupCO2();
    setupRTC();
    setupBME();
}

void debugLoop() {
#if (DEBUG != 1)
    return;
#endif
    lcdSetCursor(14, 1);
    lcdPrint("P:    ");
    lcdSetCursor(16, 1);
    lcdPrint(String(getBrightness()));

    lcdSetCursor(16, 2);
    lcdPrint("B:  ");
    lcdSetCursor(18, 2);
    lcdPrint(String(buttonGetValue()));

    co2LogStatus();

    delay(300);
}

void loop() {
    otaHandle();
    serverHandle();
    debugLoop();

    getNow();
}
