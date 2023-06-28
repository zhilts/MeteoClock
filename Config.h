#ifndef METEO_CLOCK_CONFIG_H
#define METEO_CLOCK_CONFIG_H

#define DEBUG 1
#define RESET_CLOCK true

#define TOUCH_PIN 2

#define LCD_ADDRESS 0x27
#define I2C_A 21
#define I2C_B 22

#define LED_MODE 1            // 0 - cathode, 1 - anode
#define LED_COM 4
#define LED_R 18
#define LED_G 5
#define LED_B 19

#define HTTP_LOG_ENABLED true
#define HTTP_LOG_ADDRESS "MacBook-Pro-2023.local"
#define HTTP_LOG_PORT 8000

#define CO2_SENSOR 1
#define MHZ_RX 25
#define MHZ_TX 26

#define PHOTO 32

#endif //METEO_CLOCK_CONFIG_H