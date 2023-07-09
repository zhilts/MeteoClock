#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTT.h"
#include "Secrets.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupMQTT() {
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}

bool mqttIfReconnect() {
    int count = 0;
    while (!mqttClient.connected() && count < MQTT_RECONNECT_RETRIES) {
        if (mqttClient.connect(RIG_IDENTIFIER)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 1 seconds...");
            delay(1000);
        }
        count++;
    }
    return mqttClient.connected();
}

void mqttPublish(String topic, String message) {
    if (mqttClient.connected()) {
        String path = String(RIG_IDENTIFIER) + "/" + topic;
        mqttClient.publish(path.c_str(), message.c_str());
    }
}