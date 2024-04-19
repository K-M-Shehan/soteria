#include <ESP8266WiFi.h>

// WiFi credentials
const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";

// Server IP address and port
IPAddress serverIP(192, 168, 1, 100); // Replace with the IP address of the server
const int serverPort = 80; // Use a port number that is not reserved

WiFiServer server(serverPort);

void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    // Read data from the client
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      // Process the received data as needed
    }

    // Respond to the client if needed
    client.print("Hello from Server!");

    // Close the connection
    client.stop();
  }
}

