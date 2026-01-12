# Firmware ESP32 – Smart Library

Acest firmware implementeaza clientul embedded al sistemului IoT pentru urmarirea inteligenta a cartilor in biblioteca.

## Functionalitate
- Citeste tag-uri RFID atasate cartilor
- Identifica unic fiecare carte prin UID
- Transmite evenimente prin protocolul MQTT
- Functioneaza ca punct de scanare (poarta / birou / raft)

## Hardware utilizat
- ESP32
- Modul RFID MFRC522
- Conectivitate Wi-Fi

## Topic-uri MQTT
- Publish: `library/events/scan`
- Payload JSON:
```json
{
  "tag_uid": "a1b2c3d4",
  "device_id": "ESP32_GATE_01",
  "zone_id": "ENTRANCE_GATE",
  "event_type": "SCAN"
}
