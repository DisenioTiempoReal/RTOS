#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

volatile int contador = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

//---------------------------------------------------------
void tareaA(void *pv)
{
    while (1)
    {
        portENTER_CRITICAL(&mux);

        contador++;

        Serial.print("A -> ");
        Serial.println(contador);

        portEXIT_CRITICAL(&mux);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

//---------------------------------------------------------
void tareaB(void *pv)
{
    while (1)
    {
        portENTER_CRITICAL(&mux);

        contador++;

        Serial.print("B -> ");
        Serial.println(contador);
        vTaskDelay(1);     
        portEXIT_CRITICAL(&mux);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

//---------------------------------------------------------
void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        tareaA,
        "A",
        2048,
        NULL,
        1,
        NULL);

    xTaskCreate(
        tareaB,
        "B",
        2048,
        NULL,
        1,
        NULL);
}

//---------------------------------------------------------
void loop(){}