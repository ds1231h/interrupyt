/*���������ⲿ�жϵ�led��*/
/*���ܣ�		PA1�½��ش�������D2��PB8��
					PA2�����ش�������D3��PB9��*/
/*���ڣ�		2016.05.02*/
/*���ߣ�		����*/

#include"stm32f10x.h"
//����ϵͳʱ��************************************************************
void RCC_Configuration(void)
{
	/* TIM2 clock enable */ 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
 /* GPIOB clock enable */ 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
}
//����GPIO����************************************************
//���ܣ�����GPIO���������ģʽ
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                     //����һ��IO�˿ڲ����ṹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��PB�˿�ʱ��	                   					 			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;//��ʼ��PB8.9.14.15�˿�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��ת����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //���������ʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);             //��ʼ��PB8.9.14.15
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15���øߣ�����
	 
}

//�ⲿ�жϺ���*************************************************************************************
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;	              //��ʼ���ⲿ�жϼĴ���

	EXTI_ClearITPendingBit(EXTI_Line1);					  //�����1 IO���ж��������λ������жϱ�־λ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  //�����ⲿ�жϴ�������һ�����¼�������
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //�����жϴ�����ʽ���½��ش�����ʽ
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;			  //ѡ���ж���·Ϊ1����ѡ���Ǹ�IO��Ϊ�ж����룩
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //ʹ���ⲿ�ж�
	EXTI_Init(&EXTI_InitStructure);                       //��ʼ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //��GPIOA1�ҵ��ж���
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line2);					  //�����2 IO���ж��������λ������жϱ�־λ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //�����жϴ�����ʽ�������ش�����ʽ
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;			  //ѡ���ж���·Ϊ2
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //ʹ���ⲿ�ж�
	EXTI_Init(&EXTI_InitStructure);                       //��ʼ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2); //��GPIOA2�ҵ��ж���

}

//�жϷ��麯��***************************************************************
void NIVC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;                  //��ʼ���жϷ��麯��

//NVIC_PriorityGroupConfig:�������ȼ����飨����һ�䣩
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //�������ȼ����������ȼ�0���������ȼ�4λ��16����
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		 // ʹ�����õ��ⲿ�ж�ͨ������
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;     //���жϹҵ�PA1���ⲿ�ж���1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 //���������ȼ�1
	NVIC_Init(&NVIC_InitStructure);                   	 //��ʼ��
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;     //���жϹҵ�PA2���ⲿ�ж���2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	 //���������ȼ�2��Ҫ����ǰ��������ȼ�1
	NVIC_Init(&NVIC_InitStructure);                   	 //��ʼ��
	
	
}


//�жϷ�����********************************************************
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//���ж�����
	{
		//����жϴ�����
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);     //����led
		EXTI_ClearFlag(EXTI_Line1);			 //�����־�ж�λ
		EXTI_ClearITPendingBit(EXTI_Line1);	 //����ⲿ�ж���1�Ĺ���λ
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		//����жϴ�����
		GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
		EXTI_ClearFlag(EXTI_Line2);			 
		EXTI_ClearITPendingBit(EXTI_Line2);	 //����ⲿ�ж���2�Ĺ���λ
	}
}


//������***********************************************************************
int main(void)
{
	RCC_Configuration();				   //����ϵͳʱ�Ӻ���
	GPIO_Configuration();				   //����GPIO
	NIVC_Configuration();
	EXTI_Configuration();
	while(1);
}


