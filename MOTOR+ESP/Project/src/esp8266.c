#include "esp8266.h"
#include "usart.h"	
#include "delay.h"
#include "string.h"
#include "stdio.h"


u8 Hand(char *a)
{ 
      if(strstr(USART_RX_BUF_A,a)!=NULL)    
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void esp_Senddata(char buf[])
{
	int len = strlen(buf);
	printf("AT+CIPSEND=0,%d\r\n",len);
	delay_ms(500);
	printf("%s",buf);
	
}

void CLR_Buf(void)
{
	uint8_t k;
  for(k=0;k<USART_RX_LEN;k++)      
  {
			USART_RX_BUF[k] = 0;
			USART_RX_BUF_A[k] = 0;
	}      
	USART_BUF_TAIL = 0;
}

void ESP8266_Init()
{
  /*向ESP8266发送联机模块，成功则返回'OK'*/
	
	while(!Hand("OK"))                 /*判断是否设置成功，如不成功，延时后再发送*/      
	{	
		printf("AT\r\n");            /*发送联机指令AT*/        
		delay_ms(500);               /*延时*/  
	}
      CLR_Buf();                         /*清空接收数组*/ 

      /*向ESP8266发送设置工作模式命令，返回'OK'或'no change'*/
	while(!(Hand("OK") | Hand("no change")))   /*判断是否设置成功，如不成功，延时后再发送*/
	{	
		printf("AT+CWMODE=1\r\n");           /*设置工作模式为station模式*/
		delay_ms(500);                     /*延时*/
	}
      CLR_Buf();                            /*清空接收数组*/
 
      /*连接到WiFi热点*/
	while(!(Hand("OK")))                       /*判断是否设置成功，如不成功，延时后再发送*/
	{	
		printf("AT+CWJAP=\"TP-LINK_EA64\",\"bjut0712\"\r\n");
		delay_ms(2000);                     /*延时*/
	}
   CLR_Buf();                                /*清空接收数组*/
   
      /*开启多练接*/
	while(!(Hand("OK")))                        /*判断是否设置成功，如不成功，延时后再发送*/
	{	

		printf("AT+CIPMUX=1\r\n");   /*发送ESP8266的AT指令*/
		delay_ms(3000);                      /*延时*/
	}
  CLR_Buf();   	/*清空接收数组*/
	
	/*开启服务器*/
	while(!(Hand("OK")))                        /*判断是否设置成功，如不成功，延时后再发送*/
	{	

		printf("AT+CIPSERVER=1,9090\r\n");   /*发送ESP8266的AT指令*/
		delay_ms(3000);                      /*延时*/
	}
  CLR_Buf();                                  /*清空接收数组*/
	/*配置该服务器IP地址*/
	while(!(Hand("OK")))                        /*判断是否设置成功，如不成功，延时后再发送*/
	{	
		printf("AT+CIPSTA_DEF=\"192.168.3.217\",\"192.168.3.1\",\"255.255.255.0\"\r\n");   /*发送ESP8266的AT指令*/
		delay_ms(3000);                      /*延时*/
	}
  CLR_Buf();     
	
      /*关闭回显*/
//	while(!(Hand("OK")))                       /*判断是否设置成功，如不成功，延时后再发送*/
//	{   
//	    printf("ATE0\r\n");        /*使能发送数据*/
//	    delay_ms(2000);                     /*延时*/
//	}
//   CLR_Buf();                   /*清空接收数组*/
}
