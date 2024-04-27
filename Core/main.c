#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include"semphr.h"

float g_temp = 0 ;
QueueHandle_t queue_temp;
EventGroupHandle_t event_temp ;
SemaphoreHandle_t  mutex_printlog ;

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize ) {
    /* Cung cấp bộ nhớ cho task IDLE */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize ) {
    /* Cung cấp bộ nhớ cho task Timer */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


SystemInit(){}

void func1(void *pvParameters) {
    for (;;) {
        GPIOB->ODR ^= (1<<2); 
        vTaskDelay(1000);
    }
}

void func2(void *pvParameters) {
    for (;;) {
    xEventGroupSync(event_temp,0,1, 10000);
    float tmp ;
        xSemaphoreTake(mutex_printlog, 10000);
        printlog("nhiet do :[");
        while(uxQueueMessagesWaiting(queue_temp) > 0){
        xQueueReceive(queue_temp, &tmp, portMAX_DELAY);
        printlog(" %.2f",tmp);
        }
        printlog(" ] \r\n",tmp);
        xSemaphoreGive(mutex_printlog);
    }
}
void func3(void *pvParameters) {
        int count  ;
    for (;;) {
        if(++count >= 10){
            count = 0 ;
            //send event 
            xEventGroupSetBits(event_temp, 1);
        }
        g_temp =  adc_get_temperature();
        xQueueGenericSend(queue_temp, &g_temp,10000,queueSEND_TO_BACK );
        vTaskDelay(510);
        
    }
}

void func4(void *pvParameters) {
    for (;;) {
        xSemaphoreTake(mutex_printlog, 10000);
        printlog("noise!!!!!!!!!! \r\n");
        xSemaphoreGive(mutex_printlog);
        vTaskDelay(500);
    }
}

int main(void) {

	SystemInit();
	rcc_init();
    gpio_init(); 
    adc_init();
    timer1_init();
    uart1_init();
    
    TaskHandle_t task_1 , task_2, task_3 , task_4;
    xTaskCreate(func1, "Task 1", 200, NULL, 0, &task_1);
   	xTaskCreate(func2, "Task 2", 200, NULL, 1, &task_2);
   	xTaskCreate(func3, "Task 3", 300, NULL, 1, &task_3);
   	xTaskCreate(func4, "Task 4", 200, NULL, 1, &task_4);
    
    queue_temp = xQueueCreate(20, sizeof(float));
    event_temp = xEventGroupCreate();
    mutex_printlog = xSemaphoreCreateMutex();

    vTaskStartScheduler();
    while (1) {
	}

}
