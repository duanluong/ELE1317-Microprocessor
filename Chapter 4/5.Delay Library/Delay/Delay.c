#include "stm32f10x.h"
#include "Delay.h"
static u8 fac_us=0;
static u16 fac_ms=0;
void DELAY_Init (unsigned char _CLK)
{
    SysTick->CTRL&=0xfffffffb;
    fac_us=_CLK/8;
    fac_ms=(u16)fac_us*1000;
}
void DELAY_ms (unsigned int _vrui_Time)
{
    u32 temp;
    
    SysTick->LOAD=(u32)_vrui_Time*fac_ms;
    SysTick->VAL =0x00;
    SysTick->CTRL=0x01;
    do{
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL=0x00;
    SysTick->VAL =0X00;
}
void DELAY_us (unsigned long _vrui_Time)
{
    u32 temp;

    SysTick->LOAD=_vrui_Time*fac_us;
    SysTick->VAL=0x00;
    SysTick->CTRL=0x01 ;
    do{
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL=0x00;
    SysTick->VAL =0X00;
}