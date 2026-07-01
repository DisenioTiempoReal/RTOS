#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define WIFI_OK      BIT0
#define BT_OK        BIT1

EventGroupHandle_t eventos;

void tareaWiFi(void *pv)
{
    Serial.println("Inicializando WiFi...");
    vTaskDelay(pdMS_TO_TICKS(3000));

    Serial.println("WiFi listo");
    xEventGroupSetBits(eventos, WIFI_OK);

    vTaskDelete(NULL);
}

void tareaBluetooth(void *pv)
{
    Serial.println("Inicializando Bluetooth...");
    vTaskDelay(pdMS_TO_TICKS(5000));

    Serial.println("Bluetooth listo");
    xEventGroupSetBits(eventos, BT_OK);

    vTaskDelete(NULL);
}

void tareaPrincipal(void *pv)
{
    Serial.println("Esperando WiFi y Bluetooth...");

    xEventGroupWaitBits(
        eventos,
        WIFI_OK | BT_OK,
        pdFALSE,
        pdTRUE,
        portMAX_DELAY);

    Serial.println("Sistema listo!!");

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup()
{
    Serial.begin(115200);

    eventos = xEventGroupCreate();

    xTaskCreate(tareaWiFi, "wifi", 2048, NULL, 1, NULL);
    xTaskCreate(tareaBluetooth, "bt", 2048, NULL, 1, NULL);
    xTaskCreate(tareaPrincipal, "main", 2048, NULL, 1, NULL);
}

void loop(){}