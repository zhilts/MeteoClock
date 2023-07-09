#ifndef METEO_CLOCK_MQTT_H
#define METEO_CLOCK_MQTT_H

#include <Arduino.h>

#define MQTT_RECONNECT_RETRIES 3

void setupMQTT();

bool mqttIfReconnect();

void mqttPublish(String topic, String message);

#endif //METEO_CLOCK_MQTT_H
