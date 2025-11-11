# Hardware Setup & Wiring

Components:
- ESP32 DevKit v1 (ESP-WROOM-32) - MCU with Wi-Fi and multiple UARTs.
- NEO-6M GPS module - TTL UART, 3.3V/5V compatible (antenna required).
- 1-channel Relay Module (5V, opto-isolated recommended) - for immobilizer control.
- Active buzzer and LED - alerts and status.
- SIM800L (optional) - GSM for SMS fallback; requires 4V 2A supply.
- Buck converter (12V -> 5V) - to power ESP32 and relay module.
- Inline fuse (1-3A) near battery.

Pin Mapping (recommended):
- NEO-6M TX -> ESP32 RX2 (GPIO16)
- NEO-6M RX -> ESP32 TX2 (GPIO17)
- RELAY IN -> ESP32 GPIO25
- BUZZER -> ESP32 GPIO26 (use transistor if needed)
- LED -> ESP32 GPIO27 (with resistor)
- Power: 12V -> fuse -> buck converter -> 5V -> ESP32 VIN (or V5)
- Grounds must be common.

Safety Notes:
- Do not switch starter motor current with this relay. Use relay to control immobilizer/ignition-sense line.
- Use fuse and opto-isolation where possible.
