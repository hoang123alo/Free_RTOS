/*
 * adc.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Tran Hoang
 */
#include"main.h"
// #include"stm32f103xx.h"
// #include"cortex_m3.h"
// #include<stdint.h>
// #include"system_init.h"
void adc_init();
float adc_get_temperature();
float adc_get_vol();
void adc_vol_init();