#include <ESP8266WiFi.h>
#include "../wi_fi/ssid.h"

// Define variables to store the  values we send and recieve through wi-fi
//int pirVal;
//int buzzerVal;


void setup() 
{
  // Initialize serial communication
  Serial.begin(115200);
  
  // Connect to WiFi
  connectToWiFi(ssid, ssid_pw);
}

void loop() 
{/*
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
