#include <Arduino.h>

/*
    VARIABLES GLOBALES
*/
volatile uint32_t contador = 0;

/*
    TAREA 1
    Consume algo de stack
*/
void tareaA(void *pvParameters)
{
    while (1)
    {
        char buffer[1000];

        memset(buffer, 0, sizeof(buffer));

        contador++;

        Serial.printf(
            "[TAREA A] Stack libre minimo: %u bytes\n",
            uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t));

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/*
    TAREA 2
    Consume más stack
*/
void tareaB(void *pvParameters)
{
    while (1)
    {
        char buffer[3000];

        memset(buffer, 0, sizeof(buffer));

        Serial.printf(
            "[TAREA B] Stack libre minimo: %u bytes\n",
            uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t));

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void setup()
{
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("====================================");
    Serial.println(" DEMO MONITOREO FREERTOS ESP32 ");
    Serial.println("====================================");

    /*
        HERRAMIENTA 1

        Cantidad total de tareas del sistema
    */
    Serial.printf(
        "Tareas existentes antes de crear las nuestras: %u\n",
        uxTaskGetNumberOfTasks());

    /*
        Creamos dos tareas
    */
    xTaskCreate(
        tareaA,
        "TAREA_A",
        2048,       // 2048 palabras = 8192 bytes
        NULL,
        1,
        NULL);

    xTaskCreate(
        tareaB,
        "TAREA_B",
        2048,
        NULL,
        1,
        NULL);

    /*
        HERRAMIENTA 2

        Ver cuántas tareas existen ahora
    */
    Serial.printf(
        "Tareas existentes despues de crear las nuestras: %u\n",
        uxTaskGetNumberOfTasks());

    /*
        HERRAMIENTA 3

        Heap libre del sistema
    */
    Serial.printf(
        "Heap libre: %u bytes\n",
        ESP.getFreeHeap());

    /*
        HERRAMIENTA 4

        Bloque continuo más grande disponible
        Permite detectar fragmentación
    */
    Serial.printf(
        "Bloque libre mas grande: %u bytes\n",
        heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    Serial.println("------------------------------------");
}

void loop()
{
    /*
        MONITOREO PERIÓDICO
    */

    Serial.println();
    Serial.println("===== ESTADO DEL SISTEMA =====");

    /*
        Cantidad de tareas
    */
    Serial.printf(
        "Cantidad de tareas: %u\n",
        uxTaskGetNumberOfTasks());

    /*
        Heap libre actual
    */
    Serial.printf(
        "Heap libre: %u bytes\n",
        ESP.getFreeHeap());

    /*
        Bloque libre más grande
    */
    Serial.printf(
        "Bloque libre mas grande: %u bytes\n",
        heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    /*
        Contador para verificar que
        las tareas siguen ejecutándose
    */
    Serial.printf(
        "Contador tareaA: %lu\n",
        contador);

    Serial.println("==============================");

    delay(5000);
}