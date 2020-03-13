

int nholes = 2;
unsigned long lastcheck;
int checkTime = 250;
int RPM;
int count;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), photo, RISING);
  lastcheck = millis();
}

void loop() {

  if (millis() - lastcheck >= checkTime) {
    detachInterrupt(digitalPinToInterrupt(2));
    RPM = (count / nholes) * 4 * 60;
    lastcheck = millis();
    count = 0;
    attachInterrupt(digitalPinToInterrupt(2), photo, RISING);
  }
Serial.println(RPM);
}
void photo() {
  count = count + 1;
}
