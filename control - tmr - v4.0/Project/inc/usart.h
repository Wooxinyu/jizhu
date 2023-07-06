#ifndef USART_H__
#define	USART_H__ 

#define USART_REC_LEN  			2 	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
void uart_init(u32 bound);
uint8_t Usart_GetRxFlag(void);
void Clear_Buf(void);
#endif


