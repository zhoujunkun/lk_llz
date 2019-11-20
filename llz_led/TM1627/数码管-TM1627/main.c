//STC15W4K56S4  内部震荡 27MHZ 
//用于内部测试功能
#include<T4_Test.h>
#include<Uart_1_Test.h>
#include<TM1627.h>

extern struct  Display;
unsigned char TM1627_Key=0;
void main(void)
{
	SP = 0X81;//把堆栈的地址指向0x81
	P0M1=0;P0M0=0;P1M1=0;P1M0=0;
	P2M1=0;P2M0=0;P3M1=0;P3M0=0;
	P4M1=0;P4M0=0;P5M1=0;P5M0=0;//上电初始化所有IO口为普通IO
	Init_T4();//初始化板载LED灯
	Init_Uart1();//初始化串口 9600bps 27MHZ
	EA =1;//打开全局中断
	Init_TM1627();//初始化TM1627
	Delay1ms(5);//上电等待一会，让晶振更稳定
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












