#include <ESP8266WiFi.h>

// WiFi credentials
const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";

// Server IP address and port
IPAddress serverIP(192, 168, 1, 100); // Replace with the IP address of the server
const int serverPort = 80; // Use the same port as the server

void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
}

void loop() {
  // Connect to the server
  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    // Send data to the server
    client.print("Hello from Client!");
    
    // Read the server's response
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      // Process the received data as needed
    }

    // Close the connection
    client.stop();
  }

  delay(5000); // Adjust the delay based on your needs
}

void connectToWiFi(const char* ssid, const char* password) {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

