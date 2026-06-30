#include <Arduino.h>

QueueHandle_t cola;

void TaskProductor(void *pvParameters)
{
    int contador = 0;

    while (true)
    {
        contador++;

     //   if (xQueueSend(cola, &contador, portMAX_DELAY) == pdTRUE)
        if (xQueueSend(cola, &contador, 10) == pdTRUE)
        {
            Serial.print("Enviado: ");
            Serial.println(contador);

   //         Serial.print(" | Cola = ");
   //         Serial.println(uxQueueMessagesWaiting(cola));

        }
        else
        {
            Serial.println("QUEUE LLENA !!");
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // productor
    }
}

void TaskConsumidor(void *pvParameters)
{
    int dato;

    while (true)
    {
        if (xQueueReceive(cola, &dato, portMAX_DELAY))
        {
            Serial.print("Procesando: ");
            Serial.println(dato);

            vTaskDelay(pdMS_TO_TICKS(2000));  // consumidor
        }
    }
}

void setup()
{
    Serial.begin(115200);

    cola = xQueueCreate(5, sizeof(int));  // creación de la cola con 5 elementos de tipo int

    xTaskCreate(TaskProductor,
                "Productor",
                2048,
                NULL,
                1,
                NULL);

    xTaskCreate(TaskConsumidor,
                "Consumidor",
                2048,
                NULL,
                1,
                NULL);
}

void loop()
{
}