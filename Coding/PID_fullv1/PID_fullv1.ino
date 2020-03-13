#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int setpointlcd;
int potpin = A3;
int motorpin = 10;
int value;
int setpoint;
int kP = 2;
int kI = 1;
int kD = 1;
int nholes = 8;
unsigned long lastcheck;
int checkTime = 250;
int RPM;
int count = 0;
int dt = 100;
int drive;
int switchpid = 3;
int ledpid = 7;
int error;
int derivative;
int previous_error;
int integral;
int motorinput;


void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), photo, RISING);
  lastcheck = millis();
  lcd.init();
  lcd.backlight();
  lcd.print("hello!");
  pinMode(potpin, INPUT);
  pinMode(motorpin, OUTPUT);
  pinMode(ledpid, OUTPUT);
  pinMode(switchpid, INPUT);
}

void loop()
{
  lcd.setCursor(0, 1);
  digitalWrite(ledpid, LOW);
  value = analogRead(potpin);
  setpointlcd = map(value, 0, 1023, 0, 90);
  setpoint = map(value, 0, 1023, 0, 30000);
  motorinput = map(drive, 0, 30000, 0, 255);
//  rpmserial = map(RPM, 0, 1023, 0, 30000);
  //analogWrite(motorpin, motorinput);
  lcd.print("input:");
  lcd.print(setpoint);
  lcd.print("      ");
  //32,160highestRPM
  Serial.println(RPM);

  analogWrite(motorpin, motorinput);

  if (millis() - lastcheck >= checkTime) {
    detachInterrupt(digitalPinToInterrupt(2));
    RPM = (count / nholes)  * 4 * 60;
    lastcheck = millis();
    count = 0;
    attachInterrupt(digitalPinToInterrupt(2), photo, RISING);
  }

  if (digitalRead(switchpid) == HIGH) {
    digitalWrite(ledpid, HIGH);
    error = setpoint - (RPM);
    integral = integral + (error * dt);
    derivative = (error - previous_error) / dt;
    drive = (error * kP) + (integral * kI) + (derivative * kD);
    previous_error = error;
    delay(dt);

    // analogWrite(motorpin, drive);
  }
  else {
    drive = setpoint;
  }

}

void photo() {
  count = count + 1;
}
