void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 13; i++) {
    pinMode(i+1, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < sizeof(ledPins); i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);              // wait for a second
  for (int i = 0; i < 13; i++) {
    digitalWrite(i+1, LOW);
  }
  delay(1000); 
}
