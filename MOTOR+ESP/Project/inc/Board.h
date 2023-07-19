#ifndef __BOARD__H
#define __BOARD__H

/*本头文件用于存放程序中所需要的变量*/
#include "srcIncluder.h"
#include "UART.h"
#include "Key.h"
#include "ESP8266.h"



/*STM32系统所需要的公共变量*/
   /*时间调度变量*/
    volatile u32 TimeForDelay;                                /*延时时间*/
    volatile u32 millis;
   
   /*串口实现所需要的公共变量*/
    volatile u8 USART_RX_FINISH = 0;                           /*接收完成状态*/
    volatile u8 USART_RX_READ = 0;                             /*接收信息读取完成状态*/
    volatile u16 USART_RX_LENGTH = 0;                          /*接收长度*/
    volatile u16 USART_RX_READ_LENGTH = 0;                     /*接收读取长度*/
    volatile u16 USART_TX_LENGTH = 0;                          /*发送长度*/
    volatile u8 USART_RX_0X0D = 0;                             /*接收到0X0D状态*/
    volatile u8 USART_RX = 0;
    volatile u8 USART_RX_BUF[USART_REC_LEN_TOTAL];           /*串口接收数组*/
    volatile u8 USART_RX_BUF_READ[USART_REC_LEN_TOTAL];      /*串口接收读取数组*/
    volatile char USART_RX_BUF_A[USART_REC_LEN_TOTAL];
    volatile u16 USART_TX_BUF[USART_TRA_LEN_TOTAL];           /*串口发送数组*/

/*外部设备所需的公共变量*/
   /*板载硬件的公共变量*/
    volatile u8 swich_state = 1;      /*板载按钮状态，READ:信息已读  PRESS:正在按下  NEW:有新消息*/
    volatile u8 swich_info = SW_SHORT;      /*板载按钮信息，长/短*/
    volatile u32 swich_time;                /*按钮时间*/
    volatile uint8_t Count=0;                                                      // ½ÓÊÕÊý×éÀÛ¼Ó¼ÆÊý       
    volatile char Rx232buffer[Buf_Max];

/*软件功能所需变量*/
   /*主要状态变量*/
   volatile int zeroPressure = 0;          
   volatile int minPressure = 0;
   volatile int maxPressure = 10;
   volatile int zeroDisplacement = 0;
   volatile int minDisplacement = 0;
   volatile int maxDisplacement = 200;


















#endif
