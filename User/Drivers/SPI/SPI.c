/**
  ******************************************************************************
  * &file    SPI.c
  * &author  cc
  * &version V1.0.0
  * &date    2018-08-28
  * &brief   
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */
#include "SPI.H"

#define SPI_WAIT_TIMEOUT			((uint16_t)0xFFFF)

void SPI_Config()
{
  SPI_InitTypeDef		SPI_InitStructer;

  GPIO_Config(SPI_CS_CLK,SPI_CS_Port,SPI_CS_Pin,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);       //Initialize  GPIO  NSS/CS 
  GPIO_Config(SPI_SCK_CLK,SPI_SCK_Port,SPI_SCK_Pin,GPIO_Speed_10MHz,GPIO_Mode_AF_PP);     //Initialize  GPIO  SCK 
  GPIO_Config(SPI_MISO_CLK,SPI_MISO_Port,SPI_MISO_Pin,GPIO_Speed_10MHz,GPIO_Mode_AF_PP);
  GPIO_Config(SPI_MOSI_CLK,SPI_MOSI_Port,SPI_MOSI_Pin,GPIO_Speed_10MHz,GPIO_Mode_AF_PP);
    
  SPI_I2S_DeInit( SPI_Port );			//��λSPI
  if( SPI1 == SPI_Port ){
		RCC_APB2PeriphClockCmd( SPI_CLK, ENABLE );			//SPI1��APB2�ϣ�����ӦSPIʱ��
	}
  else{
		RCC_APB1PeriphClockCmd( SPI_CLK, ENABLE );			//SPI2 3��APB1��
	}  
  
  SPI_Cmd( SPI_Port, DISABLE );		//�ر�SPI���裬����ǰ�ر�
/*--------------- Reset SPI init structure parameters values -----------------*/
  SPI_InitStructer.SPI_Direction = SPI_Direction_2Lines_FullDuplex;/* Initialize the SPI_Direction member */
  SPI_InitStructer.SPI_Mode = SPI_Mode_Master;/* initialize the SPI_Mode member */
  SPI_InitStructer.SPI_DataSize = SPI_DataSize_8b;/* initialize the SPI_DataSize member */
  SPI_InitStructer.SPI_CPOL = SPI_CPOL_Low; /* Initialize the SPI_CPOL member */
  SPI_InitStructer.SPI_CPHA = SPI_CPHA_1Edge; /* Initialize the SPI_CPHA member */
  SPI_InitStructer.SPI_NSS = SPI_NSS_Soft;/* Initialize the SPI_NSS member */
  SPI_InitStructer.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; /* ����Ƶ */ 
  SPI_InitStructer.SPI_FirstBit = SPI_FirstBit_MSB; /* ��λ�ȳ� */
  SPI_InitStructer.SPI_CRCPolynomial = 7; /* CRCУ�� */
  
  SPI_Init(SPI_Port, &SPI_InitStructer);
  SPI_Cmd (SPI_Port, ENABLE);
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t SPI_RW_Byte( uint8_t TxByte )
{
	uint8_t value = 0;
	uint16_t WaitTime_buff = 0;
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_Port, SPI_I2S_FLAG_TXE ) )		//�ȴ����ͻ�����Ϊ��
	{
		if( SPI_WAIT_TIMEOUT == ++WaitTime_buff )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	WaitTime_buff = SPI_WAIT_TIMEOUT / 2;		//�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
	SPI_Port->DR = TxByte;	//��������
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_Port, SPI_I2S_FLAG_RXNE ) )		//�ȴ����ջ������ǿ�
	{
		if( SPI_WAIT_TIMEOUT == ++WaitTime_buff )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	value = (uint8_t)SPI_Port->DR;		//��ȡ��������
  
	return value;		//����
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void SPI_RW_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	GPIO_ResetBits( SPI_CS_Port, SPI_CS_Pin);			//����Ƭѡ
	while( Length-- )
	{
		*ReadBuffer = SPI_RW_Byte( *WriteBuffer );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;				//��д��ַ��1
	}
	GPIO_SetBits( SPI_CS_Port, SPI_CS_Pin);				//����Ƭѡ
}







/********************* BY CC *************END OF FILE**************************/
