#ifndef USART_H__
#define	USART_H__ 

#include "stm32f10x.h"

#define USART_REC_LEN  			2 	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define USART_RX_LEN       64	  	


extern char  USART_RX_BUF[USART_RX_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern char USART_RX_BUF_A[USART_RX_LEN];
extern int USART_BUF_TAIL;

void uart_init(u32 bound);
uint8_t Usart_GetRxFlag(void);
void Clear_Buf(void);

#endif


