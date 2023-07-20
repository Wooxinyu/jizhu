#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "motor_control.h"
#include "usart.h"
#include "stdio.h"
#include "usart_scan.h"
#include <math.h>
#include "esp8266.h"
#include "string.h"

#define POSCTL  0
#define PASCTL  1
#define NETTEST 1

extern u8 Rx_Flag; 
//extern char USART_RX_BUF[USART_REC_LEN];
void SendPress(void);

int aim_pos = 50;
volatile int cur_pos = 50;
volatile int distance;
int sig;
int connected = 0;
int num = 0;
int pressure1 = 0, pressure2 = 0, pressure3 = 0;
int main(void) 
{   	

	int len = 0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);

	
#if POSCTL|PASCTL
	Motor_Init();
	KEY_Init();
#endif

//	bufinit1();
	delay_ms(1500);

		
	#if NETTEST
		char usart_tx_buf[128] = {0};
		char usart_command[64] = {0};
		ESP8266_Init();
	#endif
	Usart2_Init(115200);
	while(1)
	{
	#if POSCTL
		if(Rx_Flag == 1)
		{	
			aim_pos = USART_RX_BUF[0];
			if(aim_pos != cur_pos)
			{
				distance = aim_pos - cur_pos;
				if(distance > 0)
				{	
					MOTOR_SCAN_UP
					sig = 1;
				}
				else
				{
					MOTOR_SCAN_DOWN
					sig = -1;
				}
				distance = sig*distance;
				TIM_Cmd(TIM4,ENABLE);
			}
			Rx_Flag = 0;
		}
		if(distance == 0)
		{
			TIM_Cmd(TIM4,DISABLE);
		}
		printf("n0.val=%d\xff\xff\xff",cur_pos);
		printf("j0.val=%d\xff\xff\xff",cur_pos);
	#endif
		pressure1 = getval1();
		pressure2 = getval2();
		pressure3 = getval3();
	#if PASCTL

		if(pressure1 > 5000)	
		{
			MOTOR1_STOP
		}
		else
		{
			MOTOR1_RUN
		}
//		if(pressure2>5000)
//		{
//			MOTOR2_STOP
//		}
//		{
//			MOTOR2_RUN
//		}
		if(pressure3 > 5000)
		{
			MOTOR_SCAN_STOP
		}
		else
		{
			MOTOR_SCAN_RUN
		}
	#endif
		
	#if NETTEST
		if(Hand("CONNECT"))
		{
			connected = 1;
			CLR_Buf();
		}
		if(Hand("CLOSED"))
		{
			connected = 0;
			CLR_Buf();
		}
		if(connected)
		{
			CLR_Buf();
			sprintf(usart_tx_buf,"pressure1 num :%d\r\npressure2 num :%d\r\npressure3 num :%d\r\n",pressure1,pressure2,pressure3);
			esp_Senddata(usart_tx_buf);
			len = strlen(usart_tx_buf);
			sprintf(usart_command,"AT+CIPSEND=0,%d\r\n",len);
			printf("%s",usart_command);
			delay_ms(50);
			printf("%s",usart_tx_buf); 
			CLR_Buf();
		}
	#endif
	}
}

	

void SendPress(void)
{
	char usart_tx_buf[50];
	sprintf(usart_tx_buf,"pressure1 value :%d\r\n",getval1());
	esp_Senddata(usart_tx_buf);
	sprintf(usart_tx_buf,"pressure2 value :%d\r\n",getval2());
	esp_Senddata(usart_tx_buf);
	sprintf(usart_tx_buf,"pressure3 value :%d\r\n",getval3());
	esp_Senddata(usart_tx_buf);
}
