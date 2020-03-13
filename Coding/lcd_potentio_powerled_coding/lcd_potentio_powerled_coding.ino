#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int inputlcd;
int potpin = A3;
int motorpin = A2;
int motorinput;
int value;


void setup()
{

  lcd.init();
  lcd.backlight();
  lcd.print("hello!");
  pinMode(potpin, INPUT);
}

void loop()
{
  lcd.setCursor(0, 1);
  value = analogRead(potpin);
  motorinput = map(value, 0, 1023, 0, 225);
  inputlcd = map(value, 0, 1023, 10, 90);
  analogWrite(motorpin, motorinput);
  lcd.print("input:");
  lcd.print(inputlcd);
  delay(100);

}
