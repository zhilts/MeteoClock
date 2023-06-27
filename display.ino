#include <LiquidCrystal_I2C.h>
#include "Config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, I2C_A, I2C_B);

void setupLCD() {
    lcd.init();
    lcd.backlight();
//    lcdLoadClock();
}

void lcdSetCursor(int x, int y) {
    lcd.setCursor(x, y);
}

void lcdPrint(String text) {
    lcd.print(text);
}

void lcdClear() {
    lcd.clear();
}

void lcdLoadClock() {
//    lcd.createChar(0, LT);
//    lcd.createChar(1, UB);
//    lcd.createChar(2, RT);
//    lcd.createChar(3, LL);
//    lcd.createChar(4, LB);
//    lcd.createChar(5, LR);
//    lcd.createChar(6, UMB);
//    lcd.createChar(7, LMB);
}

void lcdDrawClock(byte hours, byte minutes, byte x, byte y) {
    lcd.setCursor(x, y);
    lcd.print("               ");
    lcd.setCursor(x, y + 1);
    lcd.print("               ");

//    if (hours / 10 == 0) drawDig(10, x, y);
//    else drawDig(hours / 10, x, y);
//    drawDig(hours % 10, x + 4, y);
//    drawDig(minutes / 10, x + 8, y);
//    drawDig(minutes % 10, x + 12, y);
}