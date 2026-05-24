# Blynk Setup Guide for Soteria Project

## Overview
This document explains how to configure the Blynk project (mobile app / cloud) so the main unit can send notifications and you can control buzzer/system behavior.

### Steps
1. Install the Blynk app (iOS or Android).
2. Create a new Template or Project (the code references a template id in `wi_fi/ssid.h` but you can also use an old-style project):
   - If using Template: note Template ID and Template Name.
3. Add widgets to the project with these virtual pin mappings:
   - V0: Value/Toggle — System enable/disable (sets `syStatus`) — use a Switch widget.
   - V1: Value/Toggle — Buzzer automatic/manual mode (sets `buzStatus`) — use a Switch widget.
   - V2: Button — Manual buzzer trigger (sets `buzzzVal`) — use a PushButton.
   - V3: LED or Value — Motion indicator (main writes `1` briefly on motion).
4. Configure Notifications / Events:
   - In the Blynk Console (or in the Template -> Events), create an event named `motion_detected` (the sketch calls `Blynk.logEvent("motion_detected")`).
   - Configure the event to send a push notification, email, or other action when it is triggered.
5. Obtain your Auth Token:
   - In the single project flow: press the share/code icon to get the device Auth Token.
   - In Template flow: retrieve the Auth Token for the device instance or use device provisioning flow.
6. Populate `wi_fi/ssid.h`:
   - Open `wi_fi/ssid.h` and set `const char auth[]` to your auth token, set `ssid` and `ssid_pw` to your Wi‑Fi SSID and password. Also confirm `serverIp` and `unitPort` match your main unit network configuration.
7. Test the integration:
   - Boot the main unit (with filled `ssid.h`) and open Serial Monitor. Confirm Blynk connects and shows online.
   - Boot a sub unit and trigger PIR motion — you should see motion events in the main unit Serial log and receive the notification configured for `motion_detected`.

## Security note
- Do not commit `wi_fi/ssid.h` with real credentials or the Blynk auth token to public repositories. Use `ssid_example.h` with placeholders in the repo and ignore the real `ssid.h` via `.gitignore`.

## Advanced
- If you want tighter control, modify the main unit to send richer JSON payloads to Blynk or to call `Blynk.notify()` directly.