#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTT.h"
#include "Secrets.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupMQTT() {
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    while (!mqttClient.connected()) {
        if (mqttClient.connect(RIG_IDENTIFIER)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void reconnect() {
    while (!mqttClient.connected()) {
        if (mqttClient.connect(RIG_IDENTIFIER)) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void mqttPublish(String topic, String message) {
    reconnect();
    String path = String(RIG_IDENTIFIER) + "/" + topic;
    mqttClient.publish(path.c_str(), message.c_str());
}