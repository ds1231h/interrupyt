/*程序名：外部中断点led灯*/
/*功能：		PA1下降沿触发点亮D2（PB8）
					PA2上升沿触发点亮D3（PB9）*/
/*日期：		2016.05.02*/
/*作者：		穆沛*/

#include"stm32f10x.h"
//配置系统时钟************************************************************
void RCC_Configuration(void)
{
	/* TIM2 clock enable */ 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
 /* GPIOB clock enable */ 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
}
//配置GPIO函数************************************************
//功能：配置GPIO的输入输出模式
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个IO端口参数结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  //使能PB端口时钟	                   					 			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;//初始化PB8.9.14.15端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //翻转速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推免输出方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);             //初始化PB8.9.14.15
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15设置高，灯灭
	 
}

//外部中断函数*************************************************************************************
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;	              //初始化外部中断寄存器

	EXTI_ClearITPendingBit(EXTI_Line1);					  //清除线1 IO口中断清除挂起位（清除中断标志位）
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  //设置外部中断触发（另一种是事件触发）
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //设置中断触发方式：下降沿触发方式
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;			  //选择中断线路为1（即选择那个IO作为中断输入）
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //使能外部中断
	EXTI_Init(&EXTI_InitStructure);                       //初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); //将GPIOA1挂到中断上
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line2);					  //清除线2 IO口中断清除挂起位（清除中断标志位）
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //设置中断触发方式：上升沿触发方式
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;			  //选择中断线路为2
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //使能外部中断
	EXTI_Init(&EXTI_InitStructure);                       //初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2); //将GPIOA2挂到中断上

}

//中断分组函数***************************************************************
void NIVC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;                  //初始化中断分组函数

//NVIC_PriorityGroupConfig:设置优先级分组（下面一句）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //设置优先级：抢先优先级0个，子优先级4位（16个）
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		 // 使能设置的外部中断通道请求
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;     //将中断挂到PA1脚外部中断线1上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 //设置子优先级1
	NVIC_Init(&NVIC_InitStructure);                   	 //初始化
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;     //将中断挂到PA2脚外部中断线2上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	 //设置子优先级2，要低于前面的子优先级1
	NVIC_Init(&NVIC_InitStructure);                   	 //初始化
	
	
}


//中断服务函数********************************************************
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//有中断申请
	{
		//添加中断处理函数
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);     //点亮led
		EXTI_ClearFlag(EXTI_Line1);			 //清除标志中断位
		EXTI_ClearITPendingBit(EXTI_Line1);	 //清除外部中断线1的挂起位
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		//添加中断处理函数
		GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
		EXTI_ClearFlag(EXTI_Line2);			 
		EXTI_ClearITPendingBit(EXTI_Line2);	 //清除外部中断线2的挂起位
	}
}


//主函数***********************************************************************
int main(void)
{
	RCC_Configuration();				   //调用系统时钟函数
	GPIO_Configuration();				   //调用GPIO
	NIVC_Configuration();
	EXTI_Configuration();
	while(1);
}


