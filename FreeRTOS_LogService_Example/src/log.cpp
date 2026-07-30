#include "log.h"

QueueHandle_t logQueue=NULL;

void Log_Init(){
    logQueue=xQueueCreate(10,sizeof(char*));
}

void Log_Print(const char *msg){
    if(logQueue) xQueueSend(logQueue,&msg,portMAX_DELAY);
}

void TaskLogger(void *pv){
    char *msg;
    while(1){
        if(xQueueReceive(logQueue,&msg,portMAX_DELAY)){
            Serial.println(msg);
        }
    }
}
