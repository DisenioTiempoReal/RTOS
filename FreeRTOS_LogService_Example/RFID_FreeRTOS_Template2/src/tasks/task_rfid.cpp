#include <Arduino.h>
#include "task_rfid.h"
#include "log.h"
void TaskRFID(void *pv){while(1){Log_Print("[RFID] Esperando tarjeta");vTaskDelay(pdMS_TO_TICKS(1000));}}
