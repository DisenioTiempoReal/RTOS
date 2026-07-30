#pragma once
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
extern QueueHandle_t logQueue;
void Log_Init();
void Log_Print(const char *msg);
void TaskLogger(void *pv);
