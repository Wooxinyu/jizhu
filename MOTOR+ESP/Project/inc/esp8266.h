#ifndef __ESP8266_H
#define __ESP8266_H

#include "stm32f10x.h"


void ESP8266_Init(void);     /*ESP8266配置函数*/
u8 Hand(char *a);           /*握手成功与否函数*/        
void CLR_Buf(void);
void esp_Senddata(char buf[]);
#endif

