#ifndef METEO_CLOCK_MEMORY_H
#define METEO_CLOCK_MEMORY_H

struct WiFiCredentials {
    String ssid;
    String password;
};

WiFiCredentials readWiFiCredentials();

void writeWiFiCredentials(WiFiCredentials credentials);

#endif //METEO_CLOCK_MEMORY_H
