#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num=10000;
uint8_t Last_Flag=0;
uint8_t Flag=0;

int main(void)
{
	OLED_Init();
	OLED_ShowString(1,1,"Countdown:");
	Timer_Init();




	while(1)
	{
		if(Flag==0)
		{
			OLED_ShowNum(2,1,Num,5);
		}
		else if(Last_Flag==0)
		{
			OLED_Clear();
			OLED_ShowString(1,1,"Follow");
			OLED_ShowString(2,1,"Ace_Taffy");
			OLED_ShowString(3,1,"Thank");
			OLED_ShowString(4,1,"Moew!");
			
			Last_Flag=1;
		}
	
		Delay_ms(500);
	
	}


}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(Num>10000)
		{
			Num=10000;
		}
		else if(Num>0)
		{
			Num--;
			if(Num==0)
			{
				Flag=1;
				TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
				
			}
		}	
		
	}

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

}
