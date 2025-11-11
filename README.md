# IoT Vehicle Tracking & Theft Prevention System

**Complete industry-oriented project (ESP32 + NEO-6M GPS + MQTT + Node-RED + Blynk + InfluxDB/Grafana)**

**Contents:** firmware (MQTT and Blynk), Node-RED flow, Grafana dashboard, docs, sample data, demo scripts, presentation.

---

## Project Overview
This project implements a production-like vehicle tracking and theft prevention system using an ESP32 microcontroller, a GPS module (NEO-6M), MQTT for telemetry, a cloud dashboard (Node-RED + Blynk), and analytics (InfluxDB + Grafana). The system supports remote engine IMMOBILIZER control via a relay, geofencing-based theft detection, and multi-channel alerts (Blynk push, Telegram, Twilio).

**Industry relevance:** Fleet management, vehicle telematics, stolen vehicle recovery, and insurance telematics. Companies such as Bosch Mobility, Tata Telematics, and Fleet Complete offer similar services at scale.

## Quick Start (summary)
1. Edit `code/esp32_tracker/vehicle_tracker.ino` or `vehicle_tracker_blynk.ino` with your Wi-Fi and Blynk token.
2. Install Arduino libraries: TinyGPSPlus, PubSubClient, Blynk (if using Blynk).
3. Upload to ESP32 (Board: ESP32 Dev Module).
4. Run Node-RED, import flow, connect MQTT to broker.hivemq.com or your Mosquitto.
5. Optionally set up InfluxDB + Grafana and import dashboard JSON.

---
For full file list and detailed instructions see the repo files in this ZIP.
