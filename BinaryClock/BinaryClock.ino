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

int hours = 10;
int minutes = 0;
int oldMinutes;
int oldHours;

void setup() {
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {

  //int hours = 10;
  //int minutes = 59;
  
  minutes++;
  if(minutes == 60) {
    minutes = 0;
    hours++;
  }
  if(hours == 24) {
    hours = 0;
  }
  delay(500);

  //reset LEDs
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

  int oldMinutes = minutes;
  int oldHours = hours;
  
}
