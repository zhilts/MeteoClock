#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTT.h"
#include "Secrets.h"
#include "Config.h"
#include "Log.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

bool isMqttEnabled = MQTT_ENABLED;
String mqttName = RIG_IDENTIFIER;
String mqttHost = MQTT_HOST;
int mqttPort = MQTT_PORT;

void setupMQTT() {
    log("[MQTT] setup. " + mqttName + "@" + mqttHost + ":" + String(mqttPort));
    mqttClient.setServer(mqttHost.c_str(), mqttPort);
}

bool mqttIfReconnect() {
    if (!isMqttEnabled) return false;
    int count = 0;
    while (!mqttClient.connected() && count < MQTT_RECONNECT_RETRIES) {
        if (mqttClient.connect(mqttName.c_str())) {
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
        String path = mqttName + "/" + topic;
        mqttClient.publish(path.c_str(), message.c_str());
    }
}

MQTTConfig getMQTTConfig() {
    MQTTConfig config;
    config.enabled = isMqttEnabled;
    config.name = mqttName;
    config.host = mqttHost;
    config.port = mqttPort;
    return config;
}

void setMQTTConfig(MQTTConfig config) {
    isMqttEnabled = config.enabled;
    mqttName = config.name;
    mqttHost = config.host;
    mqttPort = config.port;
    setupMQTT();
}