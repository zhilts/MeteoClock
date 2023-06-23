#include <LiquidCrystal_I2C.h>
#include "Config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, I2C_A, I2C_B);

void setupLCD() {
    lcd.init();
    lcd.backlight();
}

void lcdSetCursor(int x, int y) {
    lcd.setCursor(x, y);
}

void lcdPrint(String text) {
    log("LCD print: " + text);
    lcd.print(text);
}

void lcdClear() {
    lcd.clear();
}