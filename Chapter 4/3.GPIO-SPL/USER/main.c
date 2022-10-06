#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void delay(int time);
void LED_Init (void);
void Input_Init (void);
void Port_Init (void);

int main(void){
	unsigned char readInputValue;
	unsigned char countValue;
		
	SystemInit();
	LED_Init();
	Input_Init();
	while(1){
		// Read B9 and export to C13
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_SET){
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		}
		else{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		}
		
		//Read A0-A7 and export to A8-A15
		readInputValue = GPIO_ReadInputData(GPIOA);
		GPIO_Write(GPIOA, readInputValue >> 8);
		
		//Increase value of B0-B7
		countValue++;
		GPIO_Write(GPIOB, countValue);
		
		delay(1000);
	}
}

void delay(int time){
	unsigned int count;
	while(time--){
		for (count = 0; count < 1000; count++);
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

void Input_Init (void){
	GPIO_InitTypeDef gpio_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio_InitStruct.GPIO_Pin = GPIO_Pin_9;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOB, &gpio_InitStruct);
}

void Port_Init (void){
	GPIO_InitTypeDef gpio_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// Config A0-A7 as Output
	gpio_InitStruct.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | \
								GPIO_Pin_2 | GPIO_Pin_3 | \
								GPIO_Pin_4 | GPIO_Pin_5 | \
								GPIO_Pin_6 | GPIO_Pin_7;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_InitStruct);
	
	// Config A8-A15 as Input
	gpio_InitStruct.GPIO_Pin = 	GPIO_Pin_8 | GPIO_Pin_9 | \
								GPIO_Pin_10 | GPIO_Pin_11 | \
								GPIO_Pin_12 | GPIO_Pin_13 | \
								GPIO_Pin_14 | GPIO_Pin_15;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &gpio_InitStruct);	
	
	// Config B0-B7 as Output
	gpio_InitStruct.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | \
								GPIO_Pin_2 | GPIO_Pin_3 | \
								GPIO_Pin_4 | GPIO_Pin_5 | \
								GPIO_Pin_6 | GPIO_Pin_7;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_InitStruct);
}
 
