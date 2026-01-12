"""
Proiect: Urmarirea inteligenta a cartilor in biblioteca
Componenta: Client receptor MQTT (backend)

Rol:
- Primeste evenimente MQTT de la dispozitivele embedded
- Proceseaza datele si le pregateste pentru stocare in baza de date
"""

import json
from paho.mqtt import client as mqtt

BROKER = "localhost"
TOPIC = "library/events/#"

def on_message(client, userdata, msg):
    data = json.loads(msg.payload.decode())
    print("Eveniment primit:", data)

client = mqtt.Client("backend_ingestor")
client.connect(BROKER, 1883)
client.subscribe(TOPIC)
client.on_message = on_message
client.loop_forever()

