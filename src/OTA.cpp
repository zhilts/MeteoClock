#include <ArduinoOTA.h>

#include "Config.h"
#include "Secrets.h"
#include "OTA.h"

void setupOTA() {
    ArduinoOTA
            .onError([](ota_error_t error) {
                esp_restart();
            });

    ArduinoOTA.setHostname(RIG_IDENTIFIER);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();
}

void otaHandle() {
    ArduinoOTA.handle();
}