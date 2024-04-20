/*
This file is for the ESP 01  wifi module to identify an intruder
and to sound the buzzer to warn the intruder and inform the user about the user about
the intruder via sounding the buzzer
*/

#include <ESP8266WiFi.h>
#include "../wi_fi/ssid.h"
#include "../wi_fi/wi_fi.h"
#include "localio.h"

// Declaring GPIO 0 and GPIO 2 as buzzer and pir pins
const int pir = 0;
const int buzzer = 2;

//setting this esp-01 as the client
WiFiClient client;

//Bellow this sound setup and the main loop is declared.
void setup() {
  Serial.begin(115200);

  // Set pir as input and buzzer as output
  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);

  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  connectToWiFi(ssid, ssid_pw);

  // Connect to the server
  Serial.print("Connecting to server: ");
  Serial.println(serverIp);

  if (client.connect(serverIp, serverPort)) {
    /*make some kind of sound to indicate the connection is sucesfull
    
    Once connected, send data to the server
    client.println("Hello from client");*/

  } else {
    //make some kind of sound to indicate the connection is not sucesfull
  }
}
 
void loop() {
  Serial.print("PIR Sensor Values: ");
  senseMotion(pir, buzzer);
  delay(1000);
}
