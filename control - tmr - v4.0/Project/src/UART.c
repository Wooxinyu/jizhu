#include "UART.h"
#define USART3_IRQn 39                                /*USART1全局中断*/
//volatile u8 A=0X0A;
extern u8 USART_RX_FINISH;                               /*接收完成状态*/
extern u8 USART_RX_READ;                                 /*接收信息读取完成状态*/
extern u16 USART_RX_LENGTH;                              /*接收长度*/
extern u16 USART_RX_READ_LENGTH ;                         /*接收读取长度*/
extern u16 USART_TX_LENGTH;                              /*发送长度*/
extern u8 USART_RX_0X0D;                                 /*接收到0X0D状态*/
extern u8 USART_RX;
extern u8 USART_RX_BUF[USART_REC_LEN_TOTAL];           /*串口接收数组*/
extern u8 USART_RX_BUF_READ[USART_REC_LEN_TOTAL];      /*串口接收读取数组*/
extern u16 USART_TX_BUF[USART_TRA_LEN_TOTAL];           /*串口发送数组*/
extern char USART_RX_BUF_A[USART_REC_LEN_TOTAL]; 
extern uint8_t Count;                                                      // ½ÓÊÕÊý×éÀÛ¼Ó¼ÆÊý       
extern char Rx232buffer[Buf_Max];                                                     // ½ÓÊÕÊý×é
void Uart_Init()                                      /*串口初始化程序*/
{
      GPIO_InitTypeDef gpioInit;                             /*定义GPIO结构体*/
      USART_InitTypeDef uartInit;                            /*定义USART结构体*/
      NVIC_InitTypeDef nvicInit;                             /*定义NVIC结构体*/
	/*1.串口时钟使能，GPIO 时钟使能，复用时钟使能*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
      
      
      //USART_ClockInitTypeDef  USART_ClockInitStructure;
      /*2.串口复位*/
     
      
      /*3.GPIO 端口模式设置*/
      gpioInit.GPIO_Pin = GPIO_Pin_10;                               
      gpioInit.GPIO_Speed = GPIO_Speed_50MHz;                       /*输出速度*/
      gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;                         /*复用推挽输出*/
      GPIO_Init(GPIOB, &gpioInit);                                  

      gpioInit.GPIO_Pin = GPIO_Pin_11;                             
      gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;                   /*浮空输入*/
      GPIO_Init(GPIOB, &gpioInit); 
      
      gpioInit.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;                
	    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	    gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;           //ÍÆÍìÊä³ö
	    GPIO_Init(GPIOB, &gpioInit);
      //³õÊ¼×´Ì¬½«ESP8266¸´Î»Òý½ÅÊ¹ÄÜÖÃ¸ß
      GPIO_SetBits(GPIOB,GPIO_Pin_6);
      GPIO_SetBits(GPIOB,GPIO_Pin_7);
      /*4.串口参数初始化*/
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
      USART_DeInit(USART3);
      uartInit.USART_BaudRate = 115200;                                        /*波特率57600*/
      uartInit.USART_WordLength = USART_WordLength_8b;                        /*数据位8位*/
      uartInit.USART_StopBits = USART_StopBits_1;                             /*停止位1位*/
      uartInit.USART_Parity = USART_Parity_No;                                /*无校验*/
      uartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    /*无硬件控制流*/
      uartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                    /*工作模式*/
      USART_Init(USART3, &uartInit);                                          /*PA9->Tx, PA10->Rx*/
      
      //USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;      //Ê±ÖÓµÍµçÆ½»î¶¯
      //USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;            //ÉèÖÃSCLKÒý½ÅÉÏÊ±ÖÓÊä³öµÄ¼«ÐÔÎªµÍµçÆ½
      //USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;          //Ê±ÖÓµÚÒ»¸ö±ßÑØ½øÐÐÊý¾Ý²¶»ñ
      //USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;  //×îºóÒ»Î»Êý¾ÝµÄÊ±ÖÓÂö³å²»´ÓSCLKÊä³ö
      //USART_ClockInit(USART3, &USART_ClockInitStructure); 
      /*5.初始化 NVIC*/
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
      nvicInit.NVIC_IRQChannel = USART3_IRQn;                                 /*外部中断线*/
      nvicInit.NVIC_IRQChannelPreemptionPriority=2; 
      nvicInit.NVIC_IRQChannelSubPriority = 3; 
      nvicInit.NVIC_IRQChannelCmd = ENABLE; 
      NVIC_Init(&nvicInit);
      
      /*6.开启中断*/
      USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                         /*使能接收中断*/

      /*7.使能串口*/
      USART_Cmd(USART3, ENABLE);
}


void Uart_SendData(u16 Data)                            /*串口发送数据*/
{

      USART_SendData(USART3, Data);

      while(USART_GetFlagStatus(USART3,USART_FLAG_TC) != SET);
}

u8 Uart_SendBuf(u16 SendBufLength)                     /*串口发送不定数组*/
{
      u16 i;
      for(i = 0;(i<SendBufLength)&&(i<USART_TRA_LEN_TOTAL);i++)
      {
            Uart_SendData(USART_TX_BUF[i]);
      }
      return 1;
}

u8 Uart_CheckReceive()                                /*检验是否有输入*/
{                 
    
    return (USART_RX_FINISH);
}

u16 Uart_ReceiveLength()                              /*查看接收数据长度*/
{               
    
    return (USART_RX_LENGTH);
}



u8 Uart_RecBuf()                                       /*串口读取数组*/
{

      if(USART_RX)
      //if(Uart_ReceiveLength())
      {
           u16 i;
          USART_RX_READ_LENGTH = Uart_ReceiveLength();
           for(i = 0;i<Uart_ReceiveLength();i++)
           {
                 USART_RX_BUF_READ[i]=USART_RX_BUF[i];
           }
           USART_RX_READ = 1;         /*接收信息读取完成*/
           /*准备接收下一组数据*/
           USART_RX_FINISH = 0;       /*接收完成状态置0*/
           USART_RX_LENGTH = 0;       /*接收数组长度置0*/
           USART_RX_0X0D = 0;         /*接收到0x0d的状态置0*/
           USART_RX=0;
           return 1;
      }
      else
      {
            
            return 0;
      }
      
}

//void USART3_IRQHandler()                                    /*串口中断服务程序*/
//{
    //u16 Res;
//   if(USART_GetITStatus(USART3, USART_IT_RXNE)!=RESET)       /*接收中断(接收到的数据必须是 0x0d 0x0a 结尾)*/
//    {
       
//      USART_RX_BUF[USART_RX_LENGTH] = USART_ReceiveData(USART3);                        /*读取接收到的数据*/
      
//      if(USART_RX_FINISH==0)                                  /*接收未完成*/
//      {

//            if(USART_RX_0X0D==1)                              /*接收到了0x0d*/
//            {
                
//                if(USART_RX_BUF[USART_RX_LENGTH]!=0x0a)                                 /*Res没接收到0x0a*/
//                {
                  
//                  USART_RX_LENGTH = 0;                        /*接收错误，重新开始*/
//                  USART_RX_0X0D = 0;

//                }
//                else
//               {
                  
//                  USART_RX_FINISH = 1;                         /*接收完成*/
//                  USART_RX_READ = 0;                           /*接收读取未完成*/
//                  USART_RX_0X0D = 0;                           /*接到0x0d状态置0*/
                  //flag = 1;
                //#ifdef UART_INT_HANDLE_INSTANT 
                 // if(Uart_RecBuf()==1)
                 //  {
                 // DoWhenFinishRec();
                 //  }
               // #endif

//                }
//                 USART_RX_FINISH = 0;
                 
//            }
//            else                                                /*还没接收到0x0d*/
//            {
//                  if(USART_RX_BUF[USART_RX_LENGTH]==0x0d)                                 /*接收数据为0x0d*/
//                 {
                        
//                       USART_RX_0X0D = 1;                      /*接到0x0d状态置1*/
//                 }

//                  else                                          /*接收数据不是0x0d*/
//                  {
                        
     //                   USART_RX_BUF[USART_RX_LENGTH] = Res;    /*将接收到的数据存入数组*/
//                        USART_RX_LENGTH++;                      /*数组长度+1*/

//                        if(USART_RX_LENGTH>(USART_REC_LEN_TOTAL-1))
//                        {
//                            USART_RX_LENGTH = 0;               /*接收错误，重新开始*/
//                        }
//                  }
                  
//            }
            
//      }
//      USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//    }
    
//}

void DoWhenFinishRec()
{
      u16 i;
	USART_TX_LENGTH = USART_RX_LENGTH;
     for(i=0;i<USART_RX_LENGTH;i++)
      {
            USART_TX_BUF[i] = USART_RX_BUF[i];
      }
     // printf("AT+CIPSEND=%d\r\n",USART_TX_LENGTH);
      //Delay_ms(200);
      Uart_SendBuf(USART_TX_LENGTH);
      Uart_SendData(0x0d);
      Uart_SendData(0x0a);
}

u16 flag_num=0;
u16 flag_receive_complete=0;
u16 count_data=0;
u16 contr_data_1=0;
u16 contr_data_2=0;
u16 contr_data_3=0;
void USART3_IRQHandler(void)
{  
      //USART_SendData(USART3,A);
  if(USART_GetITStatus(USART3,USART_IT_RXNE)!= RESET)       //½ÓÊÕÖÐ¶Ï
  {  
    USART_RX=1; 
    USART_RX_BUF[USART_RX_LENGTH]= USART_ReceiveData(USART3);  
    USART_RX_BUF_A[USART_RX_LENGTH]= USART_ReceiveData(USART3);
    
		if(flag_num)
		{
			if(count_data==0)
				contr_data_1=USART_ReceiveData(USART3);
			if(count_data==1)
				contr_data_2=USART_ReceiveData(USART3);
			if(count_data==2)
				contr_data_3=USART_ReceiveData(USART3);
			count_data++;
			if(count_data==3)
			{
				flag_receive_complete=1;
				count_data=0;
				flag_num=0;
			}
		}
		if(USART_ReceiveData(USART3)==0xFF)
			flag_num=1;
		  USART_RX_LENGTH++;                                                
                                   
	  if(USART_RX_LENGTH>USART_REC_LEN_TOTAL)                                       //½ÓÊÕÊý´óÓÚ¶¨Òå½ÓÊÕÊý×é×î´ó¸öÊýÊ±£¬´ÓÍ·¿ªÊ¼·ÅÖÃÊý¾Ý
		{
			 USART_RX_LENGTH = 0;
		} 
     
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);         //Çå³ýUSART3µÄÖÐ¶Ï´ý´¦ÀíÎ»
    
  } 
    
//  USART_RX=0;
}
