#include <EEPROM.h>
#include "Memory.h"
#include "Log.h"

const int eepromSize = 512;
const int ssidStartAddress = 0;
const int passwordStartAddress = 32;


WiFiCredentials readWiFiCredentials() {
    WiFiCredentials result;
    result.ssid = "";
    result.password = "";
    EEPROM.begin(eepromSize);

    for (int i = 0; i < 32; i++) {
        char c = char(EEPROM.read(ssidStartAddress + i));
        if (c == '\0') break;
        result.ssid += c;
    }
    for (int i = 0; i < 32; i++) {
        char c = char(EEPROM.read(passwordStartAddress + i));
        if (c == '\0') break;
        result.password += c;
    }
    EEPROM.end();
    return result;
}

void writeWiFiCredentials(WiFiCredentials credentials) {
    EEPROM.begin(eepromSize);
    for (int i = 0; i < credentials.ssid.length(); i++) {
        EEPROM.write(ssidStartAddress + i, credentials.ssid[i]);
    }
    EEPROM.write(ssidStartAddress + credentials.ssid.length(), '\0');
    for (int i = 0; i < credentials.password.length(); i++) {
        EEPROM.write(passwordStartAddress + i, credentials.password[i]);
    }
    EEPROM.write(passwordStartAddress + credentials.password.length(), '\0');
    EEPROM.commit();
    EEPROM.end();
}
