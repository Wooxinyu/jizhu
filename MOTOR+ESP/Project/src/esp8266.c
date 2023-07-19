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
  /*��ESP8266��������ģ�飬�ɹ��򷵻�'OK'*/
	
	while(!Hand("OK"))                 /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/      
	{	
		printf("AT\r\n");            /*��������ָ��AT*/        
		delay_ms(500);               /*��ʱ*/  
	}
      CLR_Buf();                         /*��ս�������*/ 

      /*��ESP8266�������ù���ģʽ�������'OK'��'no change'*/
	while(!(Hand("OK") | Hand("no change")))   /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
	{	
		printf("AT+CWMODE=1\r\n");           /*���ù���ģʽΪstationģʽ*/
		delay_ms(500);                     /*��ʱ*/
	}
      CLR_Buf();                            /*��ս�������*/
 
      /*���ӵ�WiFi�ȵ�*/
	while(!(Hand("OK")))                       /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
	{	
		printf("AT+CWJAP=\"TP-LINK_EA64\",\"bjut0712\"\r\n");
		delay_ms(2000);                     /*��ʱ*/
	}
   CLR_Buf();                                /*��ս�������*/
   
      /*����������*/
	while(!(Hand("OK")))                        /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
	{	

		printf("AT+CIPMUX=1\r\n");   /*����ESP8266��ATָ��*/
		delay_ms(3000);                      /*��ʱ*/
	}
  CLR_Buf();   	/*��ս�������*/
	
	/*����������*/
	while(!(Hand("OK")))                        /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
	{	

		printf("AT+CIPSERVER=1,9090\r\n");   /*����ESP8266��ATָ��*/
		delay_ms(3000);                      /*��ʱ*/
	}
  CLR_Buf();                                  /*��ս�������*/
	/*���ø÷�����IP��ַ*/
	while(!(Hand("OK")))                        /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
	{	
		printf("AT+CIPSTA_DEF=\"192.168.3.217\",\"192.168.3.1\",\"255.255.255.0\"\r\n");   /*����ESP8266��ATָ��*/
		delay_ms(3000);                      /*��ʱ*/
	}
  CLR_Buf();     
	
      /*�رջ���*/
//	while(!(Hand("OK")))                       /*�ж��Ƿ����óɹ����粻�ɹ�����ʱ���ٷ���*/
//	{   
//	    printf("ATE0\r\n");        /*ʹ�ܷ�������*/
//	    delay_ms(2000);                     /*��ʱ*/
//	}
//   CLR_Buf();                   /*��ս�������*/
}
