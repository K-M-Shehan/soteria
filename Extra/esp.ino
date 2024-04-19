#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// IP address and port of your app server
const char* serverIP = "192.168.1.100"; // Replace with your app server's IP address
const int serverPort = 80; // Replace with the port your app server is listening on

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Make a GET request to the app server
    HTTPClient http;
    http.begin("http://" + String(serverIP) + ":" + String(serverPort) + "/data"); // Specify the endpoint on your app server
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println("Received payload: " + payload);
      // Process the received data as needed
    } else {
      Serial.print("Error in HTTP GET request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(5000); // Adjust the delay as needed
}
