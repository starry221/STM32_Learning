#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_8;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Instructure);
}	

static u8 last1=1,last2=1,last3=1;
static u8 cnt1=0,cnt2=0,cnt3=0;
u8 now1,now2,now3;


u8 Key_GetNum(void)
{
	u8 key=0;
	now1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	now2=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
	now3=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);

	if(last1!=now1)
	{
		cnt1++;
		if(cnt1>=20) 
		{
			cnt1=0;
			last1=now1;
			if(last1==0) {key=1;}
		}
	}
	else {cnt1=0;}

	if(last2!=now2)
	{
		cnt2++;
		if(cnt2>=20) 
		{
			cnt2=0;
			last2=now2;
			if(last2==0) {key=2;}
		}
	}
	else {cnt2=0;}

	if(last3!=now3)
	{
		cnt3++;
		if(cnt3>=20)
		{
			cnt3=0;
			last3=now3;
			if(last3==0) {key=3;}
		}
	}
	else {cnt3=0;}

	return key;
}





























