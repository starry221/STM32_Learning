#include "stm32f10x.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "PWM.h"
#include "Delay.h"

static u8 power=0;
static u8 mode=1;
static u8 key=0;

void Device_ON(void)
{
	OLED_Clear();
	OLED_ShowString(1,1,"Mode:");
	OLED_ShowNum(1,5,mode,1);
}

void Device_OFF(void)
{
	OLED_Clear();
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	FlowLED_Reset();
	TIM_SetCompare3(TIM3,0);
	BreathLED_Reset();
	ctrl_Reset();
	OLED_ShowString(1,1,"OFF");
}





int main(void)
{
	OLED_Init();
	Key_Init();
	PWM2_Init();
	LED_Init();
	PWM_Init();

	OLED_ShowString(1,1,"TryPressKey1");

	while(1)
	{
		key=Key_GetNum();
		if(key==1) 
		{
			power=!power;
			if(power==1) Device_ON();
			else Device_OFF();
		}
		if(key==2&&power==1)
		{
			if(mode==1) {mode=2;}
			else if(mode==2) {mode=3;}
			else if(mode==3) {mode=1;}

			GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			TIM_SetCompare3(TIM3,0);
			FlowLED_Reset();
			BreathLED_Reset();
			ctrl_Reset();

			OLED_ShowString(2,1,"                ");
			OLED_ShowNum(1,5,mode,1);
		}
		if(power==1)
		{
			if(mode==1) 
			{
				FlowLED();
				OLED_ShowString(2,1,"Location:");
			}
	
			else if(mode==2) BreathLED(); 
			else if(mode==3) 
			{
				OLED_ShowString(2,1,"Location:");
				if(key==3) { ctrl();}
			}
		}
		Delay_ms(1);
	}
}


