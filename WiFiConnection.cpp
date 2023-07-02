#include <WiFi.h>
#include "Secrets.h"
#include "WiFiConnection.h"
#include "Log.h"

void connectWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        log("Connecting to WiFi...");
    }
    log("Connected to WiFi");
}