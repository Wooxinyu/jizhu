#ifndef __ESP8266_H
#define __ESP8266_H

#include "stm32f10x.h"


void ESP8266_Init(void);     /*ESP8266���ú���*/
u8 Hand(char *a);           /*���ֳɹ������*/        
void CLR_Buf(void);
void esp_Senddata(char buf[]);
#endif

