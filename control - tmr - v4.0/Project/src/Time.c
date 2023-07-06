#include "Time.h"

void delay(volatile u32 ms) 
{
    volatile u32 i, j;
    for(i = 0; i < 6000; ++i)
    {
        for(j = 0; j < ms; ++j);
    }
}
