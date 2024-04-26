/*
 * system_init.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Tran Hoang
 */

#ifndef INC_SYSTEM_INIT_H_
#define INC_SYSTEM_INIT_H_

/*--------------------------Include header files------------------------------*/
#include"main.h"
/*--------------------------------Global variables----------------------------*/

/*--------------------------------Enum----------------------------------------*/
typedef enum{
	timer2,
	timer3,
	timer4,
	timer5,
	timer6,
	timer7,
	watchdog = 	11,
	spi2 	 = 	14 ,
	spi3,
	uart2	 =	17,
	uart3,
	uart4,
	uart5,
	i2c1,
	i2c2,
	can1	 =	25,
	can2,
	bkp,
	pwr,
	dac
}APB1_peripheral;

typedef enum{
	afio,
	gpioa 	=	2,
	gpiob,
	gpioc,
	gpiod,
	gpioe,
	adc1	=	9,
	adc2,
	timer1,
	spi1,
	uart1	=	14
}APB2_peripheral;
typedef enum{
	dma1,
	dma2,
	sram,
	flitfen =	4,
	crc		= 	6,
	otgfs	=	12,
	ethmac	=	14,
	ethmactx,
	ethmacrx
}AHB_peripheral;
/*----------------------------Declare functions-------------------------------*/

void rcc_init(void);
void enable_clock_APB1(APB1_peripheral peripheral);
void enable_clock_APB2(APB2_peripheral peripheral);
void enable_clock_AHB(AHB_peripheral peripheral);
void disable_clock_APB1(APB1_peripheral peripheral);
void disable_clock_APB2(APB2_peripheral peripheral);
void disable_clock_AHB(AHB_peripheral peripheral);
void systick_init();
void systick_delay(uint32_t ms);
#endif /* INC_SYSTEM_INIT_H_ */
