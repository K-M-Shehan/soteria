#include "/media/g0602/New Volume/SLIIT_DOCs/Y1S1/Computational Thinking/soteria/esp8266-01/wi_fi/ssid.h" //you need to add the absolute link of this file here


WiFiServer unit_server(unitPort); // port to connect with the sub units

WiFiClient clients[maxUnits]; // Array to store client objects
bool clientActive[maxUnits] = {false}; // Array to track active clients

bool syStatus = 1; //This indicate whether to sound the buzzer or not
bool buzStatus = 1; //This indicate whether to sound the buzzer or not
bool buzzzVal = 0; //This value help to manually sound the buzzer

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(10);
  
  // connect to the blynk cloud via internet
  Blynk.begin(auth, ssid, ssid_pw);


	// Start the server
  unit_server.begin();
  Serial.println("Server started");
}

BLYNK_WRITE(V0) {
  syStatus = param.asInt(); // getting values from the app and assining them to the variables
  Serial.println("V0 = " + String(syStatus));
}

BLYNK_WRITE(V1) {
  buzStatus = param.asInt(); // getting values from the app and assining them to the variables
  Serial.println("V0 = " + String(buzStatus));
}

BLYNK_WRITE(V2) {
  buzzzVal = param.asInt(); // getting values from the app and assining them to the variables
  Serial.println("V0 = " + String(buzzzVal));
}

void loop() {
  Blynk.run();

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
            Blynk.virtualWrite(V3, int(request[1])); // Send notification to Blynk app
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

  while(buzzzVal){
    for (int i = 0; i < maxUnits; i++){
      clients[i].println('1');
    }
    Serial.println("Buzzzing........");
    Blynk.run();
  }
}