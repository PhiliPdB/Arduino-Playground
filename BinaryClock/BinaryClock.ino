#include "Arduino.h";
#include <Time.h>;

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message

//globale variabelen
int ledPins[] = {A5,2,3,4,5,6,7,8,9,10,11,12,13};
byte leftHours;
byte rightHours;
byte leftMinutes;
byte rightMinutes;
int hours;
int minutes;
int oldMinutes;
int oldHours;

//declareert de LEDs
void setup() {
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {

  //haalt de nieuwe tijd op
  hours = 17;
  minutes = 37;

  //stopt de huidige loop als de oude tijd gelijk is aan de opghaalde tijd
  if(oldMinutes == minutes && oldHours == hours) { return; }

  //zet alle LEDs uit
  for (int i = 0; i < sizeof(ledPins); i++) {
    digitalWrite(ledPins[i], LOW);
  }

  //zet het aantal uren om in een binair getal van het linker en rechter getal (bijvoorbeeld 16 => 1 en 110)
  if(hours < 10) {
    leftHours = (byte) 0; //bij een getal kleiner dan 10 moet het linker getal 0 zijn (om zo alsnog 2 getallen te krijgen)
    rightHours = (byte) hours;
  } else if(hours >= 10) {
    leftHours = (byte) ((hours - (hours%10)) / 10);
    rightHours = (byte) (hours%10);
  } else {
    //I've got a problem
  }

  //leest de binaire uurtijd af en zet daarmee de goede LEDs aan
  for(int i=1; i<3; i++) {
    if(bitRead(leftHours, (i-1)) == 1) {
      digitalWrite(ledPins[i-1], HIGH);
    }
  }
  for(int i=3; i<7; i++) {
    if(bitRead(rightHours, (i-3)) == 1) {
      digitalWrite(ledPins[i-1], HIGH);
    }
  }

  //dezelfde omzetting als bij de uren maar dan voor de minuten
  if(minutes < 10) {
    leftMinutes = (byte) 0;
    rightMinutes = (byte) minutes;
  } else if(minutes >= 10) {
    leftMinutes = (byte) ((minutes - (minutes%10)) / 10);
    rightMinutes = (byte) (minutes%10);
  } else {
    //I've got a problem
  }

  //leest de binaire minuuttijd af en zet daarmee de goede LEDs aan
  for(int i=7; i<10; i++) {
    if(bitRead(leftMinutes, (i-7)) == 1) {
      digitalWrite(ledPins[i-1], HIGH);
    }
  }
  for(int i=10; i<14; i++) {
    if(bitRead(rightMinutes, (i-10)) == 1) {
      digitalWrite(ledPins[i-1], HIGH);
    }
  }

  //slaat de minuten en uren op om bij de volgende loop daarop te checken
  oldMinutes = minutes;
  oldHours = hours;
  
}
