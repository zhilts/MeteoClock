#include "Log.h"
#include "Config.h"
#include "Secrets.h"

#include <WiFiClient.h>

void setupLog() {
    Serial.begin(9600);
}

bool isHttpEnabled = HTTP_LOG_ENABLED;
String httpLogsHost = HTTP_LOG_ADDRESS;
int httpLogsPort = HTTP_LOG_PORT;

bool getHttpLogsEnabled() {
    return isHttpEnabled;
}

void setHttpLogsEnabled(bool enabled) {
    isHttpEnabled = enabled;
}

String getHttpLogsHost() {
    return String(httpLogsHost);
}

void setHttpLogsHost(String host) {
    httpLogsHost = host;
}

int getHttpLogsPort() {
    return httpLogsPort;
}

void setHttpLogsPort(int port) {
    httpLogsPort = port;
}

void log(String message) {
    if (isHttpEnabled) {
        Serial.println("HTTP Log");
        WiFiClient client;

        String formattedMessage = String(RIG_IDENTIFIER) + ": " + message;

        if (client.connect(httpLogsHost.c_str(), httpLogsPort)) {
            client.println("POST / HTTP/1.1");
            client.println("Host: " + String(httpLogsHost));
            client.println("Connection: close");
            client.println("Content-Type: plain/text");
            client.print("Content-Length: ");
            client.println(formattedMessage.length());
            client.println();
            client.println(formattedMessage);

            while (client.connected()) {
                String line = client.readStringUntil('\n');
            }

            client.stop();
        }
    }
    Serial.println(message);
}