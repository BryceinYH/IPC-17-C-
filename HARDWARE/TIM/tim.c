#include "tim.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "oled.h"
#include "string.h"
#include "stdlib.h"

//void count_second();
//void count_time();

void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_BaseInitStrecturs;
  NVIC_InitTypeDef NVIC_InitStrecturs;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//
	TIM_BaseInitStrecturs.TIM_Period = arr - 1;
  TIM_BaseInitStrecturs.TIM_Prescaler = psc-1;
	TIM_BaseInitStrecturs.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_BaseInitStrecturs.TIM_ClockDivision =  TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_BaseInitStrecturs);
	
	
	NVIC_InitStrecturs.NVIC_IRQChannel  = TIM3_IRQn;
	NVIC_InitStrecturs.NVIC_IRQChannelPreemptionPriority = 0X00;
	NVIC_InitStrecturs.NVIC_IRQChannelSubPriority = 0X00;
	NVIC_InitStrecturs.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStrecturs);
	
	//定时器使能
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//定时器打开
	TIM_Cmd(TIM3,ENABLE);
	
}

pTime_Class pthis = NULL;//全局pthis指针
/** 
  * @brief 无参构造函数
  */

pTime_Class createTimeClass(void){
	pTime_Class time = (pTime_Class)malloc(sizeof(Time_Class));//给结构体空间
	if(time==NULL)
	{
		return NULL;
	}
	time -> sec = 0;
	time -> min = 0;
  time -> hour = 0;
	time -> c_second = count_second; 
	time -> c_time   = count_time;
	pthis = time;
	
	return time;
}
/** 
  * @brief 有参构造函数
  */
pTime_Class createTimeClassWtihArgs(int sec,int min,int hour){
	pTime_Class time = createTimeClass();
	if(time==NULL)
	{
		return NULL;
	}
	pthis ->sec = sec;
	pthis ->min = min;
	pthis ->hour =hour;
	return time;

}

void count_second(void)
{
	pthis -> sec++;
}

void count_time(void)
{
	if(pthis -> sec >=60)
	{
		pthis -> min++;
		pthis -> sec = 0;
	}
	if(pthis -> min >=60)
	{
		pthis -> hour++;
		pthis -> min = 0;
	}
	if(pthis -> hour >=24)
	{
		pthis -> hour = 0;
	}
}	
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		pthis -> sec++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
	}
}

