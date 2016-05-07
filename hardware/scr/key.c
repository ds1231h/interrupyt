#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

								    
//按键IO初始化函数
void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;                //定义一个IO参数结构体
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;																	//输液测速器的输入io为pc6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                              //设置成下拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                                     //初始化PC6

}
u8 KEY_Scan(u8 mode)
{		  
	if(KEY_UP==1)
	{
		return yes;
	}
	else
	{
		return no;
	}
}
