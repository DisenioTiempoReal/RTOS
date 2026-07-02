#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"

MessageBufferHandle_t mensajes;

//----------------------------------------------------
void productor(void *pv)
{
    while (1)
    {
        xMessageBufferSend(
            mensajes,
            "Hola",
            5,
            portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(500));

        xMessageBufferSend(
            mensajes,
            "ESP32",
            6,
            portMAX_DELAY);
      

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

//----------------------------------------------------
void consumidor(void *pv)
{
    char buffer[30];

    while (1)
    {
        size_t n = xMessageBufferReceive(
                        mensajes,
                        buffer,
                        sizeof(buffer),
                        portMAX_DELAY);

        Serial.print("Mensaje recibido: ");
        Serial.println(buffer);
    }
}

//----------------------------------------------------
void setup()
{
    Serial.begin(115200);

    mensajes = xMessageBufferCreate(100);

    xTaskCreate(productor,"P",2048,NULL,1,NULL);
    xTaskCreate(consumidor,"C",2048,NULL,1,NULL);
}

void loop()
{
}