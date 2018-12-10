/**
  ******************************************************************************
  * &file    loop.c
  * &author  cc
  * &version V1.0.0
  * &date    2018-04-06
  * &brief   
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
	
#include "head.h"
#include "bsp_key.h"

void Init(void);
void Initial_Run(void);
void loop(void);




int main()
{
	Init();
	Initial_Run();
	loop();	
	return 0;
}


/***************************************** USER CODE **********************************************/
void Init(void)//硬件资源初始化
{ 
  GPIO_Config(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2,GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
  USART_Config();
  DMA_UART_Config();
  Key_GPIO_Config();
}

uint8_t a='A',ch='b';
uint8_t v='5',h='2';
void Initial_Run(void)//软件初始化函数
{

  USART_Send_String(USART2,"你好\r\n");
  DMA_USART_Send("nihao\r\n",8);
  DMA_USART_Send("wohao\r\n",8);
  printf("good %c %c\n",a,ch);
}

uint8_t buf[10];
void loop(void)				//循环主函数
{

	while(1)
	{	
//      printf_usart1("ni %c\r\n",ch);  
//      printf_usart2("ni %c\r\n",ch);
//      printf_usart3("%c %c\r\n",v,h);
//      printf("%c %c\r\n",a,ch);

//    Key_Scan(Scan);
//    PAOut(2)=0;
//    Delay_usms(1000 ms);
//    PAOut(2)=1;
//    getKey();
//    if(KeyBuffer.Name == Key_1 && KeyBuffer.ReadFlag == 1)
//    printf("ACACU=13.23/A=15.12/T=35.58"); 
    Delay_usms(800 ms);
    
    
//    printf_usart1("-->");

    DMA_USART_Receive(buf,13);
    Delay_usms(2 ms);
    DMA_USART_Send(buf,13);
    
//    DMA_USART_Send("\r\n",3);
//    printf_usart1("\r\n"); 
	}
}

/***************************************** USER CODE END ******************************************/






/**************************** BY CC ******* END OF FILE ***********************/

