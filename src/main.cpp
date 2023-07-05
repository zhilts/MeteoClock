#include <Arduino.h>

#include "Config.h"

#include "Log.h"
#include "WiFiConnection.h"
#include "OTA.h"
#include "Led.h"
#include "RTCTime.h"
#include "Display.h"
#include "WebDashboard.h"
#include "Photo.h"
#include "BME.h"
#include "CO2.h"
#include "Button.h"

void setup() {
    setupLog();
    connectWifi();
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
    log("----- DEBUG ------");
    log("Photo: " + String(getBrightness()));
    log("Button: " + String(buttonGetValue()));
    log("CO2: " + getCo2DebugSting());
    log("Time: " + getNowISO());
    log("BME: " + bmeGetDebugString());
    log("Logs: " + getHttpLogsHost() + ":" + getHttpLogsPort());
    delay(1000);
}

void loop() {
    otaHandle();
    serverHandle();
    debugLoop();
}
