/*
 * gpio.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Tran Hoang
 */

#include"gpio.h"

/*-----------------------------------------------------------------------------
 * @brief  		: set gpio pin input/output
 * @param	 	: None
 * @retval		: None
 * */
void gpio_init(){
	enable_clock_APB2(gpiob);
	GPIOB->CRL &= ~(0b1111<<8); // clear all bit of PC13 because resetvalue = 0x4444 4444
	GPIOB->CRL |= (0b0001<<8);	//set PC13 output mode push-pull
	
	GPIOB->CRH &= ~(0b1111<<0); // clear all bit of PC13 because resetvalue = 0x4444 4444
	GPIOB->CRH |= (0b0001<<0);	//set PC13 output mode push-pull
	GPIOB->CRH &= ~(0b1111<<4); // clear all bit of PC13 because resetvalue = 0x4444 4444
	GPIOB->CRH |= (0b0001<<4);	//set PC13 output mode push-pull
	GPIOB->ODR |= (1 << 8);
	GPIOB->ODR |= (1 << 9);

	enable_clock_APB2(gpioc);
	GPIOC->CRH &= ~(0b1111<<24); // clear all bit of PC13 because resetvalue = 0x4444 4444
	GPIOC->CRH |= (0b0001<<24);	//set PC13 output mode push-pull
}

/*-----------------------------------------------------------------------------
 * @brief  		: Blink gpio pin
 * @param	 	: Time toggle
 * @retval		: None
 * */

void blink_led1(uint32_t ms){
	GPIOB->ODR ^= (1 << 8); // toggle state of PB8
	timer1_delay(ms);
}
void blink_led2(uint32_t ms){
	GPIOB->ODR ^= (1 << 9); // toggle state of PB9
	timer1_delay(ms);
}