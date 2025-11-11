# Alert System

Triggers (Node-RED):
- Geofence breach: (dist > GEOFENCE_RADIUS) && engine_locked
- Speed while locked: (engine_locked && speed > 5 km/h)
- GPS lost while moving: if last GPS > 60s and ignition detected

Delivery channels:
- Blynk.notify (push notification)
- Telegram bot (node-red-node-telegram)
- Twilio (node-red-contrib-twilio) for SMS/WhatsApp
- GSM fallback: ESP32 -> UART -> SIM800L AT commands to send SMS (AT+CMGS)

Node-RED flow example:
- Subscribe to vehicle/<id>/data -> function (check geofence) -> if alert -> publish vehicle/<id>/alert and call Telegram/Twilio nodes.
