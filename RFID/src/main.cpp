#include <Arduino.h>

TaskHandle_t tareaLEDHandle;
TaskHandle_t tareaMemoriaHandle;

const int LED_BUILTIN = 2;


void tareaLED(void *pvParameters)
{
    pinMode(LED_BUILTIN, OUTPUT);

    while (true)
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        Serial.println("Tarea LED ejecutando");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void tareaMemoria(void *pvParameters)
{
    while (true)
    {
        char bufferGigante[2000];

        for (int i = 0; i < sizeof(bufferGigante); i++)
        {
            bufferGigante[i] = i;
        }

        Serial.println("Tarea memoria ejecutando");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        tareaLED,
        "LED",
        2048,
        NULL,
        1,
        &tareaLEDHandle);

    xTaskCreate(
        tareaMemoria,
        "MEMORIA",
        512,
        NULL,
        1,
        &tareaMemoriaHandle);
}

void loop()
{
}