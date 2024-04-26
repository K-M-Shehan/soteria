#include <ESP8266WiFi.h>
#include "/media/g0602/New Volume/SLIIT_DOCs/Y1S1/Computational Thinking/soteria/esp8266-01/wi_fi/ssid.h" //you need to add the absolute link of this file here

WiFiServer server(serverPort);

void setup() 
{
  // Initialize serial communication
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  connectToWiFi(ssid, ssid_pw);


	// Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() 
{
	WiFiClient client = server.available();

	//following code only run if the client is available
  if (client) {
    Serial.println("New client connected");
    // Read data from the client
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("Received: " + request);
        // Process the received data
        // You can send a response back to the client if needed
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
	}

	/*
  // Check for human presence
  if (detectHumanPresence()) 
  {
    // Alert user
    sendAlertToPhone();
    
    // User decision
    bool soundBuzzer = getUserDecision();

    // Sound the buzzer if required
    if (soundBuzzer) 
    {
      activateBuzzer();
      
      // Monitor human presence and check if user wants to escalate
      if (!monitorHumanPresence()) 
      {
        promptToCallPolice();
      }

      // Deactivate the buzzer
      deactivateBuzzer();
    }
  }*/
}


/*
bool detectHumanPresence() 
{
  // this code detects human presence using the PIR sensor
  // Return true if human is detected, false otherwise
  int pirVal= digitalRead(pirSensorPin);
  if(pirVal == HIGH) 
  {
    Serial.println("Motion Detected!");
    return true;
  }
  else 
  {
    Serial.println("No Motion");
    return false;
  }
}

void sendAlertToPhone() 
{
  // code to send an alert to the user's phone
}

bool getUserDecision() 
{
  // this code interacts with the user and get their decision
  // Return true if user wants to sound the buzzer, false otherwise
}

bool monitorHumanPresence() 
{
  // this code monitors human presence and return true if human is still present after 20 seconds
  if (detectHumanPresence()  == true)
  {
    delay(20000);
    if (detectHumanPresence()  == true)
      return true;
    else
      return false;
  } 
  else
    return false;
}

void promptToCallPolice() 
{
  // this code sends a prompt to the user's phone asking to call the police
}
*/