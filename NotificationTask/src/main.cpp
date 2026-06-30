#include <Arduino.h>

TaskHandle_t tareaLED;

void TaskProductor(void *pvParameters)
{
    while (true)
    {
        Serial.println("Evento generado");

        xTaskNotifyGive(tareaLED);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void TaskLED(void *pvParameters)
{
    pinMode(2, OUTPUT);

    while (true)
    {
        // Espera una notificación
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        digitalWrite(2, !digitalRead(2));

        Serial.println("Notificación recibida - Cambio LED");
    }
}

void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        TaskLED,
        "LED",
        2048,
        NULL,
        1,
        &tareaLED);

    xTaskCreate(
        TaskProductor,
        "Productor",
        2048,
        NULL,
        1,
        NULL);
}

void loop()
{
}