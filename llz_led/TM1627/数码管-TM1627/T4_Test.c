//���� �����ڲ��Զ�ʱ��T4���ļ�
#include<T4_Test.h>

unsigned char T4_Count=0;//T4�жϼ�����
//��ʼ����ʱ��T4
void Init_T4(void)
{
	//��ʼ��T4��ΪMCULEDָʾ��
	T4T3M &= 0xDF;//12T����ģʽ
	T4L = 0xB0;
	T4H = 0x3C;//��ʼ��ʱ��  30MHZ 20MS
	//T4T3M |= 0x10;//P0.6���T4�������
	IE2 |= 0X40;//����T4�ж�
	T4T3M |= 0x80;//��T4��ʱ��
}
//��ʱ��T4�жϷ������
void T4_INT(void) interrupt 20
{
	T4_Count++;
	if(T4_Count > 5)
	{
		T4_Count = 0;
		MCU_LED1 = ~MCU_LED1;
		MCU_LED2 = ~MCU_LED1;
	}
}



