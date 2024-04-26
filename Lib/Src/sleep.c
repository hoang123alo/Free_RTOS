#include"sleep.h"
void goto_sleep(){
    PWR->CR |=  (1 << 1);
    SCB->SCR |= (1<<2) ; //enable SLEEPDEEP 
    __asm("WFI") ; // sleep instruction
}

void enable_iwdg(){
    //set watchdog 2sec wakeup MCU
    IWDG->KR = 0x5555;
    IWDG->PR |= (0b011 << 0 ); // set devider / 32
    IWDG->RLR = 2500 ;
    IWDG->KR = 0xAAAA; // Start watchdog ;
    IWDG->KR = 0xCCCC;

}