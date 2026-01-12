/*
  Proiect: Urmarirea inteligenta a cartilor în biblioteca
  Disciplina: Proiect Sincretic I A
  Componenta: Client embedded (ESP32)

  Rol:
  - Citeste UID-ul tag-urilor RFID atasate cartilor
  - Trimite evenimente prin protocolul MQTT catre broker
  - Reprezinta punctul de scanare din biblioteca

  Evenimente transmise:
  - SCAN (scanare carte)
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

// CONFIGURARE HARDWARE
#define SS_PIN 5
#define RST_PIN 27

// CONFIGURARE REȚEA
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";
const char* mqtt_server = "192.168.1.100";

// IDENTITATE DISPOZITIV
const char* device_id = "ESP32_GATE_01";
const char* zone_id   = "ENTRANCE_GATE";

// OBIECTE
WiFiClient espClient;
PubSubClient mqttClient(espClient);
MFRC522 rfid(SS_PIN, RST_PIN);

// SETUP
void setup() {
  Serial.begin(115200);

  // Initializare RFID
  SPI.begin();
  rfid.PCD_Init();

  // Conectare Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Conectare MQTT
  mqttClient.setServer(mqtt_server, 1883);
  while (!mqttClient.connected()) {
    mqttClient.connect(device_id);
    delay(1000);
  }
}

// LOOP
void loop() {
  mqttClient.loop();

  // Verifica daca exista un tag nou
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Construire UID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  // Construire mesaj JSON
  String payload = "{";
  payload += "\"tag_uid\":\"" + uid + "\",";
  payload += "\"device_id\":\"" + String(device_id) + "\",";
  payload += "\"zone_id\":\"" + String(zone_id) + "\",";
  payload += "\"event_type\":\"SCAN\"";
  payload += "}";

  // Trimitere mesaj
  mqttClient.publish("library/events/scan", payload.c_str());

  delay(2000); // anti-dublare scan
}

