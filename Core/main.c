#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

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
void func1(void *pvParameters) {
    for (;;) {
        GPIOB->ODR ^= (1<<2); 
        vTaskDelay(100);
    }
}

void func2(void *pvParameters) {
    for (;;) {
        GPIOB->ODR ^= (1<<8); 
        vTaskDelay(1000); 
    }
}
SystemInit(){}

int main(void) {
	SystemInit();
	rcc_init();
    gpio_init(); 
    TaskHandle_t task_1, task_2;
    xTaskCreate(func1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task_1);
   	xTaskCreate(func2, "Task2", configMINIMAL_STACK_SIZE, NULL, 1, &task_2);
    vTaskStartScheduler();
    while (1) {
	}

}
