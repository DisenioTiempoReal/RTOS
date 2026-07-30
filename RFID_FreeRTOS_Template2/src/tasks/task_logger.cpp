#include <Arduino.h>
#include "task_logger.h"
void TaskLogger(void *pv)
{
    while(1)
    {
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
