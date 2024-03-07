/*
This file is for the ESP 01  wifi module to identifi an intruder
and to sound the buzzer to warn the intruder and to inform the user about the user about
the intruder via sounding the buzzer
*/

// Declaring GPIO 0 and GPIO 2 as buzzer and pir pins
const int buzzer = 0;
const int pir = 2;

// declaring senseMotion function
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

// declaring soundBuzzer function
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 500);
  digitalWrite(buzzer, LOW);
}


//Bellow this sound setup and  main loop is declared.
void setup() {
  Serial.begin(9600);
  // Set pir as input and buzzer as output
  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
  Serial.print("PIR Sensor Values: ");
  // the below function prints a msg in the serial monitor if motion is sensed
  // then soundBuzzer function is what makes the buzzer make noises
  senseMotion(pir, buzzer);
  delay(2000);
}


