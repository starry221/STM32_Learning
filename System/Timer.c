#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef Timer_InitStructure;
	Timer_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	Timer_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	Timer_InitStructure.TIM_Period=10000-1;
	Timer_InitStructure.TIM_Prescaler=7200-1;
	Timer_InitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&Timer_InitStructure);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM2,ENABLE);

}
