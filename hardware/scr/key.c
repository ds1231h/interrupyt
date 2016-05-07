#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

								    
//����IO��ʼ������
void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;                //����һ��IO�����ṹ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTCʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;																	//��Һ������������ioΪpc6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                              //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);                                     //��ʼ��PC6

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
