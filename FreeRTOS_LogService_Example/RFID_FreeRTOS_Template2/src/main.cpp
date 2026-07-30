#include <Arduino.h>
#include "app.h"
#include "log.h"
#include "task_logger.h"
#include "task_rfid.h"
void setup(){Serial.begin(115200);Log_Init();App_Init();xTaskCreate(TaskLogger,"Logger",2048,NULL,2,NULL);xTaskCreate(TaskRFID,"RFID",4096,NULL,1,NULL);} void loop(){}
