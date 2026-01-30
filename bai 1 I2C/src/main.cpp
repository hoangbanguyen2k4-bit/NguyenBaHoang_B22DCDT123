#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

String messageToScroll = "Dien tu nhung Tiot Smart";

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void setup()
{
    // initialize LCD
    lcd.init();
    // turn on LCD backlight
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Xin chao");
    delay(1000);
    lcd.clear();

    lcd.setCursor(0, 1);
    lcd.print("Xin chao");
    delay(1000);
    lcd.clear();

    scrollText(1, messageToScroll, 500, lcdColumns);
}