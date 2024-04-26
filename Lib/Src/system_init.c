/*
 * system_init.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Tran Hoang
 */

#include"system_init.h"

uint32_t g_systick_count = 0 ;
/*-----------------------------------------------------------------------------
 * @brief  		: Configure system clock use clock source HSE for PLL
 * @note 		: PLLMUL min = x2
 * 				  if APB prescale = 1 then timer *= 1 | else timer *= 2
 * @param	 	: None
 * @retval		: None
 * */
void rcc_init(void){
	/****************Sequence follow*************************************
	 * enable HSE and wait stable
	 * select HSE as input clock for PLL
	 * PLL selected ad system clock
	 * configure MUL/DIV for PLL / AHB / APB1 / APB2
	 * enable PLL and wait stable
	 * */
	RCC->CR =  0 ; 						//clear all bit ;
	RCC->CR |= (1<< 16) ; 				//enable HSE
	while(((RCC->CR >> 17 )&1)== 0); 	//wait HSE ready

	RCC->CFGR |= (0b10<<0); 			//PLL selected as system clock

	RCC->CFGR |= (1<<16); 				//HSE oscillator clock selected as PLL input clock
	RCC->CFGR |= (0b0111<<18);			//PLL input clock x 9 
	FLASH->ACR |= (0b010<<0);			//Two wait states, if 48 MHz < SYSCLK ≤72 MHz

	RCC->CFGR |= (0b1000<<4); 			// AHB DIV 2

	RCC->CR |= (1<<24);
	while(((RCC->CR >> 25 )&1)== 0); 	// wait PLL ready
}
/*-----------------------------------------------------------------------------
 * @brief  		: Enable clock for peripheral in APB1
 * @param	 	: APB1_peripheral
 * @retval		: None
 * */
void enable_clock_APB1(APB1_peripheral peripheral){
	RCC->APB1ENR |=  (1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Enable clock for peripheral in APB2
 * @param	 	: APB2_peripheral
 * @retval		: None
 * */
void enable_clock_APB2(APB2_peripheral peripheral){
	RCC->APB2ENR |=  (1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Enable clock for peripheral in AHB
 * @param	 	: AHB_periperal
 * @retval		: None
 * */
void enable_clock_AHB(AHB_peripheral peripheral){
	RCC->AHBENR |=  (1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Disable clock for peripheral in APB1
 * @param	 	: APB1_peripheral
 * @retval		: None
 * */
void disable_clock_APB1(APB1_peripheral peripheral){
	RCC->APB1ENR &=  ~(1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Disable clock for peripheral in APB2
 * @param	 	: APB2_peripheral
 * @retval		: None
 * */
void disable_clock_APB2(APB2_peripheral peripheral){
	RCC->APB2ENR &=  ~(1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Disable clock for peripheral in ABH
 * @param	 	: AHB_periperal
 * @retval		: None
 * */
void disable_clock_AHB(AHB_peripheral peripheral){
	RCC->AHBENR &=  ~(1<<peripheral);
}
/*-----------------------------------------------------------------------------
 * @brief  		: Configure SysTick
 * @note		: sysTick only countdown
 * @param	 	: None
 * @retval		: None
 * */
void systick_init(){
	SysTick->LOAD = 72000; 		//	value to load into the LOAD when the counter reaches 0
	SysTick->CTRL |= (1<<2);	// 	enable core lock
	SysTick->CTRL |= (1<<1);	//	enable SysTick handler
	SysTick->CTRL |= (1<<0); 	// 	counter operates
}
/*-----------------------------------------------------------------------------
 * @brief  		: create delay using interrupt sysTick
 * @param	 	: uint32_t ms
 * @retval		: None
 * */
void systick_delay_ms(uint32_t ms){
	uint32_t l_current_count =  g_systick_count ;
	while((g_systick_count - l_current_count) < ms);
}
// void SysTick_Handler(){
// 	g_systick_count ++;
// }
