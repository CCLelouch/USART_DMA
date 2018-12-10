/**
  ******************************************************************************
  * &file    bsp_key.h
  * &author  cc
  * &version V3.1.0
  * &date    2018-11-14
  * &brief   
  ******************************************************************************
  * @attention
  * ʵ���˵͵�ƽ��Ч�ľ�����̣������������Լ�������Ч��ƽ
  * 
  ******************************************************************************
  */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_
#include "stm32f10x.h"
#include "GPIO.H"
#include "delay.h"

/**************************�����궨���޸�************************/
#define FILTERVAL            2  /* ����ֵ��ֵԽ������ʱ��Խ�� */
#define PRESSTIME            100/* ����ʱ�䳣�������峤��ʱ��   */
#define ACTIVELOGIC          0  /* 0�͵�ƽ��Ч 1�ߵ�ƽ��Ч      */
/****************************************************************/

/***************����λ��ѡ�� 1 Enable 0 Disable******************/
#define KEYSPR               0         /* separate key �������� */
#define	KEY16                1            /* ʮ��λ���󰴼����� */
/****************************************************************/

/****** KEYSPR DEFINE �û������ж������������� һ�㲻����16��*********/   ///////////////////*��֪��Ϊʲô PB�ڲ���*/////////////////////
/*�û�ʵ����Ҫ�޸�*/
#if ( KEYSPR==1 )
	#define Key1_Bus							GPIOC           
	#define Key2_Bus							GPIOC
	#define Key3_Bus							GPIOC
	#define Key4_Bus							GPIOC
	#define Key1_Pin							GPIO_Pin_1
	#define Key2_Pin							GPIO_Pin_2
	#define Key3_Pin							GPIO_Pin_3
	#define Key4_Pin							GPIO_Pin_4
	#define Key1_Bus_CLK					RCC_APB2Periph_GPIOC
	#define Key2_Bus_CLK					RCC_APB2Periph_GPIOC
	#define Key3_Bus_CLK					RCC_APB2Periph_GPIOC
	#define Key4_Bus_CLK					RCC_APB2Periph_GPIOC
#endif
/************************************************************************/

/************************ �жϰ�����Ч��ƽ **********************/   
#if   ( ACTIVELOGIC==0 )                     /* �жϰ�����Ч��ƽ*/
  #define GPIO_Mode_CLAMP GPIO_Mode_IPU /* �͵�ƽ��Ч���������� */
#elif ( ACTIVELOGIC==1 )  
  #define GPIO_Mode_CLAMP GPIO_Mode_IPD /* �͵�ƽ��Ч���������� */
#endif
/****************************************************************/

/******** ����������ʼ��&����������� �û����޸Ķ�����������Ч��ƽ�Լ������������� һ�㲻����16��**********/
#define Read_Key(GPIOx,Pin)		GPIO_ReadInputDataBit(GPIOx,Pin)              /* ��ȡ��������ֵ���ڶ������� */
#define KEYSPR_GPIOCONFIG    {GPIO_Config(Key1_Bus_CLK,Key1_Bus,Key1_Pin,GPIO_Speed_50MHz,GPIO_Mode_CLAMP);if(ACTIVELOGIC)GPIO_ResetBits(Key1_Bus,Key1_Pin);else GPIO_SetBits(Key1_Bus,Key1_Pin);\
															GPIO_Config(Key2_Bus_CLK,Key2_Bus,Key2_Pin,GPIO_Speed_50MHz,GPIO_Mode_CLAMP);if(ACTIVELOGIC)GPIO_ResetBits(Key2_Bus,Key2_Pin);else GPIO_SetBits(Key1_Bus,Key1_Pin);\
															GPIO_Config(Key3_Bus_CLK,Key3_Bus,Key3_Pin,GPIO_Speed_50MHz,GPIO_Mode_CLAMP);if(ACTIVELOGIC)GPIO_ResetBits(Key3_Bus,Key3_Pin);else GPIO_SetBits(Key1_Bus,Key1_Pin);\
															GPIO_Config(Key4_Bus_CLK,Key4_Bus,Key4_Pin,GPIO_Speed_50MHz,GPIO_Mode_CLAMP);if(ACTIVELOGIC)GPIO_ResetBits(Key4_Bus,Key4_Pin);else GPIO_SetBits(Key1_Bus,Key1_Pin);}
															
#define KEYSPR_GPIODETECTION {     if (Read_Key(Key1_Bus,Key1_Pin) == ACTIVELOGIC) return_buff = Key_1;\
															else if	(Read_Key(Key2_Bus,Key2_Pin) == ACTIVELOGIC) return_buff = Key_2;\
															else if	(Read_Key(Key3_Bus,Key3_Pin) == ACTIVELOGIC) return_buff = Key_3;\
															else if	(Read_Key(Key4_Bus,Key4_Pin) == ACTIVELOGIC) return_buff = Key_4;\
															else 																			           return_buff = Key_Up;}
/**********************************************************************************************************/

/******* KEY16  DEFINE ************************************************************************************/
//#if ( KEY16==1 )
	#define Key_Bus						 GPIOF                /*�û�ʵ����Ҫ�޸�*/
	#define Key_Bus_CLK				 RCC_APB2Periph_GPIOF /*�û�ʵ����Ҫ�޸�*/
	#define Key_Bus_L4				 (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3)
	#define Key_Bus_H4				 (GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
//#endif
/**********************************************************************************************************/

/******************** �����������****************/
typedef enum
{
	Key_Up = 0,
	Key_1 = 1,Key_2 = 2,Key_3 = 3,Key_4 = 4,
	Key_5 = 5,Key_6 = 6,Key_7 = 7,Key_8 = 8,
	Key_9 = 9,Key_10 = 10,Key_11 = 11,Key_12 = 12,
	Key_13 = 13,Key_14 = 14,Key_15 = 15,Key_16 = 16
}Key_Num;

typedef enum                 /* ����ɨ�躯������ö�� */
{
  Read = 0,        
	Scan = 1,
}Key_Scan_Operate;

typedef enum                 /* ����״̬ö�� */
{
	Up,
	Decline,
	Down,
	Rising,
}KeyState_TypeDef;
	
typedef struct{              /* ���������ṹ�� */
	enum{
		Clear = 0,	
		ShortPress = 1,
		LongPress  = 2,	
	}Press;                    /* ���������̰�״̬*/
  uint8_t Times;             /* �������´�����¼�� �û����������һ�����*/
}KeyActive_Typedef;          /* ������������ */

typedef struct
{
  Key_Num Name;              /* ������� */
	uint8_t ReadFlag :1;	     /* ���ڵ����������� */
  KeyActive_Typedef Active;  /* ��������*/
}Key_Typedef;                /* ��������   */
extern Key_Typedef KeyBuffer;/* ���������� */
/************************************************/

#endif /* _BSP_KEY_H_ */

/******************************************�û��ӿں���***************************************************/
void Key_GPIO_Config(void);                    /* ������ʼ������ */
Key_Typedef Key_Scan(Key_Scan_Operate Operate);/* ����ɨ�躯����ɨ��ģʽ�Ͷ�ģʽ��ɨ��ģʽ����ÿ5msɨ��һ�Σ�������main������������ */
void getKey(void);                             /* ��ȡ���������������� KeyBuffer ��,ÿ��ʹ�ð��������� KeyBuffer ֮ǰ������ô˺��� */
/*********************************************************************************************************/







/********************* BY CC *************END OF FILE**************************/
