#include "stm32f10x.h"
#include "OLED.h"

void PWM_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Instructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);

    TIM_InternalClockConfig(TIM3);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=20000-1;   //ARR   //Freq=72M/PSC+1/ARR/1
    TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;   //PSC 
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);


    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1 ;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse=0;  //Duty=CCR/ARR+1
    TIM_OC3Init(TIM3,&TIM_OCInitStructure);

    TIM_Cmd(TIM3,ENABLE);


}	

static u8 dir=0;
static u8 cnt=0;
static u8 bright=0;


void BreathLED(void)
{
    if(++cnt<10) return;
    cnt=0;

    if(dir>0)
    {
        if(bright<100) bright++;
        else dir=0;
    }
    else
    {
        if(bright>0) bright--;
        else dir=1;
    }
    TIM_SetCompare3(TIM3,bright);
    OLED_ShowNum(2,8,bright,3);
    OLED_ShowString(2,1,"bright:");
}

void BreathLED_Reset(void)
{
    dir=0;
    cnt=0;
    bright=0;
}

void PWM_SetCompare(u16 Compare)
{
    TIM_SetCompare3(TIM3,Compare);
}


static u8 loc=0;
static u16 angle=0;

void ctrl(void)
{
    switch(loc)
    {
        case 0:angle=500; break;
        case 1:angle=1000; break;
        case 2:angle=1500; break;
        case 3:angle=2000; break;
        case 4:angle=2500; break;
    }
    loc++;
    if(loc>=4) loc=0;
    PWM_SetCompare(angle);
}

