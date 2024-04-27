/*
 * adc.c
 *
 *  Created on: Apr 17, 2024
 *      Author: Tran Hoang
 */
#include"adc.h"

/*-----------------------------------------------------------------------------
 * @brief  		: init ADC
 * @param	 	: None
 * @retval		: None
 * */
void adc_init(){
    enable_clock_APB2(adc1);
    ADC1->SMPR1 |= (0b111 << 18); // Set sample time to 239.5 cycles
    ADC1->JSQR &= ~(0b11 << 20);  // Clear bits for injected sequence length (00 : 1 conversion)
    ADC1->JSQR |= (0b00 << 20);   // Set injected sequence length to 1 conversion
    ADC1->JSQR &= ~(0x1F << 15);  // Clear bits for JSQ4 (Injected channel 4)
    ADC1->JSQR |= (16<< 15);     // Set source for JSQ4 to temperature sensor (IN16)
    ADC1->CR2 |= (1 << 23);       // Enable temperature sensor
    ADC1->CR2 |= (1 << 0);        // Enable ADC and start conversion

}

/*-----------------------------------------------------------------------------
 * @brief  		: get temperature for ADC1_IN16
 * @param	 	: None
 * @retval		: None
 * */
float adc_get_temperature(){
    float Vin = 0;
    float Temp ;
    uint16_t rawdata ;
    ADC1->CR2 |= (0b111 << 12) ;
    ADC1->CR2 |= (0b1 << 15) ;
    // Trigger ADC start conversion
    ADC1->CR2 |= (1 << 21);
    // Wait until end of conversion
    while(((ADC1->SR >> 2)&1) == 0);
    ADC1->SR &= ~(1 << 2); // Clear JEOC flag
    // Read ADC data from JDR1
    rawdata = ADC1->JDR1;
    Vin = (rawdata * 3300.0) / 4095.0;
    Temp = ((Vin - 1430 ) / 43) + 25;
    return Temp;
}
float adc_get_vol(){
    		float Vin = 0;
		uint16_t rawdata ;
	    ADC1->CR2 |= (0b111 << 12) ;
	    ADC1->CR2 |= (0b1 << 15) ;
	    // Trigger ADC start conversion
	    ADC1->CR2 |= (1 << 21);
	    // Wait until end of conversion
	    while(((ADC1->SR >> 2)&1) == 0);
	    ADC1->SR &= ~(1 << 2); // Clear JEOC flag
	    // Read ADC data from JDR1
	    rawdata = ADC1->JDR1;
	    Vin = (rawdata * 3.0) / 4095.0;
	    return Vin;
}
void adc_vol_init(){
        enable_clock_APB2(adc1);

    ADC1->SMPR1 |= (0b111 << 9); // Set sample time to 239.5 cycles
    ADC1->JSQR &= ~(0b11 << 20);  // Clear bits for injected sequence length (00 : 1 conversion)
    ADC1->JSQR |= (0b00 << 20);   // Set injected sequence length to 1 conversion
    ADC1->JSQR &= ~(0x1F << 15);  // Clear bits for JSQ4 (Injected channel 4)
    ADC1->JSQR |= (3<< 15);     // Set source for JSQ4 to temperature sensor (IN16)

    ADC1->CR2 |= (1 << 22)|(1 << 20);       // Enable temperature sensor
    ADC1->CR2 |= (1 << 0);        // Enable ADC and start conversion
}