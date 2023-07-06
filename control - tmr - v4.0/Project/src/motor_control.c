#include "motor_control.h"
#include "stm32f10x.h"
#include "bsp_motor_init.h"

void TIM3_Control_Decision(int index)
{
	
	switch (index)
			{
				case 0:
					MOTOR1_STOP		
					MOTOR_WASH_DIR_DOWN				
					MOTOR_WASH_RUN				
					break;
				case 1:
					MOTOR_WASH_STOP
					WASH_ON
					break;
				case 2:
					WASH_OFF
					MOTOR_WASH_DIR_UP
					MOTOR_WASH_RUN
					break;
				case 3:
					MOTOR_WASH_STOP
					MOTOR_SWAP_RUN
					break;
				case 4:
					MOTOR_SWAP_STOP
					MOTOR1_RUN
					break;
				case 5:
					MOTOR1_STOP
					MOTOR_WASH_DIR_DOWN
					MOTOR_WASH_RUN
					break;
				case 6:
					MOTOR_WASH_STOP
					break;
				case 7:
					MOTOR_WASH_DIR_UP
					MOTOR_WASH_RUN
					break;	
				case 8:
					MOTOR_SWAP_RUN
					MOTOR_WASH_STOP
					break;
				case 9:
					MOTOR_SWAP_STOP
					MOTOR1_RUN
					break;
				case 10:
					MOTOR1_STOP
					MOTOR_WASH_DIR_DOWN
					MOTOR_WASH_RUN
					break;
				case 11:
					MOTOR_WASH_STOP
					break;
				case 12:
					MOTOR_WASH_DIR_UP
					MOTOR_WASH_RUN
					break;
				case 13:
					MOTOR_WASH_STOP
					MOTOR1_RUN
					break;
				default:
					MOTOR1_STOP
					TIM_Cmd(TIM3,DISABLE);
					MOTOR_SCAN_RUN
					TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);
			}
}

