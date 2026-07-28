#include <Arduino.h>
#include "esp_heap_caps.h"

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("\n==============================");
    Serial.println("      EJEMPLO DE MALLOC");
    Serial.println("==============================\n");

    Serial.printf("Heap libre antes : %d bytes\n", ESP.getFreeHeap());

    // Reservamos 100 bytes
    char *buffer = (char *)malloc(100);

    if (buffer == NULL)
    {
        Serial.println("No hay memoria.");
        while (1);
    }

    Serial.println("\nLuego de malloc(100)");

    Serial.printf("Direccion del puntero : %p\n", buffer);

    Serial.printf("sizeof(buffer)        : %d bytes\n", sizeof(buffer));

    Serial.printf("Heap libre despues    : %d bytes\n", ESP.getFreeHeap());

    // Escribimos datos
    strcpy(buffer, "Hola FreeRTOS!");

    Serial.printf("\nContenido del bloque : %s\n", buffer);

    Serial.println("\nDirecciones de los primeros bytes:");

    for (int i = 0; i < 20; i++)
    {
        Serial.printf("%p -> %02X (%c)\n",
                      buffer + i,
                      buffer[i],
                      (buffer[i] >= 32 && buffer[i] <= 126) ? buffer[i] : '.');
    }

    Serial.println("\nLiberando memoria...\n");

    free(buffer);

    Serial.printf("Heap libre despues del free : %d bytes\n", ESP.getFreeHeap());

}

void loop()
{

}