# Power & Installation

- Use inline fuse (1-3A) next to vehicle battery on the 12V feed.
- Use an automotive-grade buck converter (e.g., LM2596 but rated for automotive use) to step 12V to 5V for ESP32 and relay VCC.
- SIM800L needs a stable 4.0V supply capable of 2A peaks; DO NOT power SIM800L from ESP32 5V regulator directly.
- Provide common ground between all modules.
- Enclosure: mount electronics under dash in ventilated, vibration-damped enclosure.
- Optional Li-ion backup with charger/protection to allow alerts on main power loss.
