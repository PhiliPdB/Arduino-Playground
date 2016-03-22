int ledPins[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < sizeof(ledPins); i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);              // wait for a second
  for (int i = 0; i < sizeof(ledPins); i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000); 
}
