
🚗 IoT Vehicle Tracking & Theft Prevention System
ESP32 • NEO-6M GPS • MQTT • Node-RED • Blynk IoT • InfluxDB • Grafana

📌 1. Overview
This project is a complete, industry-oriented IoT Vehicle Tracking & Theft Prevention System designed using:

ESP32 DevKit V1

NEO-6M GPS Module

MQTT (HiveMQ / Mosquitto)

Node-RED Dashboard

Blynk IoT Mobile App

InfluxDB + Grafana Analytics

Relay-based Engine Immobilizer

The system supports real-time GPS tracking, remote engine lock/unlock, geofencing, speed alerts, and multi-channel notifications.

🎯 Industry Relevance
Similar functionality is used by:

Bosch Mobility

Tata Telematics

Fleet Complete

LocoNav

MapMyIndia Fleet

This makes the project resume-ready, interview-ready, and deployment-ready.

🚀 2. Features
✔ Real-time GPS tracking (lat, lon, speed)
✔ MQTT cloud telemetry (HiveMQ / Mosquitto)
✔ Blynk IoT mobile app: LOCK/UNLOCK, live speed + push alerts
✔ Geofencing (radius-based alerts)
✔ Theft detection (movement while locked)
✔ Node-RED web dashboard
✔ InfluxDB storage + Grafana historical analytics
✔ Relay-based engine immobilizer
✔ Optional GSM (SIM800L) fallback SMS alerts
✔ Professionally structured repo with CI, docs & screenshots

📡 3. System Architecture
less
Copy code
         ┌───────────────┐
         │   GPS NEO-6M   │
         └───────┬───────┘
                 │ UART
                 ▼
         ┌─────────────────┐
         │     ESP32       │
         │ (Firmware: MQTT │
         │   + Blynk IoT)  │
         └───────┬────────┘
            WiFi │
                 ▼
        ┌──────────────────┐
        │    MQTT Broker    │
        │ HiveMQ / Mosquitto│
        └────────┬─────────┘
                 │ Pub/Sub
                 ▼
   ┌───────────────────────────┐
   │        Node-RED UI        │
   │ Maps, Speed, Lock Control │
   └───────────┬──────────────┘
               │ Writes
               ▼
     ┌─────────────────────┐
     │     InfluxDB        │
     └─────────┬───────────┘
               │ Queries
               ▼
     ┌─────────────────────┐
     │      Grafana        │
     │  Speed + Route logs │
     └─────────────────────┘

                 (Parallel)
                 ▼
      ┌────────────────────┐
      │   Blynk IoT App    │
      │ Mobile Alerts +    │
      │ Lock/Unlock Button │
      └────────────────────┘
🔧 4. Hardware Requirements
Component	Purpose	Notes
ESP32 DevKit V1	Main controller	WiFi, UART
NEO-6M GPS	Location fix	9600 baud
Relay Module	Engine lock	5V, opto-isolated
Buck Converter	Vehicle power	12V → 5V
Buzzer & LED	Alerts	Optional
SIM800L (optional)	GSM SMS fallback	Needs 4V 2A

Pin Mapping
GPS TX → GPIO16

GPS RX → GPIO17

Relay → GPIO25

Buzzer → GPIO26

LED → GPIO27

💻 5. Firmware
Two full sketches included:

bash
Copy code
code/esp32_tracker/vehicle_tracker.ino             (MQTT version)
code/esp32_tracker/vehicle_tracker_blynk.ino       (MQTT + Blynk hybrid)
Features:

Reads GPS (TinyGPSPlus)

Publishes GPS data via MQTT

Handles LOCK/UNLOCK commands

Performs geofencing + theft detection

Sends Blynk push notifications

Controls relay immobilizer

🌐 6. Cloud Dashboards
Node-RED Flow
Location:

bash
Copy code
code/node-red/flow_vehicle_tracker.json
Provides:

Live GPS data

Map widget

Speed gauge

Lock/Unlock buttons

Alerts

Grafana Analytics
Location:

bash
Copy code
code/grafana/dashboard.json
Graphs:

Speed over time

Route history (via InfluxDB Geo queries)

🔔 7. Alert System
Trigger conditions:

Exiting geofence radius

Vehicle moving while engine locked

Speed > 5 km/h when locked

Alert channels:

Blynk push notifications

Node-RED Telegram Bot

Twilio (SMS/WhatsApp)

GSM fallback (SIM800L AT commands)

🔌 8. Power & Installation
Use inline 1–3A fuse on vehicle 12V line

Convert to 5V using automotive buck converter

Do NOT drive vehicle starter motor directly with relay

Enclose ESP32 + GPS in dashboard area

Keep GPS antenna near windshield

🧪 9. Testing & Validation
GPS outdoor fix test

MQTT publish/subscribe test

LOCK/UNLOCK relay test

Geofence breach simulation via mosquitto_pub

Grafana data retention test

Mobile Blynk dashboard test

📁 10. Repository Structure
css
Copy code
iot-vehicle-tracker/
├── code/
│   ├── esp32_tracker/
│   ├── node-red/
│   └── grafana/
├── docs/
├── data/
├── demo/
├── screenshots/
├── .github/
├── LICENSE
├── .gitignore
└── README.md
🎥 11. Demo Script
Found in:

bash
Copy code
demo/demo_script.md
Includes:

What to show in viva

Commands for MQTT tests

Screenshot plan

📘 12. Resume Highlights
pgsql
Copy code
• Built a production-style IoT Vehicle Tracking System using ESP32, MQTT, Node-RED, Blynk IoT, and Grafana.
• Implemented GPS telemetry, geofencing, and theft detection algorithms.
• Designed cloud dashboards and analytics pipeline (InfluxDB + Grafana).
• Developed mobile app controls for engine lock and movement alerts.
• Built safe automotive power system using fused buck converter and relay isolation.
📄 13. License
nginx
Copy code
MIT License
🙌 14. Author
Sayli – Electrical Engineering
Industry-inspired IoT & Embedded Systems Engineer
