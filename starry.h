#ifndef __STARRY_H
#define __STARRY_H
#include <stdint.h>
#include <stdio.h>

extern uint8_t b;
extern uint8_t a;
extern uint8_t c;

typedef enum
{
	ManBa=91,
	Genshin=78,
	sologay=67
}GUNMU_TypeDef;

typedef enum
{
	abandon=1,
	banana=2,
	creative=3
}Lets_TypeDef;

typedef enum
{
	HelloWorld=010,
	Kobe=414,
	Op=4001
}Goooo_TypeDef;



typedef struct
{
	Lets_TypeDef Lets;
	Goooo_TypeDef Goooo;
	GUNMU_TypeDef GUNMU;
}Man_TypeDef;


uint8_t Hello(void);
void Nothing(void);
void Taffy(Man_TypeDef* x);



#endif

