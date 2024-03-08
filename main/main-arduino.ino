#include <Wire.h>
#include <ESP8266WiFi.h>

// Define pins for components
const int pirSensorPin = 2;
const int buzzerPin = 3;

// WiFi credentials
const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";

void setup() 
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize components
  pinMode(pirSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Connect to WiFi
  connectToWiFi(ssid, password);
}

void loop() 
{
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
  }
}

void connectToWiFi(const char* ssid, const char* password) 
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
}

bool detectHumanPresence() 
{
  // this code detects human presence using the PIR sensor
  // Return true if human is detected, false otherwise
  int pirValue = digitalRead(pirSensorPin);
  if(pirValue == HIGH) 
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

void activateBuzzer() 
{
  // this code activates the buzzer
  tone(buzzerPin, 1000, 500);
  digitalWrite(buzzerPin, LOW);
}

void monitorHumanPresence() 
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

void deactivateBuzzer() 
{
  // this code deactivates the buzzer
  noTone(buzzerPin);
}

