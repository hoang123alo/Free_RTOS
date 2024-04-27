#include"main.h"
void uart1_init();
void UART1_SEND_1BYTE(char data);
void UART1_SEND_STRING(const char msg[]);
char UART1_RECIVER_1BYTE();
void printlog(char * format, ...);