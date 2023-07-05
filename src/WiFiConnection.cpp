#include <WiFi.h>

#if __has_include("Secrets.h")
    #include "Secrets.h"
#else
    #include "ConfigWTF.h"
#endif
#include "Config.h"
#include "WiFiConnection.h"

void connectWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}