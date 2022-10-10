#include "stm32f10x.h"
#include "Delay.h"

static uint8_t fac_us = 0;
static uint16_t fac_ms = 0;

void Delay_Init (unsigned char _CLK)
{
    SysTick->CTRL &= 0xfffffffb;
    fac_us = _CLK/8;
    fac_ms = (uint16_t)fac_us*1000;
}

void Delay_ms (unsigned int _vrui_Time)
{
    u32 temp;
    
    SysTick->LOAD = (uint32_t)_vrui_Time * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL = 0x01;
    do{
        temp=SysTick->CTRL;
    }
    while((temp&0x01) && (!(temp&(1<<16))));
    SysTick->CTRL = 0x00;
    SysTick->VAL = 0X00;
}

void Delay_us (unsigned long _vrui_Time)
{
    u32 temp;

    SysTick->LOAD = _vrui_Time * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL = 0x01 ;
    do{
        temp = SysTick->CTRL;
    }
    while((temp&0x01) && (!(temp&(1<<16))));
    SysTick->CTRL = 0x00;
    SysTick->VAL = 0X00;
}

