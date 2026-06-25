#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

//========================================
// 0 = Sin Mutex
// 1 = Con Mutex
//========================================
#define USAR_MUTEX 0

int saldo = 1000;

#if USAR_MUTEX
SemaphoreHandle_t mutexSaldo;
#endif

//------------------------------------------------

void TaskATM1(void *pv)
{
    while (1)
    {
#if USAR_MUTEX
        xSemaphoreTake(mutexSaldo, portMAX_DELAY);
#endif

        Serial.println("\nATM1 quiere retirar $100");

        int aux = saldo;

        Serial.printf("ATM1 lee saldo = %d\n", aux);
        Serial.println("");

        vTaskDelay(pdMS_TO_TICKS(100));   // Simula tiempo de procesamiento

        aux = aux - 100;

        saldo = aux;

        Serial.printf("ATM1 escribe saldo = %d\n", saldo);
        Serial.println("");


#if USAR_MUTEX
        xSemaphoreGive(mutexSaldo);
#endif

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//------------------------------------------------

void TaskATM2(void *pv)
{
    while (1)
    {
#if USAR_MUTEX
        xSemaphoreTake(mutexSaldo, portMAX_DELAY);
#endif

        Serial.println("\nATM2 quiere retirar $100");

        int aux = saldo;

        Serial.printf("ATM2 lee saldo = %d\n", aux);
        Serial.println("");


        vTaskDelay(pdMS_TO_TICKS(100));

        aux = aux - 100;

        saldo = aux;

        Serial.printf("ATM2 escribe saldo = %d\n", saldo);
        Serial.println("");


#if USAR_MUTEX
        xSemaphoreGive(mutexSaldo);
#endif

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//------------------------------------------------

void setup()
{
    Serial.begin(115200);

#if USAR_MUTEX
    mutexSaldo = xSemaphoreCreateMutex();
#endif

    Serial.println();
    Serial.println("==============================");

#if USAR_MUTEX
    Serial.println("EJEMPLO CON MUTEX");
#else
    Serial.println("EJEMPLO SIN MUTEX");
#endif

    Serial.printf("Saldo inicial = %d\n", saldo);
    Serial.println("==============================");

    xTaskCreate(TaskATM1, "ATM1", 2048, NULL, 1, NULL);
    xTaskCreate(TaskATM2, "ATM2", 2048, NULL, 1, NULL);
}

void loop()
{
}