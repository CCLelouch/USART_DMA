/**
  ******************************************************************************
  * &file     USART.c
  * &author   CC
  * &previous version V1.0.0
  * &version  V2.0.0
  * &date     2018-11-17
  * &brief    
  ******************************************************************************
  * &attention
  * Ŀǰ����USART1-3�Ĵ��ڷ���
  * None
  * ������ж�ǧ������ printf()
  ******************************************************************************
  */
#include "USART.H"
#include "DMA.H"
#include "GPIO.H"

uint8_t UART_TX_BUF[UART_TX_BUFNUM];/*USART��ͳһ���շ��洢��*/
uint8_t UART_RX_BUF[UART_RX_BUFNUM];/*USART��ͳһ���շ��洢��*/
MyUSART_Type MyUSART1_Type,MyUSART2_Type,MyUSART3_Type;/*USART�Ķ������ô洢���������շ���*/

static void NVIC_Configuration(void)/*����USART�жϵĶ�д������*/
{
  NVIC_InitTypeDef NVIC_InitStructure;
/***********If Rename USART1 Interrupt***********/
  #ifdef USER_USART1_IRQHandler
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* Ƕ�������жϿ�������ѡ�� */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; /* ����USART1Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /* �������ȼ�*/ 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;/* �����ȼ� */ 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /* ʹ���ж� */
    NVIC_Init(&NVIC_InitStructure); /* ��ʼ������NVIC */
    
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// ʹ�ܴ��ڿ����ж�DMA
  #endif
/***********If Rename USART2 Interrupt***********/
  #ifdef USER_USART2_IRQHandler
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* Ƕ�������жϿ�������ѡ�� */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; /* ����USART2Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /* �������ȼ�*/ 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;/* �����ȼ� */ 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /* ʹ���ж� */
    NVIC_Init(&NVIC_InitStructure); /* ��ʼ������NVIC */
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);// ʹ�ܴ��ڽ����ж�		  
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);// ʹ�ܴ��ڿ����ж�DMA
  #endif
/***********If Rename USART3 Interrupt***********/
  #ifdef USER_USART3_IRQHandler
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* Ƕ�������жϿ�������ѡ�� */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; /* ����USART3Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /* �������ȼ�*/ 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;/* �����ȼ� */ 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /* ʹ���ж� */
    NVIC_Init(&NVIC_InitStructure); /* ��ʼ������NVIC */
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);// ʹ�ܴ��ڽ����ж�			
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);// ʹ�ܴ��ڿ����ж�DMA
  #endif
}

void USART_Config(void)
{ 
  USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStructure;
/******************************************* USART1 *********************************************/
  #if (DEF_USART1 == 1)
    MyUSART1_Type.BaudRate = USER_USART1_BAUDRATE;
    MyUSART1_Type.Parity   = USER_USART1_Parity;
    MyUSART1_Type.Mode     = USER_USART1_Mode;
    
    RCC_APB2PeriphClockCmd(USER_USART1_GPIO_CLK, ENABLE);// �򿪴���GPIO��ʱ��		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//USART����ʱ�� 
    #if (REMAP_USER1 == 1)
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_USART1 , ENABLE);  //USART1������ӳ��
    #endif
    GPIO_InitStructure.GPIO_Pin   = USER_USART1_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_USART1_TX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = USER_USART1_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// ��USART Rx��GPIO����Ϊ��������ģʽ
    GPIO_Init(USER_USART1_RX_GPIO_PORT, &GPIO_InitStructure);//TX��RX��������ӳ�仹��Ĭ�϶���һ��
    
    USART_InitStruct.USART_BaudRate   = MyUSART1_Type.BaudRate;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits   = USART_StopBits_1;

    USART_InitStruct.USART_Parity     = MyUSART1_Type.Parity;
    USART_InitStruct.USART_Mode       = MyUSART1_Type.Mode;//USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);
//��getchar��Ҫ�ر�*************************************************************************BUG*****/ 
   
    NVIC_Configuration();// �����ж����ȼ�����	DMA	
    
//#ifndef  STDIO_USART// ������������ڱ�׼���������,�������ж�STDIO_USART 		
////	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);// ʹ�ܴ��ڽ����ж�
//#endif    
    USART_Cmd(USART1, ENABLE);// ʹ�ܴ���	
  #endif

/******************************************* USART2 *********************************************/
  #if (DEF_USART2 == 1)
    MyUSART2_Type.BaudRate = USER_USART2_BAUDRATE;
    MyUSART2_Type.Parity   = USER_USART2_Parity;
    MyUSART2_Type.Mode     = USER_USART2_Mode;
    
    RCC_APB2PeriphClockCmd(USER_USART2_GPIO_CLK, ENABLE);// �򿪴���GPIO��ʱ��		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//USART����ʱ�� 
    #if (REMAP_USER2 == 1)
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_USART2 , ENABLE);  //USART2������ӳ��
    #endif
    GPIO_InitStructure.GPIO_Pin   = USER_USART2_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_USART2_TX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = USER_USART2_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// ��USART Rx��GPIO����Ϊ��������ģʽ
    GPIO_Init(USER_USART2_RX_GPIO_PORT, &GPIO_InitStructure);//TX��RX��������ӳ�仹��Ĭ�϶���һ��
    
    USART_InitStruct.USART_BaudRate   = MyUSART2_Type.BaudRate;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits   = USART_StopBits_1;

    USART_InitStruct.USART_Parity     = MyUSART2_Type.Parity;
    USART_InitStruct.USART_Mode       = MyUSART2_Type.Mode;//USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStruct);
    
    USART_Cmd(USART2, ENABLE);// ʹ�ܴ���	
  #endif
/******************************************* USART3 ******************************************/
  #if (DEF_USART3 == 1)
    MyUSART1_Type.BaudRate = USER_USART3_BAUDRATE;
    MyUSART1_Type.Parity   = USER_USART3_Parity;
    MyUSART1_Type.Mode     = USER_USART3_Mode;
    
    RCC_APB2PeriphClockCmd(USER_USART3_GPIO_CLK, ENABLE);// �򿪴���GPIO��ʱ��		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//USART����ʱ�� 
    #if (REMAP_USER3 == 1)//USART3  ������ӳ��
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART3 , ENABLE);  
    #elif (REMAP_USER3 == 2)//USART3  ȫ��ӳ��
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_FullRemap_USART3 , ENABLE);
    #endif
    GPIO_InitStructure.GPIO_Pin   = USER_USART3_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_USART3_TX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = USER_USART3_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// ��USART Rx��GPIO����Ϊ��������ģʽ
    GPIO_Init(USER_USART3_RX_GPIO_PORT, &GPIO_InitStructure);//TX��RX��������ӳ�仹��Ĭ�϶���һ��

    USART_InitStruct.USART_BaudRate   = MyUSART3_Type.BaudRate;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits   = USART_StopBits_1;

    USART_InitStruct.USART_Parity     = MyUSART3_Type.Parity;
    USART_InitStruct.USART_Mode       = MyUSART3_Type.Mode;//USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3, &USART_InitStruct);
            
    USART_Cmd(USART3, ENABLE);// ʹ�ܴ���	
  #endif
  NVIC_Configuration();// �����ж����ȼ�����
}


/***************************************** ���ͺ��� *******************************************/
/** &brief  USART_Send_Byte():�û��ӿں���
	*
  *     &arg x...........
  * &retval None.
  */
void USART_Send_Byte(USART_TypeDef* USARTx, uint8_t Data)
{  
  USART_SendData(USARTx, Data);
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);//ת�Ƶ���λ�Ĵ�����־λ
}

/** &brief  USART_Send_String():�û��ӿں���
	*
  *     &arg x...........
  * &retval None.
  */
void USART_Send_String(USART_TypeDef* USARTx, const uint8_t *String)
{
  do
    USART_Send_Byte(USARTx, *String++);
  while(*String!='\0');
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//����֡������־λ
}
/**********************************************************************************************/

/***************************************** ��׼���ض��� ***************************************/
#ifdef  STDIO_USART//����������ڱ�׼���������,������ж�ǧ������ printf()
  //�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
  STDIO_USART->SR &= ~USART_FLAG_TC;/*************************************/
  USART_SendData(STDIO_USART, (uint8_t) ch);/* ����һ���ֽ����ݵ����� */		
  while (USART_GetFlagStatus(STDIO_USART, USART_FLAG_TXE) == RESET);/* �ȴ�������� */
  return (ch);
}
//�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
  while (USART_GetFlagStatus(STDIO_USART, USART_FLAG_RXNE) == RESET);/* �ȴ������������� */
  USART_ClearFlag(STDIO_USART, USART_FLAG_RXNE);
  return (int)USART_ReceiveData(STDIO_USART);
}
#endif /* STDIO_USART */
/**********************************************************************************************/

/***************************************** ģ��printf  ****************************************/
void printf_usart1(char* fmt,...)/*...Ϊ����ռλ��*/
{ 
  uint8_t buffer[128];
  va_list va_params; /*����va_list���͵�ָ��va_params�����ڴ洢������ַ va��Ϊvariable-argument(�ɱ����)*/
  va_start(va_params,fmt); //��ʼ��va_paramsָ�룬ʹ��ָ���һ���ɱ�������ú�ڶ��������Ǳ���б��ǰһ�������������һ���̶�����
  vsprintf((char *)buffer,fmt,va_params);
  va_end(va_params); //��ָ��va_params��Ϊ��Ч��������εĻ�ȡ
  //������buffer���ŵļ���Ҫ������ַ������Լ���дһ����������ַ����ĺ���������ȥ����
  USART_Send_String(USART1, (uint8_t *)buffer);//�������൱��printf("%s",buffer);
}
void printf_usart2(char* fmt,...)
{ 
  uint8_t buffer[128];
  va_list va_params; 
  va_start(va_params,fmt);
  vsprintf((char *)buffer,fmt,va_params);
  va_end(va_params);
  USART_Send_String(USART2, (uint8_t *)buffer);
}
void printf_usart3(char* fmt,...)
{ 
  uint8_t buffer[128];
  va_list va_params; 
  va_start(va_params,fmt);
  vsprintf((char *)buffer,fmt,va_params);
  va_end(va_params);
  USART_Send_String(USART3, (uint8_t *)buffer);
}
/**********************************************************************************************/

/*************************** USART1 **���жϷ������������***********************************/
void USER_USART1_IRQHandler(void)
{
//  uint8_t ucTemp;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(USART1);
//    USART_SendData(USART1,ucTemp);    
//	}
  printf_usart1("int1\r\n");
  #if (DEF_DMA_USART1 == 1)
    DMA_USART1_IRQHandler_SubFunction();
  #endif  
}

void USER_USART2_IRQHandler(void)
{ 
  printf_usart2("int2\r\n");
  #if (DEF_DMA_USART2 == 1)
    DMA_USART2_IRQHandler_SubFunction();
  #endif  
}

void USER_USART3_IRQHandler(void)
{
  printf_usart3("int3\r\n");
  #if (DEF_DMA_USART3 == 1)
    DMA_USART3_IRQHandler_SubFunction();
  #endif  
}



/************************ BY CC *************END OF FILE***********************/
