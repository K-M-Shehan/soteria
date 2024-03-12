# This is a test - not related to the main functions and folders

To find the IP address of the server in a local network:

**Serial Monitor Output:**

If you are using the Arduino IDE and have the ESP8266 connected to your computer, open the Arduino IDE, upload the code to the ESP8266, and open the Serial Monitor. When the ESP8266 connects to the WiFi network, it will print its assigned IP address to the Serial Monitor.

```c
Serial.println(WiFi.localIP());
```
