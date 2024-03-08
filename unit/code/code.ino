/*
This file is for the ESP 01  wifi module to identify an intruder
and to sound the buzzer to warn the intruder and inform the user about the user about
the intruder via sounding the buzzer
*/

// Declaring GPIO 0 and GPIO 2 as buzzer and pir pins
const int buzzer = 0;
const int pir = 2;

// Function prototypes
void soundBuzzer(int buzzer);
void senseMotion(int pir, int buzzer);


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
  delay (1000);
}

// declaring soundBuzzer function
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 1000);
}

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
