//功能 ：用于测试定时器T4的文件
#include<T4_Test.h>

unsigned char T4_Count=0;//T4中断计数器
//初始化定时器T4
void Init_T4(void)
{
	//初始化T4作为MCULED指示灯
	T4T3M &= 0xDF;//12T工作模式
	T4L = 0xB0;
	T4H = 0x3C;//初始化时间  30MHZ 20MS
	//T4T3M |= 0x10;//P0.6输出T4的溢出率
	IE2 |= 0X40;//允许T4中断
	T4T3M |= 0x80;//打开T4定时器
}
//定时器T4中断服务程序
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



