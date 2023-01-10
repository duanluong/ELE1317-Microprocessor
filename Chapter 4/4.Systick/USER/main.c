#include "stm32f10x.h" // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h" // Keil::Device:StdPeriph Drivers:GPIO

volatile unsigned char systick_Flag;

void LED_Init (void);
void LED_Toggle(void);

int main (void){
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	LED_Init();
	while(1){
		if(systick_Flag == 1){
			systick_Flag = 0;
			LED_Toggle();
		}
	}
}

void LED_Init (void){
	GPIO_InitTypeDef gpio_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	gpio_InitStruct.GPIO_Pin = GPIO_Pin_13;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpio_InitStruct);
}

void LED_Toggle(void){
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) == Bit_RESET){
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	}
	else{
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	}
}

void SysTick_Handler(void){
	systick_Flag = 1;
}

