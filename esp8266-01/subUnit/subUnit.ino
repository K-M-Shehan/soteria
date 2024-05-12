/*
This file is for the ESP 01  wifi module to identify an intruder
and to sound the buzzer to warn the intruder and inform the user about the user about
the intruder via sounding the buzzer
*/

#include "/media/g0602/New Volume/SLIIT_DOCs/Y1S1/Computational Thinking/soteria/esp8266-01/wi_fi/ssid.h" //you need to add the absolute link of this file here

// Declaring GPIO 0 and GPIO 2 as buzzer and pir pins
const int pir = 0;
const int buzzer = 2;

const unsigned long motionCooldownPeriod = 2000; // Cooldown period in milliseconds
unsigned long lastMotionTime = 0;

//setting this esp-01 as the client
WiFiClient client;

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

// declaring soundBuzzer function for the buzzer module
void soundBuzzer(int buzzer) {
  tone(buzzer, 1000, 500);
  delay(1000);
}

// declaring senseMotion function for pir sensor
void action(char reply) {
  if(reply == '1') {
    soundBuzzer(buzzer);//hear the unit need to send the 
    Serial.println("Motion Detected!");
  }
  else {
    noTone(buzzer);
    Serial.println("No Motion");
  }
}

//Bellow this sound setup and the main loop is declared.
void setup() {
  Serial.begin(115200);
  delay(10);

  // Set pir as input and buzzer as output
  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);

  // Connect to WiFi defined in "../wi_fi/wi_fi.ino"
  connectToWiFi(ssid, ssid_pw);

  // Connect to the server
  Serial.print("Connecting to server: ");
  Serial.println(serverIp);
  while (!client.connect(serverIp, unitPort)) {
    Serial.println("Connection to server failed");
    delay(100);
  }
  Serial.println("Connected to server");
  tone(buzzer, 1000, 1000); // to indicate the server is connected
}
 
void loop() {
   // Sense motion and send PIR value to server
  int pirValue = digitalRead(pir);

  // to calculate time
  unsigned long currentTime = millis();

  if (pirValue == HIGH && ((currentTime - lastMotionTime) > motionCooldownPeriod)){
    client.println(1);
    Serial.println("sent : 1");
  } else {
    client.println(0);
    Serial.println("sent : 0");
  }

  // Check for reply from server
  if (client.available()) {
    String reply = client.readStringUntil('\r'); // Read a single character
    Serial.print("Server reply: ");
    Serial.println(reply[1]);

    action(reply[1]); // this will take action acording to the reply from the main unit

  } else {
    Serial.println("server is not available"); 
  }

  delay(500);
}
