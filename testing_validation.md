# Testing & Validation

Bench Tests:
1. GPS Fix: Place GPS outdoors; verify NMEA sentences and lat/lon via Serial Monitor.
2. MQTT: Use mosquitto_pub/sub to verify topics (vehicle/vehicle001/data, /control, /alert).
3. Relay: Test relay with indicator lamp before connecting to vehicle circuits.
4. Geofence: Simulate movement via mosquitto_pub to topic vehicle/vehicle001/data with coordinates outside geofence.

Example MQTT simulation command:
mosquitto_pub -h broker.hivemq.com -t vehicle/vehicle001/data -m '{"lat":12.9800,"lon":77.6030,"speed":22,"locked":true}'

On-Vehicle Validation:
- Connect safely with fuse and test immobilizer control.
- Verify alerts and Blynk notifications.

Troubleshooting tips:
- No GPS fix: check antenna, move outdoors, verify baud 9600.
- MQTT connection fails: check broker address and port; use mosquitto_sub to debug.
