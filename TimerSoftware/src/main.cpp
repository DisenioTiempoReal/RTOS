#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#define LED 2

TimerHandle_t timerLED;

//----------------------------------------------
// Callback del Timer
//----------------------------------------------
void callback(TimerHandle_t xTimer)
{
    static bool estado = false;

    estado = !estado;

    digitalWrite(LED, estado);

    Serial.println("Callback ejecutado");
}

//----------------------------------------------
void setup()
{
    Serial.begin(115200);

    pinMode(LED, OUTPUT);

    // Crear el Software Timer
    timerLED = xTimerCreate(
                    "LED",                  // Nombre
                    pdMS_TO_TICKS(1000),    // 1 segundo
                    pdTRUE,                 // Auto Reload
                    NULL,                   // ID
                    callback);              // Callback

    // Iniciar el Timer
    xTimerStart(timerLED, 0);

    Serial.println("Software Timer iniciado...");
}

//----------------------------------------------
void loop()
{
    // No hace absolutamente nada
}