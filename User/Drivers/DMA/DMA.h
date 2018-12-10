/**
  ************************************************************************************
  * &file    DMA_UART.c.h
  * &author  CC
  * &version V1.0.1
  * &date    2018-12-04
  * &brief   This file as a example.
  ************************************************************************************
  * &attention
  *		
	* None
  *
  ************************************************************************************
  */
#ifndef _DMA_H_
#define _DMA_H_

#include "stm32f10x.h"
#include "USART.H"

/************************************UART*********************************************/
#define DEF_DMA_USART1             1/*Set 1 To Open DMA_USART1*/
#define DEF_DMA_USART2             0/*Set 1 To Open DMA_USART2*/
#define DEF_DMA_USART3             0/*Set 1 To Open DMA_USART3*/
#define DMA_UART_TX_BUFSIZE        64/*���ڻ����������С����*/
#define DMA_UART_RX_BUFSIZE        64/*���ڻ����������С����*/
#define DMA_UART_DMABUFSIZE        64/*DMA��С����*/
//#define DMA_UART_SENDBUF_ADDR      UART_TX_BUF/*DMA��Ҫ�ķ��ʹ洢����ַ*/
//#define DMA_UART_RECEIVEBUF_ADDR   UART_RX_BUF/*DMA��Ҫ�Ľ��մ洢����ַ*/

/*---------------------------DMA_USART1~3ͨ������-�û������޸�-----------------------*/
#define DMA_UART_CLK               RCC_AHBPeriph_DMA1
#if (DEF_DMA_USART1==1)
  #define DMA_USARTx                  USART1
  #define DMA_UART_DR_ADDR           &(USART1->DR)
  #define DMA_UART_TX_CH             DMA1_Channel4/*ͨ��4*/
  #define DMA_UART_RX_CH             DMA1_Channel5/*ͨ��5*/
  #define DMA_UART_TX_FLAG_TC        DMA1_FLAG_TC4/*ͨ��4��TransferComplete��־λ*/
  #define DMA_UART_RX_FLAG_TC        DMA1_FLAG_TC5/*ͨ��5��TransferComplete��־λ*/
  #define DMA_UART_SENDBUF_ADDR      MyUSART1_Type.TX_Buff/*DMA��Ҫ�ķ��ʹ洢����ַ*/
  #define DMA_UART_RECEIVEBUF_ADDR   MyUSART1_Type.RX_Buff/*DMA��Ҫ�Ľ��մ洢����ַ*/
#endif
#if (DEF_DMA_USART2==1)
  #define DMA_USARTx                  USART2
  #define DMA_UART_DR_ADDR           &(USART2->DR)
  #define DMA_UART_TX_CH             DMA1_Channel7/*ͨ��7*/
  #define DMA_UART_RX_CH             DMA1_Channel6/*ͨ��6*/
  #define DMA_UART_TX_FLAG_TC        DMA1_FLAG_TC7/*ͨ��7��TransferComplete��־λ*/
  #define DMA_UART_RX_FLAG_TC        DMA1_FLAG_TC6/*ͨ��6��TransferComplete��־λ*/
  #define DMA_UART_SENDBUF_ADDR      MyUSART2_Type.TX_Buff/*DMA��Ҫ�ķ��ʹ洢����ַ*/
  #define DMA_UART_RECEIVEBUF_ADDR   MyUSART2_Type.RX_Buff/*DMA��Ҫ�Ľ��մ洢����ַ*/
#endif
#if (DEF_DMA_USART3==1)
  #define DMA_USARTx                  USART3
  #define DMA_UART_DR_ADDR           &(USART3->DR)
  #define DMA_UART_TX_CH             DMA1_Channel2/*ͨ��2*/
  #define DMA_UART_RX_CH             DMA1_Channel3/*ͨ��3*/
  #define DMA_UART_TX_FLAG_TC        DMA1_FLAG_TC2/*ͨ��2��TransferComplete��־λ*/
  #define DMA_UART_RX_FLAG_TC        DMA1_FLAG_TC3/*ͨ��3��TransferComplete��־λ*/
  #define DMA_UART_SENDBUF_ADDR      MyUSART3_Type.TX_Buff/*DMA��Ҫ�ķ��ʹ洢����ַ*/
  #define DMA_UART_RECEIVEBUF_ADDR   MyUSART3_Type.RX_Buff/*DMA��Ҫ�Ľ��մ洢����ַ*/
#endif
/*------------------------------------------------------------------------------------*/

void DMA_UART_Config(void);
void DMA_USART_Send(uint8_t *Buff,uint8_t cound);
uint8_t* DMA_USART_Receive(uint8_t *Buff,uint8_t cound);
void DMA_USART1_IRQHandler_SubFunction(void);/*��Ҫ��DMA���գ����ڶ�Ӧ�ж������д˺���*/
void DMA_USART2_IRQHandler_SubFunction(void);/*��Ҫ��DMA���գ����ڶ�Ӧ�ж������д˺���*/
void DMA_USART3_IRQHandler_SubFunction(void);/*��Ҫ��DMA���գ����ڶ�Ӧ�ж������д˺���*/

#endif  /*_DMA_H_*/

/************************* BY CC *************END OF FILE******************************/
