#include "Secrets.h"

void setup() {
    connectWifi();
    log("Starting");
    setupLCD();
    setupOTA();
    setupButton();
    setupRGB();
    setupServer();
}

int lastButton = -1;

void loop() {
    otaHandle();
    serverHandle();
    int touchValue = buttonGetValue();

    if (touchValue != lastButton) {
        if (touchValue == HIGH) {
            lcdSetCursor(0, 0);
            lcdPrint("Touch Detected");
            log("Touch Detected");
        } else {
            lcdClear();
        }
        lastButton = touchValue;
    }
}
