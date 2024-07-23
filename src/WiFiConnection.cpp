#include <Arduino.h>
#include <WiFi.h>
#include "Config.h"
#include "Secrets.h"
#include "WiFiConnection.h"
#include "Log.h"
#include "Memory.h"

void setupWifi() {
    WiFiCredentials credentials = readWiFiCredentials();
    log("[WiFi] Connecting to " + credentials.ssid + ":" + credentials.password);
    WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 5) {
        retry++;
        delay(1000);
        log("[WiFi] Connecting to WiFi...");
    }
    if (WiFi.status() != WL_CONNECTED) {
        log("[WiFi] set AP mode");
        WiFi.mode(WIFI_AP);
        log("[WiFi] softAP");
        WiFi.softAP(String(WIFI_AP_SSID).c_str(), String(WIFI_AP_PASSWORD).c_str());
        log("[WiFi] AP started");
    } else {
        log("[WiFi] Connected to WiFi. IP: " + WiFi.localIP().toString());
    }
}