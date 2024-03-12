#include <Wire.h>
#include <SoftwareSerial.h>
#include "ssid.h"

// Define the ESP-01 RX and TX pins
#define ESP_RX 2   // Connect to TX pin of ESP-01
#define ESP_TX 3   // Connect to RX pin of ESP-01

// Define variables to store the  values we send and recieve through wi-fi
int pirVal;
int buzzerVal;

// Set up software serial communication with ESP-01
SoftwareSerial espSerial(ESP_RX, ESP_TX);

void setup() 
{
  // Initialize serial communication
  Serial.begin(9600);
  
  // Start software serial communication with ESP-01
  espSerial.begin(9600);

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
  // Send AT command to connect to WiFi
  espSerial.print("AT+CWJAP=\"");
  espSerial.print(ssid);
  espSerial.print("\",\"");
  espSerial.print(password);
  espSerial.println("\"");
  
  delay(5000); // Wait for connection
  
  // Check if connected to WiFi
  if (espSerial.find("OK")) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Error connecting to WiFi");
    while (1); // Loop indefinitely if WiFi connection fails
  }
}

// we need to figure out among the above code and the bellow code what is best way to connect to wifi

				/*void connectToWiFi(const char* ssid, const char* password) 
				{
				  // Connect to Wi-Fi
				  WiFi.begin(ssid, password);

				  // Wait for connection
				  while (WiFi.status() != WL_CONNECTED) 
				  {
					delay(1000);
					Serial.println("Connecting to WiFi...");
				  }

				  Serial.println("Connected to WiFi");
				}*/

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



