#ifndef METEO_CLOCK_MQTT_H
#define METEO_CLOCK_MQTT_H

#include <Arduino.h>

#define MQTT_RECONNECT_RETRIES 3

void setupMQTT();

bool mqttIfReconnect();

void mqttPublish(String topic, String message);

struct MQTTConfig {
    bool enabled;
    String name;
    String host;
    int port;
};

MQTTConfig getMQTTConfig();

void setMQTTConfig(MQTTConfig config);

#endif //METEO_CLOCK_MQTT_H
