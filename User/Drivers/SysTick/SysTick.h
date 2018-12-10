#ifndef _SysTick_H_
#define _SysTick_H_

#include "stm32f10x.h"
#define SysTickTime 				(SystemCoreClock/1000000-1)    /*1us,���ⲿ�����޹�. ���72m,��ôSysTickTime = 72*/

/** @defgroup Delay_usms(u32 nsms)��������
  * @{
  */
#define us									*1													 /*΢��*/
#define ms									*1000												 /*����*/


/** @defgroup Delay_Exported_Functions
  * @{
  */
void Delay_usms(u32 nsms);
void Delay(__IO uint32_t nTime);

#endif /*_DELAY_H_*/











/********************* BY CC *************END OF FILE**************************/
