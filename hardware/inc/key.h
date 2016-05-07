#include "stm32f10x.h"
#ifndef __KEY_H
#define __KEY_H	 
 	 

#define KEY_UP     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键:上  PC6


#define yes 		    1   //按键：上  键值
#define no  		    0   //按键：上  键值

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
