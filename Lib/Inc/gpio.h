/*
 * gpio.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Tran Hoang
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include"main.h"

void gpio_init();
void blink_led1(uint32_t ms);
void blink_led2(uint32_t ms);
#endif /* INC_GPIO_H_ */
