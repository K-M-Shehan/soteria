//codes needed to connect to a wifi network are defined here

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "wi_fi.h"
#include "ssid.h" // header file with wifi credentials


// Function to connect to WiFi network
void connectToWiFi(const char* ssid, const char* password) {
	// Connect to WiFi network
	WiFi.begin(ssid, password);

	Serial.print("Connecting to WiFi");
	while (WiFi.status() != WL_CONNECTED) {
	  delay(500);
	  Serial.print(".");
	}
	Serial.println("\nConnected to WiFi");
	// Print ESP8266 local IP address
	Serial.println(WiFi.localIP());
}