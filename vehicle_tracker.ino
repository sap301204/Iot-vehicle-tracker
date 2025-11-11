/*
 vehicle_tracker.ino - ESP32 Vehicle Tracking & Theft Prevention System (MQTT)
 Libraries required:
  - TinyGPSPlus
  - PubSubClient
  - WiFi.h
 Replace WIFI_SSID and WIFI_PASS and optionally MQTT_SERVER and VEHICLE_ID
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <TinyGPSPlus.h>

// ---------- CONFIG ----------
const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASS = "YOUR_PASS";

const char* MQTT_SERVER = "broker.hivemq.com";
const uint16_t MQTT_PORT = 1883;
const char* VEHICLE_ID = "vehicle001";

const int RELAY_PIN = 25;     // Relay control pin
const int BUZZER_PIN = 26;    // Buzzer pin
const int LED_PIN = 27;       // Status LED pin

// Geofence center (set to parked coordinates)
const double GEOFENCE_LAT = 12.971600;
const double GEOFENCE_LON = 77.594600;
const double GEOFENCE_RADIUS_METERS = 200.0;

// GPS on UART2
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// MQTT topics
String topic_data    = String("vehicle/") + VEHICLE_ID + "/data";
String topic_control = String("vehicle/") + VEHICLE_ID + "/control";
String topic_status  = String("vehicle/") + VEHICLE_ID + "/status";
String topic_alert   = String("vehicle/") + VEHICLE_ID + "/alert";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

bool engine_locked = false;
unsigned long lastPublish = 0;
const unsigned long PUBLISH_INTERVAL_MS = 3000;

// Haversine distance (meters)
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
  const double R = 6371000.0;
  double dLat = (lat2 - lat1) * DEG_TO_RAD;
  double dLon = (lon2 - lon1) * DEG_TO_RAD;
  double a = sin(dLat/2)*sin(dLat/2) + cos(lat1*DEG_TO_RAD)*cos(lat2*DEG_TO_RAD)*sin(dLon/2)*sin(dLon/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  return R * c;
}

void buzzAlert(int ms) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(ms);
  digitalWrite(BUZZER_PIN, LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i=0; i<length; i++) msg += (char)payload[i];
  msg.trim();
  if (String(topic) == topic_control) {
    if (msg.equalsIgnoreCase("LOCK")) {
      digitalWrite(RELAY_PIN, LOW); // change logic to match your relay
      engine_locked = true;
      mqttClient.publish(topic_status.c_str(), "Engine Locked");
    } else if (msg.equalsIgnoreCase("UNLOCK")) {
      digitalWrite(RELAY_PIN, HIGH);
      engine_locked = false;
      mqttClient.publish(topic_status.c_str(), "Engine Unlocked");
    }
  }
}

void reconnect() {
  while (!mqttClient.connected()) {
    String clientId = "ESP32_" + String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str())) {
      mqttClient.subscribe(topic_control.c_str());
      mqttClient.publish(topic_status.c_str(), "Node Online");
    } else {
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // default unlocked
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("[WIFI] Connecting");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(500); Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WIFI] Connected");
    Serial.print("[WIFI] IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n[WIFI] Not connected - will attempt MQTT when available");
  }

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!mqttClient.connected()) reconnect();
    mqttClient.loop();
  }

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid() && gps.location.isUpdated()) {
    unsigned long now = millis();
    if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
      lastPublish = now;
      double lat = gps.location.lat();
      double lon = gps.location.lng();
      double spd = gps.speed.kmph();

      String payload = "{"lat":" + String(lat,6) + ","lon":" + String(lon,6) + ","speed":" + String(spd,2) + ","locked":" + String(engine_locked ? "true":"false") + "}";
      Serial.print("[MQTT] "); Serial.println(payload);
      if (mqttClient.connected()) mqttClient.publish(topic_data.c_str(), payload.c_str());

      // geofence logic
      double dist = haversineDistance(GEOFENCE_LAT, GEOFENCE_LON, lat, lon);
      if (dist > GEOFENCE_RADIUS_METERS && engine_locked) {
        String alert = "ALERT: Vehicle moved while locked. Dist(m): " + String(dist,1);
        if (mqttClient.connected()) mqttClient.publish(topic_alert.c_str(), alert.c_str());
        for (int i=0;i<3;i++) { buzzAlert(150); delay(100); }
      }

      if (engine_locked && spd > 5.0) {
        String alert = "ALERT: Speed > 5 km/h while locked. Speed: " + String(spd,1);
        if (mqttClient.connected()) mqttClient.publish(topic_alert.c_str(), alert.c_str());
        for (int i=0;i<3;i++) { buzzAlert(150); delay(100); }
      }
    }
  }

  static unsigned long lastBlink=0;
  if (millis() - lastBlink > 1000) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    lastBlink = millis();
  }
}
