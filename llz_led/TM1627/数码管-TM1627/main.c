//STC15W4K56S4  �ڲ��� 27MHZ 
//�����ڲ����Թ���
#include<T4_Test.h>
#include<Uart_1_Test.h>
#include<TM1627.h>

extern struct  Display;
unsigned char TM1627_Key=0;
void main(void)
{
	SP = 0X81;//�Ѷ�ջ�ĵ�ַָ��0x81
	P0M1=0;P0M0=0;P1M1=0;P1M0=0;
	P2M1=0;P2M0=0;P3M1=0;P3M0=0;
	P4M1=0;P4M0=0;P5M1=0;P5M0=0;//�ϵ��ʼ������IO��Ϊ��ͨIO
	Init_T4();//��ʼ������LED��
	Init_Uart1();//��ʼ������ 9600bps 27MHZ
	EA =1;//��ȫ���ж�
	Init_TM1627();//��ʼ��TM1627
	Delay1ms(5);//�ϵ�ȴ�һ�ᣬ�þ�����ȶ�
	Send_Str1("OK");
	while(1)
	{
		if(INT0 == 0)
		{
			Delay1ms(100);
			if(INT0 == 0)
			{
				Show_Number(2,0,1,7,0,0,0x00);
			
				
			}
		}
		if(INT1 == 0)
		{
			Delay1ms(100);
			if(INT1 == 0)
			{
				
				Send_Data1(0X77);
			}
		}
		if(P37 == 0)
		{
			TM1627_Key = Read_Key();
			Send_Data1(TM1627_Key);
			Send_Data1(0X88);
			Delay1ms(800);
		}
		
	}
}












