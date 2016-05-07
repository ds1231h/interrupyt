#include "led.h" 
		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                     //����һ��IO�˿ڲ����ṹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��PB�˿�ʱ��	                   					 			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;//��ʼ��PB8.9.14.15�˿�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��ת����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //���������ʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);             //��ʼ��PB8.9.14.15
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15���øߣ�����
}

//��������LED
void LED_AllOn(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15���õͣ�����
}

//Ϩ������LED
void LED_AllOff(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15���øߣ�����
}
