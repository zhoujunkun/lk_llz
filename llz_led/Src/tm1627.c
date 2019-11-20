#include  "tm1627.h"
#define	KEYINT	P37			//INT3��IO��
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

//����0-9��10�����ֵ�HEX��ʽ   ��10��������0x00,�ر�ĳ�������
unsigned char NUM_Dat[11]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0x6f,0};
//����һ���ṹ�壬����
struct 
{
	unsigned char Mod;//��ʾģʽ
	unsigned char CMD;//��������
	unsigned char Addr;//��ʾ��ַ
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
	unsigned char Show_CMD;//��ʾ��������
}Display;
//��ʼ��TM1627��IO��
void	Init_TM1627(void)
{
	P5M1 &= 0XC7;
	P5M0 &= 0XC7;
	P5M0 |= 0X18;//����P53,P54Ϊǿ���� P55��ͨ˫���
	Display.Mod = 0X01;//������ʾģʽ   5λ12��
	Display.CMD = 0X40;//������������   д���ݵ�IC����ַ�Զ�����
	Display.Addr = 0XC0;//������ʾ��ַ     00H
	Display.Show_CMD = 0X89;//��ʾ�������� ������ܣ�
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
//����ͨ�Ź���д��һ���ֽ�
void	Write_Byte_TM1672(unsigned char dat_1)
{
	unsigned char i=0;
	unsigned char Dat=0;
	Dat = dat_1;//��������ȡ����ʱ����
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
//����ͨ�Ź��򣬶�ȡһ���ֽ�
unsigned char	Read_Byte_TM1672(void)
{
	unsigned char i=0;
	unsigned char Dat=0;
	//NOP40();//��ʱ����1us���涨��ͨ�Ź���
	//DIO = 1;//51IO�����ԣ�����֮ǰ���������������IO����1�����ڽ������Ķ�ȡIO����
	Dat = 0;
	for(i=0;i<8;i++)//оƬ�Ǵӵ�λ��ʼ����ģ�������������λ����ʾʵ�ʵĵ�λ
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
//��ַ����ģʽд������
void	Show_TM1672(void)
{
	//����Ϊ��������ģʽ����ֹģʽ�л�ʱ�������
	Display.Mod = 0X01;//������ʾģʽ   5λ12��
	Display.CMD = 0X40;//������������   д���ݵ�IC����ַ�Զ�����
	Display.Addr = 0XC0;//������ʾ��ַ     00H
	Display.Show_CMD = 0X89;//��ʾ�������� ������ܣ�
	STB = 0;
	Write_Byte_TM1672(Display.Mod);//������ʾģʽ   5λ12��
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(Display.CMD);//������������   д���ݵ�IC����ַ�Զ�����
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(Display.Addr);//������ʾ��ַ     00H
	Write_Byte_TM1672(Display.Num1_H);//��ʾ����
	Write_Byte_TM1672(Display.Num1_L);//��ʾ����
	Write_Byte_TM1672(Display.Num2_H);//��ʾ����
	Write_Byte_TM1672(Display.Num2_L);//��ʾ����
	Write_Byte_TM1672(Display.Num3_H);//��ʾ����
	Write_Byte_TM1672(Display.Num3_L);//��ʾ����
	Write_Byte_TM1672(Display.Num4_H);//��ʾ����
	Write_Byte_TM1672(Display.Num4_L);//��ʾ����
	Write_Byte_TM1672(Display.LED_H);//��ʾ����
	Write_Byte_TM1672(Display.LED_L);//��ʾ����
	STB=1;NOP40();STB = 0;
	Write_Byte_TM1672(0X89);//��ʾ�������� �������
	STB = 1;
	NOP40();
}
//��ʾ��������
//�ֱ���  ����1������2������3������4�����λ�ã�ð���Ƿ���ʾ,LED��ʾ����
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
	Show_TM1672();//ˢ�������
}
//��ȡ��������  �ӵ�λ����λ������ 3 2 1
unsigned char	Read_Key(void)
{
//	unsigned char i=0;
//	unsigned char dat[5];
//	unsigned char key;
//	STB = 0;
//	Write_Byte_TM1672(0X42);//������ʾģʽ
//	NOP40();//��ʱ����1us���涨��ͨ�Ź���
//	DIO = 1;//51IO�����ԣ�����֮ǰ���������������IO����1�����ڽ������Ķ�ȡIO����
//	for(i=0;i<5;i++)
//	{
//		dat[i] = Read_Byte_TM1672();
//		DIO = 1;
//		NOP40();//��ʱ����1us���涨��ͨ�Ź���
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




