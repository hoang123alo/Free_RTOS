/*
 * timer.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Tran hoang
 */
#include"timer.h"

uint32_t g_timer1_count = 0;

/*-----------------------------------------------------------------------------
 * @brief  		: Configure Timer1
 * @param	 	: None
 * @retval		: None
 * */
void timer1_init(){
	enable_clock_APB2(timer1);
	TIM1->PSC = 36-1 ;	//	set prescale = 8 ==> frequency =  8000 000 / 8 = 1000 000(Hz)
	TIM1->ARR = 1000 ;	//	value auto-reload = 1000(equivalent 1ms)
	TIM1->CR1 &=~(1<<4);// counter used as upcounter
	TIM1->CR1 |= (1<<0);// enable counter
	TIM1->DIER|= (1<<0);// enable interrupt
	NVIC->ISER0 |= 1<<25 ; // enable timer1 interrupt in vector table
}
/*-----------------------------------------------------------------------------
 * @brief  		: create delay using interrupt sysTick
 * @param	 	: uint32_t ms
 * @retval		: None
 * */
void timer1_delay(uint32_t ms){
	uint32_t l_current_count = g_timer1_count ;
	while((g_timer1_count -  l_current_count) < ms );
}
void TIM1_UP_IRQHandler(){
	g_timer1_count++;
	TIM1->SR &= ~(1<< 0);
}
