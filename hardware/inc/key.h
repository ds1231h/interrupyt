#include "stm32f10x.h"
#ifndef __KEY_H
#define __KEY_H	 
 	 

#define KEY_UP     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����:��  PC6


#define yes 		    1   //��������  ��ֵ
#define no  		    0   //��������  ��ֵ

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
