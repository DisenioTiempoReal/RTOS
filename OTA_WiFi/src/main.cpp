#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPUpdate.h>

//////////////////////////////////////////////////////////////
// CONFIGURACIÓN WIFI
//////////////////////////////////////////////////////////////

const char *ssid     = "HUAWEI-1DA5";
const char *password = "20150628";

//////////////////////////////////////////////////////////////
// URL DEL FIRMWARE
//////////////////////////////////////////////////////////////

const char *firmwareURL =
"https://raw.githubusercontent.com/DisenioTiempoReal/OTA/main/firmware.bin";

//////////////////////////////////////////////////////////////

WiFiClientSecure client;

void conectarWiFi()
{
    Serial.println();
    Serial.println("Conectando al WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("WiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void actualizarFirmware()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("Iniciando OTA...");
    Serial.println("================================");

    // Para la clase evitamos manejar certificados HTTPS
    client.setInsecure();

    t_httpUpdate_return resultado = httpUpdate.update(client, firmwareURL);

    switch (resultado)
    {
        case HTTP_UPDATE_FAILED:

            Serial.println();
            Serial.println("******** ERROR OTA ********");

            Serial.printf("Codigo Error: %d\n",
                          httpUpdate.getLastError());

            Serial.printf("Descripcion : %s\n",
                          httpUpdate.getLastErrorString().c_str());

            Serial.println("***************************");

            break;

        case HTTP_UPDATE_NO_UPDATES:

            Serial.println("No hay actualizacion.");

            break;

        case HTTP_UPDATE_OK:

            Serial.println("Firmware actualizado.");
            Serial.println("Reiniciando...");

            break;
    }
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("--------------------------------");
    Serial.println(" DEMO OTA GITHUB v1.1");
    Serial.println("--------------------------------");

    conectarWiFi();

    Serial.println();
    Serial.println("Escriba:");
    Serial.println("actualizar");
    Serial.println();
}

void loop()
{
    if (Serial.available())
    {
        String comando = Serial.readStringUntil('\n');
        comando.trim();

        if (comando.equalsIgnoreCase("actualizar"))
        {
            actualizarFirmware();
        }
        else
        {
            Serial.println("Comando desconocido.");
        }
    }
}