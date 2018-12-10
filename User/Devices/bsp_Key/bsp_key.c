/**
  ******************************************************************************
  * &file    bsp_key.c
  * &author  CC
	* &previous versions V2.0.0
  * &version V3.1.0
  * &date    2018-11-14
  * &brief   
  ******************************************************************************
  * &attention
  *	ʹ��ǰ����#define 	KEY16
	*					��#define		KEY4
	* Key_ReadStr.ReadFlag == 1 && Key_ReadStr.Active.Press == ShortPress ����ͬʱ����
	* ʵ���˶��������Լ�4*4������̣��Լ���Ч��ƽ�Ŀ���
  ******************************************************************************
  */
#include "bsp_key.h"

Key_Typedef KeyBuffer;

/** &brief  KEY_GPIO_Config():�û��ӿں���
	*  ʹ��ǰ�ȶ���#define KEY4
	*              #define KEY16
  *     &arg x...........
  * &retval None.
  */
void Key_GPIO_Config()
{
	#if ( KEYSPR==1	 )		/* ������������ʹ����ɢ�˿� */
    KEYSPR_GPIOCONFIG;
		GPIO_SetBits(Key_Bus,Key_Bus_L4 );
	#endif
	
	#if ( KEY16==1 )		/* ���󰴼�ֻ��ʹ�õ�һ���� */
		GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_L4 , GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
		GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_H4, GPIO_Speed_50MHz, GPIO_Mode_CLAMP);	
		GPIO_SetBits  (Key_Bus,	Key_Bus_L4 );
		GPIO_ResetBits(Key_Bus, Key_Bus_H4);
	#endif
}

/** &brief ���󰴼�ɨ����� KEY16_GPIODETECTION(void) 
	* &param  None
	*	&KeyTable:
          |--P4---P5----P6----P7--\
        P0|  1  |  2  |	 3  |	 4  | 
        P1|	 5  |	 6  |	 7  |	 8  |
        P2|	 9  |	10  |	11  |	12  |
        P3|	 13 |	14  |	15  | 16  |
          |-----------------------/
	*/	
Key_Num KEY16_GPIODETECTION(void)
{
  uint16_t BusBuff=0;
  Key_Num  calc=Key_Up;
	GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_L4 , GPIO_Speed_50MHz, GPIO_Mode_Out_PP);/*����λ���*/
	GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_H4, GPIO_Speed_50MHz, GPIO_Mode_IPU);  /*����λ����*/
	GPIO_SetBits  (Key_Bus,	Key_Bus_L4 );
	GPIO_ResetBits(Key_Bus, Key_Bus_H4);
	Delay_usms(1);
	BusBuff = Key_Bus->IDR & Key_Bus_H4 ;/*������λ ����*/	
	switch (BusBuff)
	{
	  case 0x0010: calc=Key_1;break;
		case 0x0020: calc=Key_2;break;
		case 0x0040: calc=Key_3;break;
		case 0x0080: calc=Key_4;break;
		default  : calc=Key_Up;break;
	}
	
	GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_L4 , GPIO_Speed_50MHz, GPIO_Mode_IPU);/*����λ����*/
	GPIO_Config   (Key_Bus_CLK,Key_Bus, Key_Bus_H4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);/*����λ���*/
	GPIO_SetBits  (Key_Bus,	Key_Bus_H4 );
	GPIO_ResetBits(Key_Bus, Key_Bus_L4);
	Delay_usms(1);
	BusBuff = Key_Bus->IDR & Key_Bus_L4;/*������λ ����*/
	switch (BusBuff)
	{
	  case 0x0001: calc+=0;break;
		case 0x0002: calc+=4;break;
		case 0x0004: calc+=8;break;
		case 0x0008: calc+=12;break;
		default  : calc=Key_Up;break;
	}
	return calc;
}
/** &brief getKey(void) �ײ��Ӻ���
	* &param  None
	*	&returnvalue:
			|---Name------Val---------------------------------------------------------------\
			|		Key_Up		0     |                                                           |
			|		Key_1			1     |   Key_2			2     |		Key_3			3     | 	Key_4			4     |
			|		Key_5			5     |		Key_6			6     |		Key_7			7     |		Key_8			8     |
			|   Key_9			9     |		Key_10		10    |		Key_11		11    |		Key_12		12    |
			|   Key_13		13    |		Key_14		14    |		Key_15		15    |		Key_16		16    |
			|-------------------------------------------------------------------------------/
	*/
Key_Num getKeyIO(void)
{
	Key_Num return_buff = Key_Up;//��ʼ��������ȡ������
	#if ( KEYSPR==1 )		  			//���
    KEYSPR_GPIODETECTION;     /*��ȡ���������ذ����ؼ���*/
	#endif /*KEY4*/
	#if ( KEY16==1 )
    return_buff = KEY16_GPIODETECTION();
	#endif /*KEY16*/

  return return_buff;
}

/**	
	* &brief  Key_Struct Key_Scan(Key_Scan_Operate Operate):�û��ӿں���s
	* &param  Operat Read||Scan  
	*	&returnvalue:Key_Struct
      |---Name------Val---------------------------------------------------------------\
      |   Key_Up    0     |                                                           |
      |   Key_1	    1     |   Key_2			2     |   Key_3			3     |   Key_4			4     |
      |   Key_5	    5     |   Key_6			6     |   Key_7			7     |   Key_8			8     |
      |   Key_9	    9     |   Key_10		10    |   Key_11		11    |   Key_12		12    |
      |   Key_13    13    |   Key_14		14    |   Key_15		15    |   Key_16		16    |
      |-------------------------------------------------------------------------------/
	* &attention:�˺�����Ҫÿ5-10����ˢ��һ��  
	* ʵ�ֶ̰���������������ɨ��ʽ��ⰴ������
	* Key16δ���
	* ����ɨ�躯����ɨ��ģʽ�Ͷ�ģʽ��ɨ��ģʽ����ÿ5msɨ��һ�Σ�������main������������
	*/
Key_Typedef Key_Scan(Key_Scan_Operate Operate)
{
	static KeyState_TypeDef Key_State;//����״̬ö��
	static uint16_t Counter = 0,PressCounter = 0;        //ɨ�����������
	static Key_Typedef Key_Structer;
	Key_Typedef Key_StructerBuff;
	static Key_Num ReturnVal= Key_Up;
  Key_Num Key_Buff = Key_Up;        //������ȡ������
	if(Operate == Read)               //ʵ�ְ�����ȡ�󽫶�ȡ��־λ���
	{
		Key_StructerBuff = Key_Structer;
	  Key_Structer.ReadFlag = 0;
	  return Key_StructerBuff;
	}
	Key_Buff = (Key_Num)getKeyIO();		//ÿִ��һ�κ���ֻ��һ��ֵ
	switch(Key_State)
	{
		case Up:
			if(Key_Buff != Key_Up){  //��������
        Counter++;             //����ɨ�����ֵ�ۼ�
			}
			else{                    //ĳ��ʱ���ɿ�
				Counter = 0;           //����������𣬼�¼���  
				PressCounter++;        //���������ӳ�һ����һ�μ�ֵ���ٽ���ֵ�ø�
				if(PressCounter>4)
				{
				  ReturnVal = Key_Up;
					PressCounter = 0;
				}
			}
			if(Counter>FILTERVAL){   //����������´ﵽ�˲��趨ֵ
				Counter=0;             //����ɨ�����ֵ���
			  Key_State = Decline;   //����תΪ���¹���״̬	
				Key_Structer.Active.Press = Clear;//����ȷ���̰������һ�ΰ���ʱ����յ�
				ReturnVal = (Key_Num)Key_Buff;//��׽�������½��Ӻ������ֵ
			}
			break;
			
		case Decline:
			Key_State = Down;        //����תΪ����״̬	
			Key_Structer.ReadFlag = 1;//����⵽�½��Ӻ��־��ȡλ
 			break;		
			
		case Down:
			if(Key_Buff == Key_Up){  //�����������
        Counter++;
			}
			else{
			  Counter=0;
				PressCounter ++;
				if(PressCounter> 200){
				  PressCounter = 200;
				}
				if(PressCounter>=PRESSTIME){//������������´ﵽ����ֵ		 
					Key_Structer.Active.Press = LongPress;
				}	
			}
			if(Counter>FILTERVAL){   //�����������ﵽ�˲��趨ֵ
				Counter=0;             //����ɨ�����ֵ���			
			  Key_State = Rising;    //��������
				Key_Structer.Active.Press = Clear;//����ȷ�����º��ⳤ�������һ�ε�״̬
			}
			break;	
			
		case Rising:										
			Key_State = Up;          //�����������ɱ�����һ�μ�ֵ����Ϊ�̰�Ҫ��������
			if(PressCounter<PRESSTIME>>1){
				Key_Structer.Active.Press = ShortPress;
			}
			PressCounter = 0;        //�������
			break;
		default: break;
	}
	Key_Structer.Name = ReturnVal;
	return Key_Structer;
}

void getKey()
{
  Key_Typedef Key_Structer;
	Key_Structer = Key_Scan(Read);

	KeyBuffer.Name         = Key_Structer.Name;
	KeyBuffer.ReadFlag     = Key_Structer.ReadFlag;
	KeyBuffer.Active.Press = Key_Structer.Active.Press;
}







/********************* BY CC *************END OF FILE**************************/
