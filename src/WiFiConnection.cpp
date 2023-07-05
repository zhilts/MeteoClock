#include <WiFi.h>

#if __has_include("Secrets.h")
    #include "Secrets.h"
#else
    #include "ConfigWTF.h"
#endif
#include "Config.h"
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