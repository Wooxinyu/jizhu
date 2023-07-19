#ifndef __UART_H__
#define __UART_H__

#include "srcIncluder.h"
//#include "ESP8266.h"
#include "SysTick.h"
#define USART_REC_LEN_TOTAL 50                                   /*串口接收数组的最大长度*/
#define USART_TRA_LEN_TOTAL 50                                   /*串口发送数组的最大长度*/

#define Buf_Max 50



#define UART_INT_HANDLE_BETWEEN_LOOP
void Uart_Init(void);                              /*串口初始化程序*/

void Uart_SendData(u16 Data);                      /*串口发送数据*/

u8 Uart_SendBuf(u16 SendBufLength);                /*串口发送不定数组*/

u8 Uart_CheckReceive(void);                            /*检验是否有输入*/

u16 Uart_ReceiveLength(void);                          /*查看接收数据长度*/

u8 Uart_RecBuf(void);                                  /*串口读取数组*/

void USART3_IRQHandler(void) ;                       /*串口中断服务程序*/

void DoWhenFinishRec(void);                        /*串口调试程序*/
//void USART3_IRQHandler(void);

//u8 Check(u16 A);
#endif
