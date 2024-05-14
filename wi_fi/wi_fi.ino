//codes needed to connect to a wifi network are defined here

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "/media/g0602/New Volume/SLIIT_DOCs/Y1S1/Computational Thinking/soteria/esp8266-01/wi_fi/ssid.h" //you need to add the absolute link of the "ssid.h" file here 


// Function to connect to WiFi network
void connectToWiFi(const char* ssid, const char* password) {
	// Connect to WiFi network
	WiFi.begin(ssid, password);
	Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

	while (WiFi.status() != WL_CONNECTED) {
	  delay(500);
	  Serial.print(".");
	}
	Serial.println("\nConnected to WiFi");
	// Print ESP8266 local IP address
	Serial.print("The local ip address is: ");
	Serial.println(WiFi.localIP());
}