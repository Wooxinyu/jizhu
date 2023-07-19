#ifndef USART_H__
#define	USART_H__ 

#include "stm32f10x.h"

#define USART_REC_LEN  			2 	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define USART_RX_LEN       64	  	


extern char  USART_RX_BUF[USART_RX_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern char USART_RX_BUF_A[USART_RX_LEN];
extern int USART_BUF_TAIL;

void uart_init(u32 bound);
uint8_t Usart_GetRxFlag(void);
void Clear_Buf(void);

#endif


