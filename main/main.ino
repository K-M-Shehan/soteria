/*
This code will be programmed into the main Arduino board and
this will help the Arduino to communicate through wifi with other ESP 01s (units)
currently, this is unedited
*/

#include <SoftwareSerial.h>

// Define the ESP-01 RX and TX pins
#define ESP_RX 2   // Connect to TX pin of ESP-01
#define ESP_TX 3   // Connect to RX pin of ESP-01

// Set up software serial communication with ESP-01
SoftwareSerial espSerial(ESP_RX, ESP_TX);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Start software serial communication with ESP-01
  espSerial.begin(9600);
  
  // Initialize ESP-01
  espSerial.println("AT");
  delay(1000); // Wait for ESP-01 to respond
  
  // Check if ESP-01 is responding
  if (espSerial.find("OK")) {
    Serial.println("ESP-01 initialized successfully");
  } else {
    Serial.println("Error initializing ESP-01");
    while (1); // Loop indefinitely if ESP-01 initialization fails
  }
  
  // Connect to WiFi network
  connectToWiFi("YourWiFiSSID", "YourWiFiPassword");
}

void loop() {
  // Check for data from WiFi
  if (espSerial.available()) {
    Serial.write(espSerial.read());
  }
  
  // Check for data from Serial Monitor
  if (Serial.available()) {
    espSerial.write(Serial.read());
  }
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

