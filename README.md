THIS BRANCH IS TO USE TO USE BLYNK TO CREATE APP AND CONTROL THE SYSTEM

# soteria

## Overview
This project implements a door security system using PIR sensor, buzzer module, and ESP8266 WiFi module. The system detects human presence in front of the door, sends real-time alerts to a mobile device, and allows users to make decisions and take appropriate actions.

## Features
* Human presence detection using PIR sensor
* Real-time alerts sent to mobile device via WiFi
* User decision-making through mobile app
* Buzzer activation to deter intruders
* Cost-effective and easy to install


## Hardware Requirements
* PIR Sensors (HC-SR501 module for Arduino)
* Buzzer Module (3.3 to 5V Active Buzzer Alarm Module Sensor)
* Wi-Fi Module (ESP8266 ESP-01 Serial WIFI Wireless Module)
* USB to ESP8266 ESP-01 Interface Module
* Breadboard (large)
* M-F, M-M, F-F jumper cables
* Switch


## Software Requirements
* Arduino IDE
* ESP8266WiFi library
* Additional libraries as needed for specific components

## Installation and Setup
1. <b>Hardware Setup:</b>
    * Connect the components according to the circuit shown below.
    * Ensure all connections are secure and properly powered.

2. <b>Software Setup:</b>
    * Install the Arduino IDE if not already installed.
    * Install the required libraries using the Arduino Library Manager.
    * Clone the repo and compile the code with the Arduino IDE.
    * Upload the code from the esp8266-01 directory to relevant units using the USB module.

3. <b>WiFi Configuration:</b>
    * Update the WiFi credentials in the wifi directory with your network SSID and password.
    * Adjust any other settings in the code as needed.

4. <b>Testing:</b>
    * Test the system to ensure proper functionality.
    * Verify human presence detection, alert notifications, and user interactions.
    
## Usage
* When a human presence is detected, the system sends a real-time alert to the configured mobile device.
* The user can choose to activate the buzzer to deter intruders or ignore the alert.
* Regularly monitor the system and perform maintenance as needed.

## Contributing
Contributions to improve the project are welcome! Feel free to fork the repository, make changes, and submit a pull request.

