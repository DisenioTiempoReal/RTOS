#include <Arduino.h>
#include "esp_sleep.h"

#define BOTON 0      // GPIO0 (BOOT en muchas placas)
#define LED    2

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(LED, OUTPUT);
    pinMode(BOTON, INPUT_PULLUP);

    // ¿Por qué se despertó?
    esp_sleep_wakeup_cause_t causa = esp_sleep_get_wakeup_cause();

    switch (causa)
    {
        case ESP_SLEEP_WAKEUP_TIMER:
            Serial.println("Despertó por TIMER");
            break;

        case ESP_SLEEP_WAKEUP_EXT0:
            Serial.println("Despertó por BOTON");
            break;

        default:
            Serial.println("Primer encendido");
            break;
    }

    digitalWrite(LED, HIGH);
    delay(2000);
    digitalWrite(LED, LOW);

    //--------------------------------------------------
    // Configurar wakeup por tiempo
    //--------------------------------------------------
    esp_sleep_enable_timer_wakeup(
        120ULL * 1000000ULL);     // 120 segundos

    //--------------------------------------------------
    // Configurar wakeup por GPIO0
    //--------------------------------------------------
    esp_sleep_enable_ext0_wakeup(
        (gpio_num_t)BOTON,
        0);       // Despierta cuando GPIO0 = LOW

    Serial.println("Entrando en Deep Sleep...");
    delay(500);

    esp_deep_sleep_start();
}

void loop()
{
}