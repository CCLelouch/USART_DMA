/**
  ******************************************************************************
  * &file    DMA_UART.c.c
  * &author  CC
  * &version V1.0.0
  * &date    2018-12-04
  * &brief   
  ******************************************************************************
  * &attention
  *
	* None
  *
  ******************************************************************************
  */
#include "DMA.h"
#include "USART.H"
#include <string.h>


void DMA_UART_Config()
{
/*-------------- Reset DMA init structure parameters values ------------------*/
	DMA_InitTypeDef DMA_Str; /* Initialize the DMA_PeripheralBaseAddr member */
  RCC_AHBPeriphClockCmd(DMA_UART_CLK, ENABLE);
  DMA_Str.DMA_PeripheralBaseAddr = (uint32_t)DMA_UART_DR_ADDR; /* DMAͨ�������ַ */ 
  DMA_Str.DMA_MemoryBaseAddr = (uint32_t)DMA_UART_SENDBUF_ADDR;/* DMAͨ���洢����ַ */
  
  DMA_Str.DMA_DIR = DMA_DIR_PeripheralDST;             /* ������ΪDMA��Ŀ�Ķ� */
  DMA_Str.DMA_BufferSize = 0;                          /* DMA����Ĵ�С */
  DMA_Str.DMA_PeripheralInc = DMA_PeripheralInc_Disable;/* �����ַ������ */
  DMA_Str.DMA_MemoryInc = DMA_MemoryInc_Enable;        /* �洢����ַΪ���� */
  DMA_Str.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;/* ���贫�����ݵĵ�λ */
  DMA_Str.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;/* �洢���������ݵĵ�λ�������������ͬ��*/
  DMA_Str.DMA_Mode = DMA_Mode_Circular;                /* ����ģʽ */
  DMA_Str.DMA_Priority = DMA_Priority_VeryHigh;        /* ���������ȼ� */
  DMA_Str.DMA_M2M = DMA_M2M_Disable;                   /* �ر��ڴ浽�ڴ�Ĵ��� */
	DMA_Init(DMA_UART_TX_CH, &DMA_Str);                  /*���ͳ�ʼ��*/
  DMA_Cmd(DMA_UART_TX_CH, ENABLE);
	
	DMA_Str.DMA_PeripheralBaseAddr = (uint32_t)DMA_UART_DR_ADDR; /**/
  DMA_Str.DMA_MemoryBaseAddr = (uint32_t)DMA_UART_RECEIVEBUF_ADDR ;/* Initialize the DMA_MemoryBaseAddr member */
  DMA_Str.DMA_DIR = DMA_DIR_PeripheralSRC;/* Initialize the DMA_DIR member */
  DMA_Str.DMA_BufferSize = DMA_UART_RX_BUFSIZE;/* Initialize the DMA_BufferSize member */

  DMA_Str.DMA_Priority = DMA_Priority_VeryHigh;/* Initialize the DMA_Priority member */
	DMA_Init(DMA_UART_RX_CH, &DMA_Str);//���ճ�ʼ��
  DMA_Cmd(DMA_UART_RX_CH, ENABLE);	/*ʹ�ܺ��޷��ı���Ĵ���ֵ����DMA_UART_CH->CNDTR*/
  
	USART_DMACmd(DMA_USARTx,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);/*�շ�ģʽ*/
}

void DMA_USART_Send(uint8_t *Buff,uint8_t cound)
{
  strncpy((char *)DMA_UART_SENDBUF_ADDR, (char *)Buff, cound);
  
  DMA_Cmd(DMA_UART_TX_CH, DISABLE);/*���ô������ǰҪ�ر�DMA*/
  DMA_UART_TX_CH->CNDTR = cound;/*����Ҫ����ĸ�����DMA���CNDTR--*/
	DMA_Cmd(DMA_UART_TX_CH, ENABLE);/*ʹ�ܺ�CNDTRΪֻ��*/
  
	while(DMA_GetFlagStatus(DMA_UART_TX_FLAG_TC)==RESET);/*�ȴ��������*/
	DMA_ClearFlag(DMA_UART_TX_FLAG_TC);                  /*������Ϻ���ձ�־*/
  DMA_Cmd(DMA_UART_TX_CH, DISABLE);                    /*��������ر�DMA*/
}

uint8_t* DMA_USART_Receive(uint8_t *Buff,uint8_t cound)/**/
{
  DMA_Cmd(DMA_UART_RX_CH,DISABLE);   //�ر�DMA���գ���ֹ��仹�����ݹ���
  memcpy(Buff,DMA_UART_RECEIVEBUF_ADDR,cound);
  DMA_SetCurrDataCounter(DMA_UART_RX_CH,DMA_UART_RX_BUFSIZE);    //���ô������ݳ���,��װ��,���ý��յ�ַƫַ��0��ʼ
  DMA_Cmd(DMA_UART_RX_CH,ENABLE);  //��DMA����   
	return Buff;
}

/***************************************����ڶ�Ӧ�Ĵ����ж��ڵ���*********************************/
/*--------------------------------------------DMA_USART1------------------------------------------*/
void DMA_USART1_IRQHandler_SubFunction(void)
{
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)/*���ڿ���*/
	{	
    MyUSART1_Type.STA_RX |= 1<<15;/*���յ����ݽ���15λ��һ����ʾ����������*/
    DMA_Cmd(DMA1_Channel5,DISABLE);   //�ر�DMA���գ���ֹ��仹�����ݹ���
    DMA_SetCurrDataCounter(DMA1_Channel5,DMA_UART_RX_BUFSIZE);    //���ô������ݳ���,��װ��,���ý��յ�ַƫַ��0��ʼ
    DMA_Cmd(DMA1_Channel5,ENABLE);  //��DMA����    
    USART_ClearFlag(USART1,USART_IT_IDLE);
    (void)USART1->SR;   //�ȶ�SR��Ȼ���DR�������
    (void)USART1->DR; //��USART_IT_IDLE��־
	} 
}
/*--------------------------------------------DMA_USART2------------------------------------------*/
void DMA_USART2_IRQHandler_SubFunction(void)
{
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)/*���ڿ���*/
	{	
    MyUSART2_Type.STA_RX |= 1<<15;/*���յ����ݽ���15λ��һ����ʾ����������*/
    DMA_Cmd(DMA1_Channel6,DISABLE);   //�ر�DMA���գ���ֹ��仹�����ݹ���
    DMA_SetCurrDataCounter(DMA1_Channel6,DMA_UART_RX_BUFSIZE);    //���ô������ݳ���,��װ��,���ý��յ�ַƫַ��0��ʼ
    DMA_Cmd(DMA1_Channel6,ENABLE);  //��DMA����    
    USART_ClearFlag(USART2,USART_IT_IDLE);
    (void)USART2->SR;   //�ȶ�SR��Ȼ���DR�������
    (void)USART2->DR; //��USART_IT_IDLE��־
	} 
}
/*--------------------------------------------DMA_USART3------------------------------------------*/
void DMA_USART3_IRQHandler_SubFunction(void)
{
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET)/*���ڿ���*/
	{	
    MyUSART3_Type.STA_RX |= 1<<15;/*���յ����ݽ���15λ��һ����ʾ����������*/
    DMA_Cmd(DMA1_Channel3,DISABLE);   //�ر�DMA���գ���ֹ��仹�����ݹ���
    DMA_SetCurrDataCounter(DMA1_Channel3,DMA_UART_RX_BUFSIZE);    //���ô������ݳ���,��װ��,���ý��յ�ַƫַ��0��ʼ
    DMA_Cmd(DMA1_Channel3,ENABLE);  //��DMA����    
    USART_ClearFlag(USART3,USART_IT_IDLE);
    (void)USART3->SR;   //�ȶ�SR��Ȼ���DR�������
    (void)USART3->DR; //��USART_IT_IDLE��־
	} 
}



/********************* BY CC *************END OF FILE**************************/

