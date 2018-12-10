/**
  ******************************************************************************
  * &file    delay.c
  * &author  cc
  * &version V1.0.0
  * &date    2018-08-29
  * &brief   
  ******************************************************************************
  * @attention
  * �κ���Ҫ��� stm32f10x_if.h
  * ������CM3,CM4 ����Systic��ʱ������ʱ����.Systic��ʱ����˯����Ҳ���Թ���
  ******************************************************************************
  */
#include "delay.h"


/**
	* &brief TimingDelay��ʱ���������ú���
	*	- void SysTick_Handler(),void Delay(__IO uint32_t nTime)
	*/
static __IO uint32_t TimingDelay;

/**
	*
	*/
	
	
/**
	* &brief  Delay() 
	* &param  nTimes: ѭ������
	*     &arg ns: us<2^32,
	*			&arg ms: ms<2^32/1000
	* &retval  None
	*/

void Delay_usms(u32 nTimes)
{
	SysTick->LOAD  = SysTickTime;																/*װ��Systick��ʱ��*/
	SysTick->VAL   = 0x00;																			/*��յ�ǰ�Ĵ���*/
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |								/*����ʱ��ΪFCLK*/
									 SysTick_CTRL_ENABLE_Msk;										/*�򿪶�ʱ��*/
	while(nTimes != 0)																			 	  /*ѭ����ʱ����*/
	{
	  nTimes--;
		while(!((SysTick->CTRL)&(SysTick_CTRL_COUNTFLAG_Msk)));   /*ѭ���жϱ�־λ*/	
	}
	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;						    /*�رն�ʱ��*/
}

/**
	* &brief  Delay function which using SysTic_Hander()
	* &param  nTime   The number of times 
	*     &arg
	*
	* - ʹ��Ĭ������������SysTick_Config(SystemCoreClock / 1000000)//systickʱ��ΪHCLK/FCLK,
	* - �ж�ʱ����Ϊ1us
	* - ÿһ��TimingDelay�仯��ʱΪSystic�ļ���ʱ��
	*/
void Delay_Init()
{
	SysTick_Config(SysTickTime);
}


/**
	* &brief  Delay function which using SysTic_Hander()
	* &param  nTime   The number of times 
	*     &arg
	*
	* - ʹ��Ĭ������������SysTick_Config(SystemCoreClock / 1000000)//systickʱ��ΪHCLK/FCLK,
	* - �ж�ʱ����Ϊ1us
	* - ÿһ��TimingDelay�仯��ʱΪSystic�ļ���ʱ��
	*/
//void Delay_usms(__IO uint32_t nTime)
//{
//	TimingDelay = nTime;
//	while(TimingDelay != 0x00);
//}

/**
	* &brief  Interrupt every time when Systick exception
	* &param  None
	*
	* - ʹ��Ĭ������������SysTick_Config(SystemCoreClock / 1000000)//systickʱ��ΪHCLK/FCLK,
	* - �ж�ʱ����Ϊ1ms
	* - ÿһ��TimingDelay�仯��ʱΪSystic�ļ���ʱ��
	* - �޸�stm32f10x_it.c
	*/
void Delay_SysTick(void)
{
	if(TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}















/********************* BY CC *************END OF FILE**************************/
