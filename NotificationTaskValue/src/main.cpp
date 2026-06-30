#include <Arduino.h>

TaskHandle_t tareaReceptora;

void TaskProductor(void *pvParameters)
{
    uint32_t numero = 10;

    while (true)
    {
        Serial.print("Enviando: ");
        Serial.println(numero);

        xTaskNotify(
            tareaReceptora,              // tarea destino
            numero,                      // Notification Value
            eSetValueWithOverwrite);     // guarda el valor

        numero += 10;

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void TaskReceptora(void *pvParameters)
{
    uint32_t valor;

    while (true)
    {
        xTaskNotifyWait(
            0,              // bits a limpiar al entrar
            0,              // bits a limpiar al salir
            &valor,         // aquí se copia Notification Value
            portMAX_DELAY);

        Serial.print("Valor recibido: ");
        Serial.println(valor);
    }
}

void setup()
{
    Serial.begin(115200);

    xTaskCreate(
        TaskReceptora,
        "Receptora",
        2048,
        NULL,
        1,
        &tareaReceptora);

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