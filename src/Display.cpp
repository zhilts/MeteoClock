#include <Arduino.h>
#include "Config.h"

#include "Display.h"
#include "Log.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4);

// carts
uint8_t row8[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t row7[8] = {0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t row6[8] = {0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t row5[8] = {0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t row4[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t row3[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};
uint8_t row2[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111};
uint8_t row1[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111};

// digits
uint8_t LT[8] = {0b00111, 0b01111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t UB[8] = {0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};
uint8_t RT[8] = {0b11100, 0b11110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
uint8_t LL[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b01111, 0b00111};
uint8_t LB[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};
uint8_t LR[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11110, 0b11100};
uint8_t UMB[8] = {0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111};
uint8_t LMB[8] = {0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};


void lcdLoadClock() {
    lcd.createChar(0, LT);
    lcd.createChar(1, UB);
    lcd.createChar(2, RT);
    lcd.createChar(3, LL);
    lcd.createChar(4, LB);
    lcd.createChar(5, LR);
    lcd.createChar(6, UMB);
    lcd.createChar(7, LMB);
}

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcdLoadClock();
}

void lcdSetCursor(int x, int y) {
    lcd.setCursor(x, y);
}

void lcdPrint(String text) {
    lcd.print(text);
}

void lcdWrite(int code) {
    lcd.write(code);
}

void lcdClear() {
    lcd.clear();
}

void drawDig(uint8_t dig, uint8_t x, uint8_t y) {
    switch (dig) {
        case 0:
            lcd.setCursor(x, y);
            lcd.write(0);
            lcd.write(1);
            lcd.write(2);
            lcd.setCursor(x, y + 1);
            lcd.write(3);
            lcd.write(4);
            lcd.write(5);
            break;
        case 1:
            lcd.setCursor(x + 1, y);
            lcd.write(1);
            lcd.write(2);
            lcd.setCursor(x + 2, y + 1);
            lcd.write(5);
            break;
        case 2:
            lcd.setCursor(x, y);
            lcd.write(6);
            lcd.write(6);
            lcd.write(2);
            lcd.setCursor(x, y + 1);
            lcd.write(3);
            lcd.write(7);
            lcd.write(7);
            break;
        case 3:
            lcd.setCursor(x, y);
            lcd.write(6);
            lcd.write(6);
            lcd.write(2);
            lcd.setCursor(x, y + 1);
            lcd.write(7);
            lcd.write(7);
            lcd.write(5);
            break;
        case 4:
            lcd.setCursor(x, y);
            lcd.write(3);
            lcd.write(4);
            lcd.write(2);
            lcd.setCursor(x + 2, y + 1);
            lcd.write(5);
            break;
        case 5:
            lcd.setCursor(x, y);
            lcd.write(0);
            lcd.write(6);
            lcd.write(6);
            lcd.setCursor(x, y + 1);
            lcd.write(7);
            lcd.write(7);
            lcd.write(5);
            break;
        case 6:
            lcd.setCursor(x, y);
            lcd.write(0);
            lcd.write(6);
            lcd.write(6);
            lcd.setCursor(x, y + 1);
            lcd.write(3);
            lcd.write(7);
            lcd.write(5);
            break;
        case 7:
            lcd.setCursor(x, y);
            lcd.write(1);
            lcd.write(1);
            lcd.write(2);
            lcd.setCursor(x + 1, y + 1);
            lcd.write(0);
            break;
        case 8:
            lcd.setCursor(x, y);
            lcd.write(0);
            lcd.write(6);
            lcd.write(2);
            lcd.setCursor(x, y + 1);
            lcd.write(3);
            lcd.write(7);
            lcd.write(5);
            break;
        case 9:
            lcd.setCursor(x, y);
            lcd.write(0);
            lcd.write(6);
            lcd.write(2);
            lcd.setCursor(x + 1, y + 1);
            lcd.write(4);
            lcd.write(5);
            break;
        case 10:
            lcd.setCursor(x, y);
            lcd.write(32);
            lcd.write(32);
            lcd.write(32);
            lcd.setCursor(x, y + 1);
            lcd.write(32);
            lcd.write(32);
            lcd.write(32);
            break;
    }
}

void lcdDrawClock(uint8_t hours, uint8_t minutes, uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
    lcd.print("               ");
    lcd.setCursor(x, y + 1);
    lcd.print("               ");

    if (hours / 10 == 0) drawDig(10, x, y);
    else drawDig(hours / 10, x, y);
    drawDig(hours % 10, x + 4, y);
    drawDig(minutes / 10, x + 8, y);
    drawDig(minutes % 10, x + 12, y);
}
