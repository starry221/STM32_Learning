#include "stm32f10x.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "PWM.h"
#include "Delay.h"

int main(void)
{
	PWM_Init();
	OLED_Init();
	OLED_Clear();
	Key_Init();
	u8 key;

	while(1)
	{
		key=Key_GetNum();
		if(key==1)
		{
			ctrl();
		}

		Delay_ms(1);
	}
}
