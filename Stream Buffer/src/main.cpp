#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"

StreamBufferHandle_t stream;

//---------------------------------------------------
void tareaSerialRX(void *pv)
{
    while (1)
    {
        if (Serial.available())
        {
            char c = Serial.read();

            xStreamBufferSend(
                stream,
                &c,
                1,
                portMAX_DELAY);
        }

        vTaskDelay(1);
    }
}

//---------------------------------------------------
void tareaConsumidor(void *pv)
{
    char c;

    while (1)
    {
        xStreamBufferReceive(
            stream,
            &c,
            1,
            portMAX_DELAY);

        Serial.print("Recibi: ");
        Serial.println(c);
    }
}

//---------------------------------------------------
void setup()
{
    Serial.begin(115200);

    stream = xStreamBufferCreate(100, 1);

    xTaskCreate(tareaSerialRX, "RX", 2048, NULL, 1, NULL);
    xTaskCreate(tareaConsumidor, "CONS", 2048, NULL, 1, NULL);

    Serial.println("Escriba caracteres en el Monitor Serie...");
}

void loop()
{
}