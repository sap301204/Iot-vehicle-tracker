# IoT Vehicle Tracking & Theft Prevention System

**Industry-oriented, ESP32-based vehicle tracker with GPS, MQTT telemetry, geofencing theft detection, remote engine lock/unlock, and alerting.**

## Features
- Real-time GPS telemetry (lat, lon, speed)
- MQTT publishing to cloud broker (HiveMQ, Mosquitto, ThingSpeak)
- Remote LOCK / UNLOCK via dashboard (Node-RED / Blynk)
- Geofencing and theft alert logic
- Twilio / Telegram / GSM alert fallback
- Route history storage in InfluxDB or Firebase
- Ready for GitHub upload and real hardware testing

## Hardware Requirements
- ESP32 DevKit v1
- NEO-6M GPS module
- 1-channel relay module (automotive-rated)
- Active buzzer and LED
- 12V → 5V buck converter
- Inline fuse (1–3A)
- Optional: SIM800L GSM module
- Wires, connectors, enclosure

## Wiring
See `docs/circuit_ascii.txt` and wiring notes in `docs/installation_notes.md`.

## Quick Start
1. Clone repo.
2. Install Arduino IDE and libraries:
   - TinyGPSPlus
   - PubSubClient
3. Update `vehicle_tracker.ino` with your `WIFI_SSID`, `WIFI_PASS`, and MQTT server.
4. Upload to ESP32 (select board: `ESP32 Dev Module`).
5. Start an MQTT broker (or use `broker.hivemq.com`).
6. Import Node-RED flow `code/node-red/flow_vehicle_tracker.json` into your Node-RED instance and configure MQTT node.
7. Power the device, wait for GPS fix, and monitor `vehicle/<id>/data` topic.

## Node-RED / Dashboard
- Topics:
  - `vehicle/<id>/data` (telemetry)
  - `vehicle/<id>/control` (LOCK/UNLOCK)
  - `vehicle/<id>/status` (node status)
  - `vehicle/<id>/alert` (alerts)
- Use map node (Google Maps or Leaflet) to show current position and route.

## Sample Data
See `data/sample_gps.csv` and `data/sample_mqtt_messages.json`.

## Troubleshooting
- GPS no fix: move outdoors, check antenna, check baud rate (9600).
- MQTT connection: verify broker address and port, test with `mosquitto_sub`.
- Relay not switching: verify relay Vcc and check wiring to the ignition line. Always use fuse.

## Safety & Legal
Do not modify vehicle critical systems without qualified authority. Using this system to cut ignition can be dangerous; ensure safety and legal compliance.

## License
MIT — see `LICENSE`.

## Contact
For help, open an issue or contact the repo owner.

