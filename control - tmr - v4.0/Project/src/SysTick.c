#include "SysTick.h"

void SysTick_Init()
{
        if(SysTick_Config(72000)==1)   /*设置分频时间为1ms*/
        {
            while(1);
        }
}

void OnSysTick()
{
        millis++;
        if(TimeForDelay)
        {
           TimeForDelay--;
        }
}

void Delay_ms(u32 ms)
{
        TimeForDelay=ms;
        while(TimeForDelay);
}
