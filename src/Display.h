#ifndef METEO_CLOCK_DISPLAY_H
#define METEO_CLOCK_DISPLAY_H

void setupLCD();
void lcdSetCursor(int x, int y);
void lcdPrint(String text);
void lcdWrite(int code);
void lcdClear();
void lcdDrawClock(uint8_t hours, uint8_t minutes, uint8_t x, uint8_t y);

#endif //METEO_CLOCK_DISPLAY_H
