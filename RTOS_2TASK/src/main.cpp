#include <Arduino.h>

void taskBlink(void *pvParameters)
{
    pinMode(LED_BUILTIN, OUTPUT);

    while (1)
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void taskSerial(void *pvParameters)
{
    while (1)
    {
        Serial.println("Hola desde TaskSerial");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        taskBlink,
        "Blink",
        2048,
        NULL,
        1,
        NULL);

    xTaskCreate(
        taskSerial,
        "Serial",
        2048,
        NULL,
        1,
        NULL);
}

void loop()
{
}