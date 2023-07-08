#include <Arduino.h>
#include <GyverTimer.h>

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
#include "Functions.h"
#include "Rain.h"
#include "MQTT.h"


GTimer_ms sensorsTimer(SENS_TIME);
GTimer_ms clockTimer(500);
GTimer_ms debugTimer(2000);
GTimer_ms rainPredictTimer((long) 10 * 60 * 1000);         // 10 minutes

void setup() {
    setupLog();
    connectWifi();
    setupOTA();
    setupMQTT();
    setupLCD();
    setupButton();
    setupRGB();
    setupServer();
    setupCO2();
    setupRTC();
    setupBME();
    setupRain();
    delay(500);
    lcdClear();
    updateSensors();
}

void debugLoop() {
#if (!DEBUG)
    return;
#endif
    log("----- DEBUG ------");
    log("Photo: " + String(getBrightness()));
    log("Button: " + String(buttonGetValue()));
    log("CO2: " + getCO2DebugSting());
    log("Time: " + getNowISO());
    log("BME: " + bmeGetDebugString());
    log("Logs: " + getHttpLogsHost() + ":" + getHttpLogsPort());
}

void loop() {
    otaHandle();
    serverHandle();
    buttonTick();
    if (rainPredictTimer.isReady()) rainTick();
    if (debugTimer.isReady()) debugLoop();
    if (sensorsTimer.isReady()) updateSensors();
    if (clockTimer.isReady()) timerTick();
}
