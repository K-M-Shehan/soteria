//This file contains all the functions mentionend in the local.h header file

// declaring soundBuzzer function for the buzzer module
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 500);
  delay(1000);
}

// declaring senseMotion function for pir sensor
void action(char reply) {
  if(reply == '1') {
    soundBuzzer(buzzer);//hear the unit need to send the 
    Serial.println("Motion Detected!");
  }
  else {
    noTone(buzzer);
    Serial.println("No Motion");
  }
}
