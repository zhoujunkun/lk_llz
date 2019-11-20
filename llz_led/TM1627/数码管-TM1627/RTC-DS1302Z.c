#include<RTC-DS1302Z.h>
sbit SCK = P4^0;
sbit IO  = P4^1;
sbit RST = P4^2;//定义接口线序
struct RTC_Dat RTC_Data;//RTC交换的数据
unsigned char *RTC_Data_P=&RTC_Data.Year;//定义一个指针，用于操作RTC交换的数据


//RTC初始化函数
void Ds1302_Init(void) 
{
	RST=0;			//RST脚置低
	SCK=0;			//SCK脚置低
	IO = 0;
}
//向RTC写入一字节数据
void Ds1302_Write_Byte(unsigned char addr, unsigned char d) 
{
	unsigned char i;
	unsigned char dat;
	RST=1;//启动DS1302总线	
	//写入目标地址：addr
	dat = addr;//注意，是写的地址
	for(i=0;i<8;i++) 
	{	
		if(dat & 0x01) 
			IO=1;
		else 
			IO=0;
		SCK=1;//产生时钟
		NOP(27);
		SCK=0;
		NOP(27);
		dat >>= 1;
	}	
	//写入数据：d
	dat = d;
	for(i=0;i<8;i ++)
	{
		if(dat&0x01) 
			IO=1;
		else 
			IO=0;
		SCK=1;//产生时钟
		NOP(27);
		SCK=0;
		NOP(27);
		dat >>= 1;
	}
	RST=0;		//停止DS1302总线
}
//从RTC读出一字节数据
unsigned char Ds1302_Read_Byte(unsigned char addr) 
{
	unsigned char i=0;	
	unsigned char dat;
	RST=1;//启动DS1302总线
	//写入目标地址：addr
	dat = addr;//注意，是读的地址
	for(i=0;i<8;i++) 
	{
		if(dat & 0x01) 
			IO=1;
		else 
			IO=0;
		SCK=1;
		NOP(27);
		SCK=0;
		NOP(27);	
		dat >>= 1;
	}
	IO=1;//51,IO口的特性，因为上一个回合是输出，接下来想作为输入，必须先置1才能正确读取外部状态
	dat = 0;
	//输出数据：dat
	for(i=0;i<8;i++) 
	{
		dat >>= 1;
		if(IO)
			dat |= 0x80;
		else 
			dat &= 0x7F;
		SCK=1;
		NOP(27);	
		SCK=0;
		NOP(27);	
	}	
	RST=0;					//停止DS1302总线
	return dat;
}
//向RTC写入时钟数据
void Ds1302_Write_Time(struct RTC_Dat *RTC_D) 
{
	Ds1302_Write_Byte(0x8E,0X00);//关闭写保护
	Ds1302_Write_Byte(0x80,RTC_D->Seconds);
	Ds1302_Write_Byte(0x82,RTC_D->Minutes);
	Ds1302_Write_Byte(0x84,RTC_D->Hour);
	Ds1302_Write_Byte(0x86,RTC_D->Date);
	Ds1302_Write_Byte(0x88,RTC_D->Month);
	Ds1302_Write_Byte(0x8A,RTC_D->Day);
	Ds1302_Write_Byte(0x8C,RTC_D->Year);
	Ds1302_Write_Byte(0x90,RTC_D->Charger);//修改充电状态
	Ds1302_Write_Byte(0x8E,0X80);//打开写保护
}
//从RTC读出时钟数据
void Ds1302_Read_Time(struct RTC_Dat *RTC_D)  
{
	RTC_D->Seconds = Ds1302_Read_Byte(0X81);
	RTC_D->Minutes = Ds1302_Read_Byte(0X83);
	RTC_D->Hour = Ds1302_Read_Byte(0X85);
	RTC_D->Date = Ds1302_Read_Byte(0X87);
	RTC_D->Month = Ds1302_Read_Byte(0X89);
	RTC_D->Day = Ds1302_Read_Byte(0X8B);
	RTC_D->Year = Ds1302_Read_Byte(0X8D);
	RTC_D->WP = Ds1302_Read_Byte(0X8F);
	RTC_D->Charger = Ds1302_Read_Byte(0X91);
}






