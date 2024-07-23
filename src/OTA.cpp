#include <ArduinoOTA.h>

#include "Config.h"
#include "Secrets.h"
#include "Log.h"
#include "OTA.h"

String mapError(ota_error_t error);

void setupOTA() {
    ArduinoOTA
            .onStart([]() {
                log("[OTA] Start updating...");
            })
            .onEnd([]() {
                log("[OTA] End updating");
            })
            .onProgress([](unsigned int progress, unsigned int total) {
                log("[OTA] Progress: " + String(progress / (total / 100)) + "%");
            })
            .onError([](ota_error_t error) {
                log("[OTA] Error: " + String(error) + " " + mapError(error));
                esp_restart();
            });

    ArduinoOTA.setHostname(RIG_IDENTIFIER);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();
}

void otaHandle() {
    ArduinoOTA.handle();
}

String mapError(ota_error_t error) {
    switch (error) {
        case OTA_AUTH_ERROR:
            return "Auth Failed";
        case OTA_BEGIN_ERROR:
            return "Begin Failed";
        case OTA_CONNECT_ERROR:
            return "Connect Failed";
        case OTA_RECEIVE_ERROR:
            return "Receive Failed";
        case OTA_END_ERROR:
            return "End Failed";
        default:
            return "";
    }
}