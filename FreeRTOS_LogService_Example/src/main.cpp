#include <Arduino.h>
#include "log.h"

void TaskSensor(void *pv){
    while(1){
        Log_Print("[Sensor] Leyendo sensor...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TaskWiFi(void *pv){
    while(1){
        Log_Print("[WiFi] Conectando...");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void setup(){
    Serial.begin(115200);
    Log_Init();

    xTaskCreate(TaskLogger,"Logger",2048,NULL,2,NULL);
    xTaskCreate(TaskSensor,"Sensor",2048,NULL,1,NULL);
    xTaskCreate(TaskWiFi,"WiFi",2048,NULL,1,NULL);
}

void loop(){}
