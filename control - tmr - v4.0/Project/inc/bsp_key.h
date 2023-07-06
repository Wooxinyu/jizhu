#ifndef _BSP_KEY_H
#define _BSP_KEY_H



#define KEY_START_Port GPIOC
#define KEY_START_Pin  GPIO_Pin_8

#define KEY_DOWN_PORT GPIOC
#define KEY_DOWN_PIN  GPIO_Pin_9

#define SWITCH_PORT   GPIOA
#define SWITCH_PIN    GPIO_Pin_3

#define KEY_CONTROL_CLK   RCC_APB2Periph_GPIOC |  RCC_APB2Periph_GPIOA

#define SWITCH (GPIO_ReadInputDataBit(SWITCH_PORT,SWITCH_PIN))
#define KEY_UP (GPIO_ReadInputDataBit(KEY_UP_PORT,KEY_UP_PIN))
#define KEY_DOWN (GPIO_ReadInputDataBit(KEY_DOWN_PORT,KEY_DOWN_PIN))


#define SWITCH_ON 1
#define KEY_DOWN_PRES 3 
#define KEY_UP_PRES 4
#define NO_PRES  0


void KEY_Init(void);





#endif

