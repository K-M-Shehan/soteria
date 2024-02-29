void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.write(c); // Echo back to ESP8266
  }
}
