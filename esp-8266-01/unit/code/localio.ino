//This file contains all the functions mentionend in the local.h header file

#include"localio.h"

// declaring soundBuzzer function for the buzzer module
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 500);
  delay(1000);
}

// declaring senseMotion function for pir sensor
void senseMotion(int pir, int buzzer) {
  int pirValue = digitalRead(pir);
  if(pirValue == HIGH) {
    soundBuzzer(buzzer);
    Serial.println("Motion Detected!");
  }
  else {
    noTone(buzzer);
    Serial.println("No Motion");
  }
}