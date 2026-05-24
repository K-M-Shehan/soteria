# Sub Unit (ESP‑01) — Documentation

## Overview
Each sub unit is an ESP‑01 module that reads a PIR motion sensor and controls a buzzer. The unit connects to the main unit (gateway) over TCP and sends simple motion reports. The main unit replies with a control byte to tell the unit whether to sound the buzzer.

### What this file contains
- Code to read PIR sensor input and send motion states to the server.
- Buzzer control logic reacting to server replies (`'0'`, `'1'`, `'2'`).
- Wi‑Fi connection routine (uses values from `../wi_fi/ssid.h`).

## Hardware / Pins
- PIR sensor: connected to GPIO0 on the ESP‑01 in this sketch (pin labeled `0`).
- Buzzer: connected to GPIO2 (pin labeled `2`).

## Important hardware notes
- GPIO0 affects the ESP‑01 boot mode. Wiring a PIR directly to GPIO0 can hold the pin low and prevent normal booting or programming. Use a pull‑up resistor and verify PIR output behavior on boot, or use a different board with more GPIOs for reliable deployment.

## Protocol (unit ↔ main)
- Unit sends a single-character message to the server: `'1'` when motion detected, `'0'` otherwise.
- Main replies with a single character:
	- `'1'` — main instructs unit to sound buzzer automatically for this event
	- `'0'` — no buzzer (manual mode or disabled)
	- `'2'` — force buzzer (broadcasted when manual-trigger is active)

## Software notes / fixes to consider
- Cooldown bug: the sketch declares `lastMotionTime` and `motionCooldownPeriod` but does not update `lastMotionTime` when motion is sent. Add `lastMotionTime = currentTime;` after sending to enforce cooldown.
- Message parsing: current code indexes `reply[1]`/`request[1]` which is fragile. Use `String msg = client.readStringUntil('\r'); if (msg.length() && msg.charAt(0) == '1') ...` or better, read raw bytes with `client.read()`.
- Boot and GPIO: confirm PIR output idle state and add hardware pull-ups if needed.

## Flashing and testing
1. Populate `../wi_fi/ssid.h` with network and server details (see `wi_fi/BLYNK_SETUP.md`).
2. Use a USB‑to‑ESP01 adapter to flash the ESP‑01. Ensure GPIO0 is pulled low only during programming, then released for normal run.
3. Open Serial Monitor at 115200 to watch connection attempts and server replies.

## Debug tips
- Temporarily use a NodeMCU/WeMos board to test logic — these boards are easier to flash and debug than bare ESP‑01.
- If the unit repeatedly fails to connect to the server, confirm the main unit IP (`serverIp`) and port (`unitPort`) in `wi_fi/ssid.h`.