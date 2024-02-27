const int buzzer1 = 10;
const int buzzer2 = 9;
const int pir1 = 8;
const int pir2 = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("PIR Sensor Values: ");
  
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
