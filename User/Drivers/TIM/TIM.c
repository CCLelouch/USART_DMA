/**
  ******************************************************************************
  * &file    TIM.c
  * &author  CC
	* &previous versions V1.0.0\
  * &version V1.2.0
  * &date    2018-03-19
  * &brief   TIM2 TIM3 ALL PWM
  ******************************************************************************
  * &attention
  *
	* None
  *
  ******************************************************************************
  */

#include "TIM.h"




/*
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
*/

/**
  * &brief  TIM2_Config(u16 arr,u16 psc):
  * &param  arr:�������� �Զ���װֵ�� 
  * &param  psc:Ԥ��Ƶ
  * &retval None.
  * &attention:�� arr=10-1,psc=7200-1ʱ���ж�ʱ��Ϊ1ms Time = (arr+1)(psc+1)/TCLK
  */
void TIM2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd  (RCC_APB1Periph_TIM2,ENABLE);       //�򿪶�ʱ��ʱ����		
	TIM_TimeBaseInitStruct.TIM_Period = arr;                    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;                 //Ԥ��Ƶ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ����Ϊ0 ETR,TIX
	TIM_TimeBaseInit        (TIM2,&TIM_TimeBaseInitStruct);		
	TIM_ITConfig            (TIM2,TIM_IT_Update,ENABLE);        //ʹ���ж�Դ
	TIM_Cmd                 (TIM2,ENABLE);//ʹ�ܼ�����;
}

/**
  * &brief  TIM3_Config(u16 arr,u16 psc):
  * &param  arr:�������� �Զ���װֵ�� 
  * &param  psc:Ԥ��Ƶ
  * &retval None.
  * &attention:�� arr=10-1,psc=7200-1ʱ���ж�ʱ��Ϊ1ms Time = (arr+1)(psc+1)/TCLK
  */
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd  (RCC_APB1Periph_TIM3,ENABLE);       //�򿪶�ʱ��ʱ����		
	TIM_TimeBaseInitStruct.TIM_Period = arr;                    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;                 //Ԥ��Ƶ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ����Ϊ0 ETR,TIX ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInit        (TIM3,&TIM_TimeBaseInitStruct);	
//	TIM_ITConfig            (TIM3,TIM_IT_Update,ENABLE);        //ʹ���ж�Դ	
	
//	TIM_Cmd                 (TIM3,ENABLE);//ʹ�ܼ�����;
}

/************************************************** PWM ***************************************************/
void PWM_Config(TIM_TypeDef * TIMx, uint16_t TIM_OCMode, uint8_t OCx, uint16_t TIM_OCPolarity, uint16_t TIM_OutputState)
{
//	TIM_Cmd                 (TIMx,DISABLE);              //�������ر�;ǰ��ĺ�����TIM3_Init(u16 arr,u16 psc)
	TIM_OCInitTypeDef TIM_OCInitStruct;                    //ͨ�����ƼĴ�������
	TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM2;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState;
  TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct.TIM_Pulse        = 0x0000;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity;
  TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Reset;
  TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	if(OCx&0x01 == TURE)
	{
		TIM_OC1Init             (TIMx, &TIM_OCInitStruct);
		TIM_OC1PreloadConfig    (TIMx, TIM_OCPreload_Enable);//CCMRxԤ��װ��ʹ��,���ı����ں��¸����ڲ�ִ��
	}
	if(OCx>>1&1 == TURE)
	{
		TIM_OC2Init             (TIMx, &TIM_OCInitStruct);
		TIM_OC2PreloadConfig    (TIMx, TIM_OCPreload_Enable);//CCMRxԤ��װ��ʹ��,���ı����ں��¸����ڲ�ִ��
	}
	if(OCx>>2&1 == TURE)
	{
		TIM_OC3Init             (TIMx, &TIM_OCInitStruct);
		TIM_OC3PreloadConfig    (TIMx, TIM_OCPreload_Enable);//CCMRxԤ��װ��ʹ��,���ı����ں��¸����ڲ�ִ��
	}
	if(OCx>>3&1 == TURE)
	{
		TIM_OC4Init             (TIMx, &TIM_OCInitStruct);
		TIM_OC4PreloadConfig    (TIMx, TIM_OCPreload_Enable);//CCMRxԤ��װ��ʹ��,���ı����ں��¸����ڲ�ִ��
	}

	TIM_ARRPreloadConfig    (TIMx, ENABLE);              //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
//z 	TIM_Cmd                 (TIMx, ENABLE);                  //ʹ�ܼ�����;
}

/**
  * &brief  TIM2_PWM_Init()
  * &param  uint8_t OCx, u16 arr,u16 psc:  
  *     &arg x...........
  * &retval None.
  * &attention:
  */
void TIM2_PWM_Init(uint8_t OCx, u16 arr,u16 psc)
{	
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_AFIO, ENABLE);      //AFIO��ɫ���ܼĴ���ʱ��ʹ��
	GPIO_PinRemapConfig     (GPIO_PartialRemap1_TIM2 , ENABLE);  //��ʱ��TIM2������ӳ��
	TIM2_Init               (arr,psc);//���ö�ʱ��
	
if(OCx   &1 == TURE)
	{
		PWM_Config            (TIM2, TIM_OCMode_PWM2,  OC1, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH1
	  GPIO_Config           (RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_15,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO
	}
if(OCx>>1&1 == TURE)
	{
		PWM_Config            (TIM2, TIM_OCMode_PWM2,  OC2, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH2
		GPIO_Config           (RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_3, GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO
	}
if(OCx>>2&1 == TURE)
	{
		PWM_Config            (TIM2, TIM_OCMode_PWM2,  OC3, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH3
		GPIO_Config           (RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2, GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO
	}
if(OCx>>3&1 == TURE)
	{
		PWM_Config            (TIM2, TIM_OCMode_PWM2,  OC4, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH4
		GPIO_Config           (RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_3, GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO
	}
}

 /**
  * &brief  TIM3_PWM_Init(uint8_t OCx, u16 arr,u16 psc)
  * &param  uint8_t OCx, u16 arr,u16 psc:  
  *     &arg x...........
  * &retval None.
  * &attention:
  */
void TIM3_PWM_Init(uint8_t OCx, u16 arr,u16 psc)
{
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_AFIO, ENABLE);        //AFIO��ɫ���ܼĴ���ʱ��ʹ��
	GPIO_PinRemapConfig     (GPIO_Remap_SWJ_JTAGDisable , ENABLE); /*************************/

	GPIO_PinRemapConfig     (GPIO_PartialRemap_TIM3 , ENABLE);    //��ʱ��TIM3������ӳ��
	TIM3_Init								(arr,psc);													  //TIM3��ʱ������

if(OCx   &1 == TURE)
	{
		PWM_Config            (TIM3, TIM_OCMode_PWM2,  OC1, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH1
		GPIO_Config           (RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO CH1
//	GPIO_Config             (RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO CH1
	}
if(OCx>>1&1 == TURE)
	{
		PWM_Config            (TIM3, TIM_OCMode_PWM2,  OC2, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH2
		GPIO_Config           (RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO CH2
	}
if(OCx>>2&1 == TURE)
	{
		PWM_Config            (TIM3, TIM_OCMode_PWM2,  OC3, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH3
		GPIO_Config           (RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO CH3
	}
if(OCx>>3&1 == TURE)
	{
		PWM_Config            (TIM3, TIM_OCMode_PWM2,  OC4, TIM_OCPolarity_Low, TIM_OutputState_Enable);//PWM���� CH4
		GPIO_Config           (RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);//����GPIO CH4
	}
}




/********************* BY CC *************END OF FILE**************************/


