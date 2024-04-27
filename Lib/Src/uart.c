#include"uart.h"
void uart1_init(){
	//  PA9 TX  | PA10 RX
	enable_clock_APB2(gpioa);
	GPIOA->CRH &= ~(0b1111<<4);
	GPIOA->CRH |= (0b1001<<4) ;
	//GPIOA->CRH |= (0b10<<6) ;

	GPIOA->CRH &= ~(0b1111<<8);
	GPIOA->CRH |= 0b10 <<10 ;
	GPIOA->ODR |= 1<< 10 ;

	AFIO->MAPR &= ~(0b1 <<2);
	/*
	 * USART :
	 * baudrate : 9600;
     * (72M)/(16*baudrate) = 234.375
	 * frame :
	 *	+data lenght : 8 byte
	 *	+parity (none/add/even) : none
	 *	register : SR , DR , BRR

	*/
	
    enable_clock_APB2(uart1);
    
	USART1->BRR = (234<<4)|(6<<0); // set baudrate 9600

	USART1->CR1 &= ~(0b1 <<10);
	USART1->CR1 &= ~(0b1 <<12);		// set data len as 8 bits data
	USART1->CR1 |= (1 << 2)| (1 << 3) |(1 << 13); // enable transmiter , reciver, uart
#if 1
	USART1->CR1 |= 1 << 5; // config interrupt enable

	NVIC->ISER1 |=(1<<5);//config NVIC
#else
	USART1->CR3 |= 1<<6 ; //DMA enable reciever
#endif
}
void UART1_SEND_1BYTE(char data){

	while(((USART1->SR)>>7&1) ==0);
	USART1->DR = data;
	while((USART1->SR>>6&1) ==0);
	USART1->SR &= ~(1<<6);
}

void UART1_SEND_STRING(const char msg[]){
	int msg_len = strlen(msg);
	for(int i = 0 ; i < msg_len ; i++){
		UART1_SEND_1BYTE(msg[i]);
	}
}

char UART1_RECIVER_1BYTE(){

	while((((USART1->SR)>>5) & 1 ) ==0);
	char  RCV_data = USART1->DR ;
	return RCV_data;

}
// void printlog(char * format, ...){
//     char buf[1024];
//     char buf_len = 0 ; 
//     va_list ap ; 
//     va_start(ap ,format);
//     vsprintf(buf, format, ap);
//     va_end(ap);
//     for (int i = 0; i < buf_len ; i++)
//     {
//         UART1_SEND_1BYTE(buf[i]);
//     }
// }
void printlog(char *format, ...) {
    char buf[1024];
    int buf_len = 0; // Sử dụng int thay vì char
    va_list ap;
    va_start(ap, format);
    buf_len = vsprintf(buf, format, ap); // tính độ dài của chuỗi định dạng và gán cho buf_len
    va_end(ap);
    for (int i = 0; i < buf_len; i++) {
        UART1_SEND_1BYTE(buf[i]);
    }
}