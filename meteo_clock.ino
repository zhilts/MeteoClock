#include "Secrets.h"
#include "Config.h"

#include "led.h"


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
    lcdSetCursor(14, 1);
    lcdPrint("P:    ");
    lcdSetCursor(16, 1);
    lcdPrint(String(getBrightness()));

    lcdSetCursor(14, 2);
    lcdPrint("B:    ");
    lcdSetCursor(16, 2);
    lcdPrint(String(buttonGetValue()));

    delay(300);
}

void loop() {
    otaHandle();
    serverHandle();

    rgbSetValue(RGB_GREEN);

#if (DEBUG == 1)
    debugLoop();
#endif
}
