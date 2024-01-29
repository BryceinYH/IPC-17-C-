#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "stm32f4xx.h"

typedef struct Time_Class  Time_Class; //先对结构体声明
typedef struct Time_Class* pTime_Class; //定义结构体的指针

typedef struct Time_Class{
	int sec;
	int min;
	int hour;
	void(*c_second)();
	void(*c_time)();
	
}Time_Class;



void TIM3_Init(u16 arr,u16 psc);
void count_second(void);
void count_time(void);
pTime_Class createTimeClass(void);
pTime_Class createTimeClassWtihArgs(int sec,int min,int hour);
#endif
