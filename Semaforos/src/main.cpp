#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

//=======================================
// 0 = Sin semáforo (Polling)
// 1 = Con semáforo (Evento)
//=======================================
#define USAR_SEMAFORO 0

#if USAR_SEMAFORO
SemaphoreHandle_t semPieza;
#endif

volatile bool piezaLista = false;

//----------------------------------------------------

void TaskProduccion(void *pv)
{
    while (1)
    {
        Serial.println("\nProduccion: Fabricando pieza...");

        vTaskDelay(pdMS_TO_TICKS(5000));

        Serial.println("Produccion: Pieza terminada");

        piezaLista = true;

#if USAR_SEMAFORO
        xSemaphoreGive(semPieza);
#endif
    }
}

//----------------------------------------------------

void TaskEmpaque(void *pv)
{
    while (1)
    {
#if USAR_SEMAFORO

        Serial.println("Empaque: Esperando una pieza...");

        xSemaphoreTake(
            semPieza,
            portMAX_DELAY
        );

        Serial.println("Empaque: Empaquetando pieza");

        piezaLista = false;

#else

        if (piezaLista)
        {
            Serial.println("Empaque: Empaquetando pieza");

            piezaLista = false;
        }
        else
        {
            Serial.println("Empaque: No hay piezas...");
        }

        vTaskDelay(pdMS_TO_TICKS(500));

#endif
    }
}

//----------------------------------------------------

void setup()
{
    Serial.begin(115200);

#if USAR_SEMAFORO
    semPieza = xSemaphoreCreateBinary();
#endif

#if USAR_SEMAFORO
    Serial.println("\n***** MODO CON SEMAFORO *****");
#else
    Serial.println("\n***** MODO SIN SEMAFORO *****");
#endif

    xTaskCreate(
        TaskProduccion,
        "Produccion",
        2048,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        TaskEmpaque,
        "Empaque",
        2048,
        NULL,
        1,
        NULL
    );
}

void loop()
{
}