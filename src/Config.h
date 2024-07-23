#ifndef METEO_CLOCK_CONFIG_H
#define METEO_CLOCK_CONFIG_H

#define DEBUG false

#define TOUCH_PIN 15

#define LCD_ADDRESS 0x27

#define LED_MODE 1            // 0 - cathode, 1 - anode
#define LED_COM 4
#define LED_R 18
#define LED_G 5
#define LED_B 19

#define SERIAL_MONITOR_BAUD 9600
#define MHZ_BAUD 9600

#define BME280_ADDRESS (0x76)

#define PHOTO 32

#define SENS_TIME 30000   // sensor update frequency ms
#define DISP_MODE 1       // upper right corner: 0 - year, 1 - day of the week, 2 - seconds

#endif //METEO_CLOCK_CONFIG_H

#ifndef RIG_IDENTIFIER
#define RIG_IDENTIFIER "meteo"
#endif

#ifndef HTTP_LOG_ENABLED
#define HTTP_LOG_ENABLED false
#endif

#ifndef MQTT_ENABLED
#define MQTT_ENABLED false
#endif

#ifndef MQTT_HOST
#define MQTT_HOST "mqtt.local"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef HTTP_LOG_ADDRESS
#define HTTP_LOG_ADDRESS "log.local"
#endif

#ifndef HTTP_LOG_PORT
#define HTTP_LOG_PORT 8000
#endif

#ifndef WIFI_AP_SSID
#define WIFI_AP_SSID "meteo-AP"
#endif

#ifndef WIFI_AP_PASSWORD
#define WIFI_AP_PASSWORD "meteo-gyver"
#endif
