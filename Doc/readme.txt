������Ϊ�������������ܹ���������������ж��佨ֵ�����̰����ȡ�

���ð��������裺
1��Key_GPIO_Config(void);//������ʼ������
2��Key_Typedef Key_Scan(Key_Scan_Operate Operate);//����ɨ�躯����ɨ��ģʽ�Ͷ�ģʽ��ɨ��ģʽ����ÿ5msɨ��һ�Σ�������main������������
3��void getKey(void);//��ȡ���������������� KeyBuffer ��,ÿ��ʹ�ð��������� KeyBuffer ֮ǰ������ô˺���
4���ж����½ṹ��
	KeyBuffer.Name == Key_Up||Key_1...;
	KeyBuffer.ReadFlag  == 1;//1��ʾ�������£��ڰ�������ʱ��һ�����ҵ����ú���getKey(void);�󣬶�ȡ���������
	KeyBuffer.Active.Press == LongPress||ShortPress ;
	KeyBuffer.Active.Time 




void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update) !=RESET )
	{
    Key_Scan(Scan);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
	
	
	
	