#ifndef METEO_CLOCK_CONFIG_H
#define METEO_CLOCK_CONFIG_H

#define DEBUG 1
#define RESET_CLOCK true

#define TOUCH_PIN 15

#define LCD_ADDRESS 0x27

#define LED_MODE 1            // 0 - cathode, 1 - anode
#define LED_COM 4
#define LED_R 18
#define LED_G 5
#define LED_B 19

#define HTTP_LOG_ENABLED false

#define SERIAL_MONITOR_BAUD 9600
#define MHZ_BAUD 9600

#define BME280_ADDRESS (0x76)

#define PHOTO 32

#endif //METEO_CLOCK_CONFIG_H