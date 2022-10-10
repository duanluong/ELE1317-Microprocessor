#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

#include "Delay.h"						// Delay Library

void LED_Init (void);

int main (void){
	SystemInit();
	
	Delay_Init(SystemCoreClock/1000000);
	LED_Init();
	while(1){
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(1000);
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


