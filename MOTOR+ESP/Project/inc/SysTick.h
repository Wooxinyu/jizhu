#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "srcIncluder.h"

extern volatile u32 TimeForDelay;
extern volatile u32 millis;

void SysTick_Init(void);
void OnSysTick(void);
void Delay_ms(u32 ms);



#endif

