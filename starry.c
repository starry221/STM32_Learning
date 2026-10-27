#include <stdio.h>
#include <stdint.h>
#include "starry.h"
uint8_t b=0;
uint8_t a=0;
uint8_t c=0;

uint8_t Hello(void)
{
	printf("沃操，棍母！\n");
	if(b==a)
	{
		for(b=10;b>a;b--)
		{
			a++;
		}
	}
	return b;
}


void Nothing(void)
{
	if(Hello()==5)
	{
		printf("还有第二关？！\n"); 
	} 
}

void Taffy(Man_TypeDef* x)
{
	a=x->Lets;
	b=x->Goooo;
	c=x->GUNMU;	
}
















