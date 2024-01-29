#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "stdio.h"
#include "math.h"
#include "OLED.h"
#include "math.h"
#include "icm20602.h"
#include "tim.h"


//#define Per_Class(object)  (pthis = (object))
int main(void)
{  
	delay_init(168);
	uart_init(9600);
	LED_Init();
	OLED_Init();
	icm20602_init();
	TIM3_Init(10000,8400);
	OLED_Clear();
	
	Time_Class* originTime = createTimeClassWtihArgs(0,0,0);
	
	while (1)
	{
		
		originTime -> c_time();
	
		OLED_ShowNum(1,7,originTime->sec,2);
		OLED_ShowChar(1,6,':');
		OLED_ShowNum(1,4,originTime->min,2);
		OLED_ShowChar(1,3,':');
		OLED_ShowNum(1,1,originTime->hour,2);	
		
	}

}
