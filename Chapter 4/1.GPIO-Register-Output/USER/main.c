#include "stm32f10x.h"                  // Device header

void delay(int time);
void RCC_Config (void);
void GPIO_Config (void);
void GPIO_WriteToLED (unsigned char value);
void GPIO_SetHighLevel (void);
void GPIO_SetLowLevel (void);

int main (void){
	SystemInit();
	
	// Config for LED Pin as output
	RCC_Config();
	GPIO_Config();
	while(1){
		GPIO_WriteToLED(1);
		delay(300);
		GPIO_WriteToLED(0);
		delay(300);
		/* 2nd way */
//		GPIO_SetHighLevel();
//		delay(1000);
//		GPIO_SetLowLevel();
//		delay(1000);
	}
}

void delay(int time){
	unsigned int count;
	while(time--){
		for (count = 0; count < 1000; count++);
	}
}

void RCC_Config (void){
	// Enable clock for GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

void GPIO_Config (void){
	//Clear GPIOC config
	GPIOC->CRH = 0x00000000;
	GPIOC->CRL = 0x00000000;
	
	// Config C13 as OutputPush-pull CNF[1:0] = 00, MODE[1:0] = 11
	GPIOC->CRH |= 0x00300000; 
}

void GPIO_WriteToLED (unsigned char value){
	if(value){
		GPIOC->ODR |= (1<<13);
	}
	else{
		GPIOC->ODR &= ~(1<<13);
	}
}

void GPIO_SetHighLevel (void){
	GPIOC->BSRR = (1<<13);
}

void GPIO_SetLowLevel (void){
	GPIOC->BRR = (1<<13);
}

