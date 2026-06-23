#include <Arduino.h>

void tareaMala(void *pvParameters)
{
    while (1)
    {
        Serial.println("Tarea MALA");
        //taskYIELD();
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void tareaBuena(void *pvParameters)
{
    while (1)
    {
        Serial.println("Tarea BUENA");
        taskYIELD();
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        tareaMala,
        "MALA",
        2048,
        NULL,
        1,
        NULL);

    xTaskCreate(
        tareaBuena,
        "BUENA",
        2048,
        NULL,
        1,
        NULL);
}

void loop()
{
}