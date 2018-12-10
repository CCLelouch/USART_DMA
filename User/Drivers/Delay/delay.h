#ifndef _DELAY_H_
#define _DELAY_H_

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
void Delay_Init(void);
void Delay_usms(__IO uint32_t nTime);
void Delay_SysTick(void);


#endif /*_DELAY_H_*/









/********************* BY CC *************END OF FILE**************************/
