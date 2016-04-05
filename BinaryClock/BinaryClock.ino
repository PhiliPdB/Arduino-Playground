#include "Arduino.h";
#include <Time.h>;

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message

int ledPins[] = {A5,2,3,4,5,6,7,8,9,10,11,12,13};

byte leftHours;
byte rightHours;
byte leftMinutes;
byte rightMinutes;
int oldMinutes;
int oldHours;

void setup() {
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {

  //int hours = ??;
  //int minutes = ??;

  if(oldMinutes == minutes && oldHours == hours) { return; }

  //reset LEDs
  for (int i = 0; i < sizeof(ledPins); i++) {
    digitalWrite(ledPins[i], LOW);
  }

  //hours
  if(hours < 10) {
    leftHours = (byte) 0;
    rightHours = (byte) hours;
  } else if(hours >= 10) {
    leftHours = (byte) ((hours - (hours%10)) / 10);
    rightHours = (byte) (hours%10);
  } else {
    //I've got a problem
  }
  for(int i=0; i<2; i++) {
    if(bitRead(leftHours, i) == 1) {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  for(int i=2; i<6; i++) {
    if(bitRead(rightHours, (i-2)) == 1) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  //minutes
  if(minutes < 10) {
    leftMinutes = (byte) 0;
    rightMinutes = (byte) minutes;
  } else if(minutes >= 10) {
    leftMinutes = (byte) ((minutes - (minutes%10)) / 10);
    rightMinutes = (byte) (minutes%10);
  } else {
    //I've got a problem
  }
  for(int i=6; i<9; i++) {
    if(bitRead(leftMinutes, (i-6)) == 1) {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  for(int i=9; i<13; i++) {
    if(bitRead(rightMinutes, (i-9)) == 1) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  int oldMinutes = minutes;
  int oldHours = hours;
  
}
