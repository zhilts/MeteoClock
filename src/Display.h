#ifndef METEO_CLOCK_DISPLAY_H
#define METEO_CLOCK_DISPLAY_H

void setupLCD();
void lcdSetCursor(int x, int y);
void lcdPrint(String text);
void lcdClear();

#endif //METEO_CLOCK_DISPLAY_H
