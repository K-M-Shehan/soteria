/*
This file is for the ESP 01  wifi module to identify an intruder
and to sound the buzzer to warn the intruder and inform the user about the user about
the intruder via sounding the buzzer
*/

#include"localio.h"

// Declaring GPIO 0 and GPIO 2 as buzzer and pir pins
const int pir = 4;
const int buzzer = 5;


//Bellow this sound setup and the main loop is declared.
void setup() {
  Serial.begin(9600);
  // Set pir as input and buzzer as output
  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
  Serial.print("PIR Sensor Values: ");
  senseMotion(pir, buzzer);
  delay(500);
}
