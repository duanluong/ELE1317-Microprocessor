#include "stm32f10x.h"                  // Device header

void delay(int time);
void RCC_Config (void);
void GPIO_Config (void);
void GPIO_WriteToLED (unsigned char value);
void GPIO_SetHighLevel (void);
void GPIO_SetLowLevel (void);
unsigned char GPIO_GetButton (void);

int main (void){
	SystemInit();
	
	// Config for LED Pin as output
	RCC_Config();
	GPIO_Config();
	while(1){
		if(GPIO_GetButton() != 0){
			GPIO_SetHighLevel();
		}
		else{
			GPIO_SetLowLevel();
		}
		delay(1);
	}
}

void delay(int time){
	unsigned int count;
	while(time--){
		for (count = 0; count < 1000; count++);
	}
}

void RCC_Config (void){
	// Enable clock for GPIOC and GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN;
}

void GPIO_Config (void){
	//Clear GPIOC and GPIOB config
	GPIOC->CRH = 0x00000000;
	GPIOC->CRL = 0x00000000;
	
	GPIOB->CRH = 0x00000000;
	GPIOB->CRL = 0x00000000;
	
	// Config C13 as Output Push-pull CNF[1:0] = 00, MODE[1:0] = 11
	// CRL for pin 0-7
	// CRH for pin 8-15
	GPIOC->CRH |= 0x00300000;
	// Config B9 as Input Pull-up CNF[1:0] = 10, MODE[1:0] = 00
	GPIOB->CRH |= 0x00000080;
	GPIOB->ODR |= (1<<9);
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

unsigned char GPIO_GetButton (void){
	if(GPIOB->IDR & (1<<9)){
		return 1;
	}
	
	return 0;
}


