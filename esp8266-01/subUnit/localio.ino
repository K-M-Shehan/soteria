//This file contains all the functions mentionend in the local.h header file

#include"localio.h"

// declaring soundBuzzer function for the buzzer module
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 500);
  delay(1000);
}

// declaring senseMotion function for pir sensor
// declaring senseMotion function for pir sensor
// TODO: move noTone from sense motion when connecting to app
// the reason we have to do this is cause we have to get user input to sound the buzzer
// in senseMotion() the buzzer would sound as soon as motion is detected this output is not what we desire
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
