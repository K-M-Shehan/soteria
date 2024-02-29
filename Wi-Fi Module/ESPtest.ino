#include <ESP8266WiFi.h>

const char* ssid = "Joyboy";
const char* password = "Onepieceispeakfiction";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // Echo back to client
      }
    }

    Serial.println("Client disconnected");
  }
}
