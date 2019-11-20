#include  "tm1627.h"
#define	KEYINT	P37			//INT3的IO口
#define	DIO			P55
#define	CLK			P54
#define	STB			P53


#define DIO_READ()   HAL_GPIO_ReadPin()
#define DIO_LOW()   HAL_GPIO_WritePin()
#define DIO_HIGH()   HAL_GPIO_WritePin()

#define CLK_HIGH()  HAL_GPIO_WritePin()
#define CLK_LOW()   HAL_GPIO_WritePin()


#define STB_HIGH()  HAL_GPIO_WritePin()
#define STB_LOW()   HAL_GPIO_WritePin()

//定义0-9，10个数字的HEX格式   第10个数据是0x00,关闭某个数码管
unsigned char NUM_Dat[11]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0x6f,0};
//定义一个结构体，用于
struct 
{
	unsigned char Mod;//显示模式
	unsigned char CMD;//数据命令
	unsigned char Addr;//显示地址
	unsigned char Num1_H;
	unsigned char Num1_L;
	unsigned char Num2_H;
	unsigned char Num2_L;
	unsigned char Num3_H;
	unsigned char Num3_L;
	unsigned char Num4_H;
	unsigned char Num4_L;
	unsigned char LED_H;
	unsigned char LED_L;
	unsigned char Show_CMD;//显示控制命令
}Display;
//初始化TM1627的IO口
void	Init_TM1627(void)
{
	P5M1 &= 0XC7;
	P5M0 &= 0XC7;
	P5M0 |= 0X18;//设置P53,P54为强推挽 P55普通双向口
	Display.Mod = 0X01;//设置显示模式   5位12段
	Display.CMD = 0X40;//设置数据命令   写数据到IC，地址自动增加
	Display.Addr = 0XC0;//设置显示地址     00H
	Display.Show_CMD = 0X89;//显示控制命令 打开数码管，
	Display.Num1_H = NUM_Dat[10];
	Display.Num1_L = 0;
	Display.Num2_H = NUM_Dat[10];
	Display.Num2_L = 0;
	Display.Num3_H = NUM_Dat[10];
	Display.Num3_L = 0;
	Display.Num4_H = NUM_Dat[10];
	Display.Num4_L = 0;
	Display.LED_H = NUM_Dat[10];
	Display.LED_L = 0;
}
//按照通信规则，写入一个字节
void	Write_Byte_TM1672(unsigned char dat_1)
{
	unsigned char i=0;
	unsigned char Dat=0;
	Dat = dat_1;//把数据提取到临时变量
	for(i=0;i<8;i++)
	{
		CLK_LOW();
		NOP5();
		if(Dat&0X01)
			DIO_HIGH();
		else
			DIO_LOW();
		Dat >>= 1;
		CLK = 1;
		NOP5();
	}
}
//按照通信规则，读取一个字节
unsigned char	Read_Byte_TM1672(void)
{
	unsigned char i=0;
	unsigned char Dat=0;
	//NOP40();//延时至少1us，规定的通信规则
	//DIO = 1;//51IO口特性，由于之前是输出，所以现在IO口送1，利于接下来的读取IO数据
	Dat = 0;
	for(i=0;i<8;i++)//芯片是从低位开始输出的，所以这里的最高位，表示实际的低位
	{
		Dat <<= 1;
		CLK_LOW();
		NOP5();
		CLK_HIGH();
		NOP5();
		if(DIO_READ())
			Dat++;
	}
	return Dat;
}
//地址增加模式写入数据
void	Show_TM1672(void)
{
	//设置为连续增加模式，防止模式切换时候出问题
	Display.Mod = 0X01;//设置显示模式   5位12段
	Display.CMD = 0X40;//设置数据命令   写数据到IC，地址自动增加
	Display.Addr = 0XC0;//设置显示地址     00H
	Display.Show_CMD = 0X89;//显示控制命令 打开数码管，
	STB = 0;
	Write_Byte_TM1672(Display.Mod);//设置显示模式   5位12段
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(Display.CMD);//设置数据命令   写数据到IC，地址自动增加
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(Display.Addr);//设置显示地址     00H
	Write_Byte_TM1672(Display.Num1_H);//显示数据
	Write_Byte_TM1672(Display.Num1_L);//显示数据
	Write_Byte_TM1672(Display.Num2_H);//显示数据
	Write_Byte_TM1672(Display.Num2_L);//显示数据
	Write_Byte_TM1672(Display.Num3_H);//显示数据
	Write_Byte_TM1672(Display.Num3_L);//显示数据
	Write_Byte_TM1672(Display.Num4_H);//显示数据
	Write_Byte_TM1672(Display.Num4_L);//显示数据
	Write_Byte_TM1672(Display.LED_H);//显示数据
	Write_Byte_TM1672(Display.LED_L);//显示数据
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(0X89);//显示控制命令 打开数码管
	STB = 1;
	NOP40();
}
//显示任意数字
//分别是  数字1，数字2，数字3，数字4，点的位置，冒号是否显示,LED显示多少
void	Show_Number(unsigned char N1,unsigned char N2,unsigned char N3,unsigned char N4,unsigned char D,unsigned char D2,unsigned char LED)
{
	if(D == 1)
		Display.Num1_H = NUM_Dat[N1]|0X80;
	else
		Display.Num1_H = NUM_Dat[N1];
	Display.Num1_L = 0;
	if(D == 2)
		Display.Num2_H = NUM_Dat[N2]|0X80;
	else
		Display.Num2_H = NUM_Dat[N2];
	if(D2 == 1)
		Display.Num2_L = 0X01;
	else
		Display.Num2_L = 0;
	if(D == 3)
		Display.Num3_H = NUM_Dat[N3]|0X80;
	else
		Display.Num3_H = NUM_Dat[N3];
	if(D2 == 1)
		Display.Num3_L = 0X01;
	else
		Display.Num3_L = 0;
	if(D == 4)
		Display.Num4_H = NUM_Dat[N4]|0X80;
	else
		Display.Num4_H = NUM_Dat[N4];
	Display.Num4_L = 0;
	Display.LED_H = LED;
	Display.LED_L = 0;
	Show_TM1672();//刷新数码管
}
//读取按键程序  从低位到高位依次是 3 2 1
unsigned char	Read_Key(void)
{
//	unsigned char i=0;
//	unsigned char dat[5];
//	unsigned char key;
//	STB = 0;
//	Write_Byte_TM1672(0X42);//设置显示模式
//	NOP40();//延时至少1us，规定的通信规则
//	DIO = 1;//51IO口特性，由于之前是输出，所以现在IO口送1，利于接下来的读取IO数据
//	for(i=0;i<5;i++)
//	{
//		dat[i] = Read_Byte_TM1672();
//		DIO = 1;
//		NOP40();//延时至少1us，规定的通信规则
//	}
//	STB = 1;
//	key = 0;
//	dat[1] >>= 4;
//	key += dat[1];//KEY1 
//	key <<= 1;
//	dat[3] >>= 6;
//	key += dat[3]>>1;
//	key <<= 1;
//	dat[3] &= 1;
//	key += dat[3];
//	return key;
}
//




