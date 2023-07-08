#ifndef METEO_CLOCK_MQTT_H
#define METEO_CLOCK_MQTT_H

#include <Arduino.h>

void setupMQTT();

void mqttPublish(String topic, String message);

#endif //METEO_CLOCK_MQTT_H
