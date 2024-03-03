// Buzzer 1 and PIR 1 is 1 unit and the same goes for the other 2
const int buzzer1 = 10;
const int buzzer2 = 9;
const int pir1 = 8;
const int pir2 = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Set PIR 1 and 2 as input and buzzers as output
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("PIR Sensor Values: ");
  // the below function prints a msg in the serial monitor if motion is sensed
  // the soundBuzzer function is what makes the buzzer make noises
  senseMotion(pir1, buzzer1);
  senseMotion(pir2, buzzer2);
  delay(500);
}

void senseMotion(int pir, int buzzer) {
  int pirValue = digitalRead(pir);
  if(pirValue == HIGH) {
    soundBuzzer(buzzer);
    Serial.println("Motion Detected!");
  }
  else {
    noMotion(buzzer);
    Serial.println("No Motion");
  }
}

void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 200);
  digitalWrite(buzzer, LOW);
}

void noMotion(int buzzer) {
  noTone(buzzer);
}
