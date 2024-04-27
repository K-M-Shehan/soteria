#include <ESP8266WiFi.h>
#include "/media/g0602/New Volume/SLIIT_DOCs/Y1S1/Computational Thinking/soteria/esp8266-01/wi_fi/ssid.h" //you need to add the absolute link of this file here

WiFiServer unit_server(unitPort); // port to connect with the sub units
WiFiServer app_server(appPort); // port to connect with the app

WiFiClient clients[maxUnits]; // Array to store client objects
bool clientActive[maxUnits] = {false}; // Array to track active clients

bool status = 1; //This indicate whether to sound the buzzer or not

void setup() 
{
  // Initialize serial communication
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  connectToWiFi(ssid, ssid_pw);


	// Start the server
  unit_server.begin();
  app_server.begin();
  Serial.println("Server started");
}

void loop() 
{
  WiFiClient app = app_server.available();

  if (app.connected()) {
    if (app.available()) {
      String command = app.readStringUntil('\r');

      switch(command[1]){
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        default : break;
      }
    }
  }

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
          
          // Process the received data
          if (request[1]== '1'){
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
}