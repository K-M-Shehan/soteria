const int buzzer1 = 10;
const int buzzer2 = 9;
const int pir1 = 8;
const int pir2 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
}

void loop() {
  int pirValue1 = digitalRead(pir1);
  int pirValue2 = digitalRead(pir2);

  Serial.println("Send 'Y' to activate the buzzer.");
  

  if (pirValue1 == HIGH || pirValue2 == HIGH) {
    char userInput = Serial.read();
    while (Serial.available() == 0) {
  // Wait for user input
}
    if (userInput == 'Y' || userInput == 'y') {
      Serial.println("Permission granted! Activating the buzzer.");
      soundBuzzer(buzzer1 | buzzer2);
    } else {
      Serial.println("Permission denied. Buzzer remains inactive.");
    }
  }

  // Call the function to sense motion
  senseMotion(pirValue1, pirValue2);
}

void senseMotion(int pirValue1, int pirValue2) {
  if (pirValue1 == HIGH || pirValue2 == HIGH) {
    Serial.println("Motion Detected!");
  } else {
    Serial.println("No Motion");
  }
}

void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 200);
  digitalWrite(buzzer, LOW);
}
