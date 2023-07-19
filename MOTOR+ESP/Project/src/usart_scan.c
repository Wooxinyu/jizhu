#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "usart_scan.h"
#include <math.h>
static int max(int a,int b)
{
	return a>b?a:b;
}

typedef struct device_buf
{
//	uint16_t cmd;
	uint16_t head;
	uint16_t tail;
	u8 			 flag;
	int val;
	int16_t  dif; 
	int16_t  maxdif;
}device;

device device1={0};
device device2={0};
device device3={0};

void Usart2_Init(uint32_t bound)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART1��GPIOAʱ��
	
	//USART2_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//USART2_RX	  GPIOA.3��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}



void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	static u8 state = 0;
	static u8 i = 0;
	static u8 flag = 0;
	static u8 tmp;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		if(state == 0)
		{
				if(Res == 0xaa)
				{
					state = 1;
				}
				else
				{
					state = 0;
				}
		}
		else if(state == 1)	
		{
			flag = Res;
			state = 2;
		}
		else if(state == 2)
		{
			switch (flag)
			{
				case 01:
					if(i == 0)
					{
						tmp = Res;
						++i;
					}else if(i == 1)
					{
//						device1.val[0] = tmp <<8 | Res;
						device1.val = (tmp<<8|Res);
//						device1.tail ^=1; 
		 				device1.flag = 1;
						state = 0;
						i = 0;
					}
					break;
				case 02:
					if(i == 0)
					{
						tmp = Res;
						i++;
					}else if(i == 1)
					{
						device2.val = (tmp<<8|Res);
						//device2.tail ^= 1;
						if(device2.tail == 0)
							device2.flag = 1;
						state = 0;
						i = 0;
					}
					break;
				case 03:
					if(i == 0)
					{
						tmp = Res;
						i++;
					}else if(i == 1)
					{
						device3.val = (tmp<<8|Res);
//						device3.tail ^= 1;
//						if(device3.tail == 0)
//							device3.flag =1;
						state = 0;
						i = 0;
					}
					break;	
				default:
					state = 0;
			}
		}	
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  } 

} 

int getval1(void)
{
	return device1.val;
}

int getval2(void)
{
	return device2.val;
}

int getval3(void)
{
	return device3.val;
}


int getmax1(void)
{        
	return device1.maxdif;

}
//void caldif1(void)
//{
//	if(device1.flag == 1 && device1.val[1]!=0)
//		device1.dif = device1.val[0]-device1.val[1];
//		device1.maxdif = max(abs(device1.dif),abs(device1.maxdif));
//	device1.flag = 0;

//}
