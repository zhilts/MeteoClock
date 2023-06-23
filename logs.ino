#if HTTP_LOG_ENABLED
#include <WiFiClient.h>
#endif

void log(String message) {
#if HTTP_LOG_ENABLED
    WiFiClient client;

    String formattedMessage = String(RIG_IDENTIFIER) + ": " + message;

    if (client.connect(HTTP_LOG_ADDRESS, HTTP_LOG_PORT)) {
        client.println("POST / HTTP/1.1");
        client.println("Host: " + String(HTTP_LOG_ADDRESS));
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
#endif
}