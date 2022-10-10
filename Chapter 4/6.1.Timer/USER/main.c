#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void LED_Init (void);
void Timer2_Init (void);
void Timer4_Init (void);
void NVIC_InitIRQTimer4 (void);

int main (void){
	SystemInit();
	
	LED_Init();
	Timer2_Init();
	Timer4_Init();
	while(1){
		if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
			//Toggle LED B1 when Timer 2 is updated
			if( GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1) == Bit_SET){
				GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);
			}
			else{
				GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
			}
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
		}
	}
}

//Init GPIO as output, using for control LED
void LED_Init (void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @brief Timer2 init function.
 * TIM_CLK: System clock/2 - APB1
 * TIM_Prescaler - PSC: 35
 * TIM_Period - ARR: 50000
 * TIM_ClockDivision - RCR: 0
 * 50000us = 50ms for 1 cycles
 * Mode: Count up
 */
void Timer2_Init (void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler = 36-1;
	TIM_TimeBaseStructure.TIM_Period = 50000-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief Timer4 init function.
 * TIM_CLK: System clock/2 - APB1
 * TIM_Prescaler - PSC: ((SystemCoreClock/2)/1000000)-1; 1us for 1 counter
 * TIM_Period - ARR: 1000 - 1
 * TIM_ClockDivision - RCR: 0
 * 1000us = 1ms for 1 cycles
 * Mode: Count up
 */
void Timer4_Init (void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;     // TIM2,3,4 Chia tan 2, 1 chia tan 1
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

/**
 * @brief Active Interrupt function for Timer 4
 * TIM4_IRQHandler will be called each cycles of Timer 4
 * 
 */
void NVIC_InitIRQTimer4 (void){
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Function is called when have TIM_IT_Update event
 * 
 */
void TIM4_IRQHandler(void){
	//Toggle LED B0 when Timer 2 is updated on Interrupt function
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
		if( GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0) == Bit_SET){
			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
		}
		else{
			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
	}
}
