#include "stm32f10x.h"
#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);

void BreathLED(void);

void BreathLED_Reset(void);

void ctrl(void);

void PWM2_Init(void);

void PWM_SetCompare(u16 Compare);

void ctrl_Reset(void);


#endif
