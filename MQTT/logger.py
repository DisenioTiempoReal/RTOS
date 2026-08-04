import json
from collections import deque

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import paho.mqtt.client as mqtt

#==================================================
BROKER = "6d97e59b5a2f43a39a46817ac5b90a77.s1.eu.hivemq.cloud"
PORT = 8883

USERNAME = "leonardods18"
PASSWORD = "Capi1559"

TOPIC = "medidor1/datos"
#==================================================

MAX = 50

x = deque(maxlen=MAX)

voltaje = deque(maxlen=MAX)
corriente = deque(maxlen=MAX)
potencia = deque(maxlen=MAX)

contador = 0

#--------------------------------------------------

def on_connect(client, userdata, flags, reason_code, properties):

    print("Conectado")

    client.subscribe(TOPIC)

    print("Esperando mensajes...")

#--------------------------------------------------

def on_message(client, userdata, msg):

    global contador

    texto = msg.payload.decode()

    print(texto)

    dato = json.loads(texto)

    contador += 1

    x.append(contador)

    voltaje.append(dato["voltaje"])
    corriente.append(dato["corriente"])
    potencia.append(dato["potencia"])

#--------------------------------------------------

client = mqtt.Client(
    callback_api_version=mqtt.CallbackAPIVersion.VERSION2
)

client.username_pw_set(USERNAME, PASSWORD)

client.tls_set()

client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, PORT)

client.loop_start()

#==================================================

fig, ax = plt.subplots(3, 1, figsize=(10, 8))

#--------------------------------------------------

def actualizar(frame):

    # Voltaje
    ax[0].clear()
    ax[0].plot(x, voltaje, marker='o')
    ax[0].set_title("Voltaje")
    ax[0].set_ylabel("V")
    ax[0].grid(True)

    # Corriente
    ax[1].clear()
    ax[1].plot(x, corriente, marker='o')
    ax[1].set_title("Corriente")
    ax[1].set_ylabel("A")
    ax[1].grid(True)

    # Potencia
    ax[2].clear()
    ax[2].plot(x, potencia, marker='o')
    ax[2].set_title("Potencia")
    ax[2].set_ylabel("W")
    ax[2].set_xlabel("Muestras")
    ax[2].grid(True)

#--------------------------------------------------

ani = FuncAnimation(
    fig,
    actualizar,
    interval=500,
    cache_frame_data=False
)

plt.tight_layout()

plt.show()