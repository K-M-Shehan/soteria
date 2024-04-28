#include <ESP8266WiFi.h>
#include "D:\SLIIT\Computational Thinking First Project\New folder\soteria\esp8266-01\wi_fi\ssid.h" //you need to add the absolute link of this file here

WiFiServer unit_server(unitPort); // port to connect with the sub units
WiFiServer app_server(appPort); // port to connect with the app

WiFiClient clients[maxUnits]; // Array to store client objects
bool clientActive[maxUnits] = {false}; // Array to track active clients

bool syStatus = 1; //This indicate whether to sound the buzzer or not
bool buzStatus = 1; //This indicate whether to sound the buzzer or not

void connectToWiFi(const char* ssid, const char* password);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  //connectToWiFi(ssid, ssid_pw);


	// Start the server
  unit_server.begin();
  app_server.begin();
  Serial.println("Server started");
}

void loop() 
{
  WiFiClient app = app_server.available();
  if (app){
    Serial.println("App connected");
    if (app.connected()) {
      if (app.available()) {
        String command = app.readStringUntil('\r');
        Serial.println("Received from app: " + command[1]);

        switch(command[3]){
          case '1': syStatus = 1;//this indicate theat the system is online
                  break;
          case '2': syStatus = 0;//this indicate theat the system is offline
                  break;
          case '3': buzStatus = 1;//this indicate theat the buzzer is online
                  break;
          case '4': buzStatus = 0;//this indicate theat the buzzer is offline
                  break;
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
}