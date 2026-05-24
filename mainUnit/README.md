# Main Unit (Gateway) — Documentation

## Overview
This sketch runs on the main ESP8266 unit. It acts as a TCP server that accepts connections from multiple ESP‑01 sub units, processes motion reports from them, and forwards events to the Blynk cloud (mobile app). It also sends simple control replies back to each connected unit to control buzzer behaviour.

### What this file contains
- Server logic that accepts unit connections on `unitPort` (default 8080).
- Blynk client integration using the auth token in `wi_fi/ssid.h`.
- Virtual pin handlers for system enable/disable and buzzer controls (`V0`, `V1`, `V2`).

## Hardware / Board
- Target: ESP8266 (ESP-01 or similar). Using a development board (NodeMCU / Wemos) is recommended for easier flashing and debugging.
- Wi‑Fi connection and Blynk require `ESP8266WiFi` and `BlynkSimpleEsp8266` libraries.

Project layout (relevant files)
- `mainUnit.ino` — main gateway sketch (this folder).
- `../wi_fi/ssid.h` — Wi‑Fi and Blynk credentials and shared constants (do NOT commit secrets).
- `../subUnit/` — unit/ESP-01 code that connects to this server.

## How it works (runtime)
1. On boot the main unit connects to Wi‑Fi and Blynk using the `auth`, `ssid`, `ssid_pw` values in `wi_fi/ssid.h`.
2. The sketch starts a `WiFiServer` on `unitPort` and listens for incoming unit connections.
3. When a connected unit sends a motion report (single-byte message), the main unit:
	- Logs the event on Serial
	- Calls `Blynk.virtualWrite(V3, 1)` and `Blynk.logEvent("motion_detected")` to trigger the app notification
	- Sends a reply byte to the unit indicating buzzer action (`'1'`, `'0'`, or `'2'`).

## Blynk interaction (quick)
- `V0` — System enable/disable (sets `syStatus`).
- `V1` — Buzzer automatic/manual mode (sets `buzStatus`).
- `V2` — Manual buzzer trigger (sets `buzzzVal`).
- `V3` — Motion indicator (main writes `1` briefly when motion detected).

## Notes and recommendations
- Replace absolute include paths with a relative include or copy `ssid.h` into the sketch folder before compiling. Example: `#include "../wi_fi/ssid.h"`.
- Do not commit `wi_fi/ssid.h` with real SSID/password/Blynk auth token. Use a `ssid_example.h` and add `ssid.h` to `.gitignore`.
- Improve message parsing: the sketch currently indexes message bytes in a fragile way; prefer `char c = msg.charAt(0)` or `client.read()` for more robust single-byte handling.
- Add reconnect/backoff logic for clients and Blynk if deploying to unreliable networks.

## Troubleshooting
- If units do not connect, confirm `unitPort` and `serverIp` in `wi_fi/ssid.h` match the main unit's IP and listening port.
- If Blynk does not connect, confirm the `auth` token and that the device has internet access.

## Flashing and testing
1. Ensure `wi_fi/ssid.h` is present and filled with correct values (see `wi_fi/BLYNK_SETUP.md`).
2. Select the correct board and flash settings for your ESP8266 in the Arduino IDE.
3. Open Serial Monitor at 115200 to observe logs, IP address, and client connections.
