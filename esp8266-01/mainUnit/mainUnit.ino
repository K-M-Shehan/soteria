#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "D:\SLIIT\Computational Thinking First Project\New folder\soteria\esp8266-01\wi_fi\ssid.h" //you need to add the absolute link of this file here

WiFiServer unit_server(unitPort); // port to connect with the sub units

WiFiClient clients[maxUnits]; // Array to store client objects
bool clientActive[maxUnits] = {false}; // Array to track active clients

bool syStatus = 1; //This indicate whether to sound the buzzer or not
bool buzStatus = 1; //This indicate whether to sound the buzzer or not

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

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  connectToWiFi(ssid, ssid_pw);


	// Start the server
  unit_server.begin();
  Serial.println("Server started");
}

void loop() {
  Blynk.run();

  syStatus = Blynk.virtualRead(V0);
  buzStatus = Blynk.virtualRead(V1); // grtting values from the app and assining them to the variables

	WiFiClient newClient = unit_server.available();

	//following code only run if any new client is available on unitPort
  if (newClient) {
    // Find an empty slot in the clients array
    for (int i = 0; i < maxUnits; i++) {
      if (!clientActive[i]) {
        clients[i] = newClient;
        clientActive[i] = true;
        Serial.println("New client connected");
        break;
      }
    }
  }

  // Handle each connected client
  for (int i = 0; i < maxUnits; i++) {
    if (clientActive[i]) {
      if (clients[i].connected()) {
        if (clients[i].available()) {
          String request = clients[i].readStringUntil('\r');
          Serial.println("Received from client " + String(i) + ": " + request[1]);

          if (request[1]== '1'){
            Serial.println("Motion detected from unit \"" + String(i +1)+ "\"");
            Blynk.notify("Motion detected from unit \"" + String(i +1)+ "\""); // Send notification to Blynk app
          }

          if(syStatus == 0){
            clients[i].println('0');
            continue;
          }
          // Process the received data
          if ((request[1]== '1') && (buzStatus == 1)){
            clients[i].println('1');
          } else {
            clients[i].println('0');
          }
        }
      } else {
        // Client disconnected, clean up
        clients[i].stop();
        clientActive[i] = false;
        Serial.println("Client " + String(i) + " disconnected");
      }
    }
  }

  while(Blynk.virtualRead(V3)){
    for (int i = 0; i < maxUnits; i++){
      clients[i].println('1');
    }
  }
}