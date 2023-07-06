#include "stm32f10x.h"
#include "delay.h"
#include "bsp_key.h"
#include "bsp_motor_init.h"
#include "motor_control.h"
#include "usart.h"
#include "stdio.h"
#include "usart_scan.h"
#include <math.h>

extern u8 Rx_Flag; 
extern u8 USART_RX_BUF[USART_REC_LEN];


int aim_pos = 50;
volatile int cur_pos = 50;
volatile int distance;
int sig;
int main(void) 
{   	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	Motor_Init();
	KEY_Init();
	uart_init(115200);
	Usart2_Init(115200);
//	bufinit1();
	delay_ms(1500);
	u16 len;
	while(1)
	{
//		if(Rx_Flag == 1)
//		{	
//			aim_pos = USART_RX_BUF[0];
//			if(aim_pos != cur_pos)
//			{
//				distance = aim_pos - cur_pos;
//				if(distance > 0)
//				{	
//					MOTOR_SCAN_UP
//					sig = 1;
//				}
//				else
//				{
//					MOTOR_SCAN_DOWN
//					sig = -1;
//				}
//				distance = sig*distance;
//				TIM_Cmd(TIM4,ENABLE);
//			}
//			Rx_Flag = 0;
//		}
//		if(distance == 0)
//		{
//			TIM_Cmd(TIM4,DISABLE);
//		}
		printf("n0.val=%d\xff\xff\xff",cur_pos);
		printf("j0.val=%d\xff\xff\xff",cur_pos);
		if(getval1() > 0x1000)	
		{
			MOTOR1_STOP
		}
		else
		{
			MOTOR1_RUN
		}
		if(getval2()>0x1000)
		{
			MOTOR2_STOP
		}
		{
			MOTOR2_RUN
		}
		if(getval3() > 0x1000)
		{
			MOTOR_SCAN_STOP
		}
		else
		{
			MOTOR_SCAN_RUN
		}
	}
}

	


