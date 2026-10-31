#include "stm32f10x.h"                  // Device header
#include "OLED.h"


void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Instructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}	


static u8 loc;
static u8 tick;



void FlowLED(void)
{
	tick++;
	if(tick>=200)
	{
		tick=0;

		GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

		OLED_ShowNum(2,10,loc+1,1);

		switch(loc)
		{
		case 0:GPIO_ResetBits(GPIOB,GPIO_Pin_12); break;
		case 1:GPIO_ResetBits(GPIOB,GPIO_Pin_13); break;
		case 2:GPIO_ResetBits(GPIOB,GPIO_Pin_14); break;
		case 3:GPIO_ResetBits(GPIOB,GPIO_Pin_15); break;
		}

		loc++;
		if(loc>3) {loc=0;}
	}
}

void FlowLED_Reset(void) {loc=0;}

u8 Getloc(void) {return loc;}

























