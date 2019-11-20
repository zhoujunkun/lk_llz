#include<RTC-DS1302Z.h>
sbit SCK = P4^0;
sbit IO  = P4^1;
sbit RST = P4^2;//����ӿ�����
struct RTC_Dat RTC_Data;//RTC����������
unsigned char *RTC_Data_P=&RTC_Data.Year;//����һ��ָ�룬���ڲ���RTC����������


//RTC��ʼ������
void Ds1302_Init(void) 
{
	RST=0;			//RST���õ�
	SCK=0;			//SCK���õ�
	IO = 0;
}
//��RTCд��һ�ֽ�����
void Ds1302_Write_Byte(unsigned char addr, unsigned char d) 
{
	unsigned char i;
	unsigned char dat;
	RST=1;//����DS1302����	
	//д��Ŀ���ַ��addr
	dat = addr;//ע�⣬��д�ĵ�ַ
	for(i=0;i<8;i++) 
	{	
		if(dat & 0x01) 
			IO=1;
		else 
			IO=0;
		SCK=1;//����ʱ��
		NOP(27);
		SCK=0;
		NOP(27);
		dat >>= 1;
	}	
	//д�����ݣ�d
	dat = d;
	for(i=0;i<8;i ++)
	{
		if(dat&0x01) 
			IO=1;
		else 
			IO=0;
		SCK=1;//����ʱ��
		NOP(27);
		SCK=0;
		NOP(27);
		dat >>= 1;
	}
	RST=0;		//ֹͣDS1302����
}
//��RTC����һ�ֽ�����
unsigned char Ds1302_Read_Byte(unsigned char addr) 
{
	unsigned char i=0;	
	unsigned char dat;
	RST=1;//����DS1302����
	//д��Ŀ���ַ��addr
	dat = addr;//ע�⣬�Ƕ��ĵ�ַ
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
	IO=1;//51,IO�ڵ����ԣ���Ϊ��һ���غ������������������Ϊ���룬��������1������ȷ��ȡ�ⲿ״̬
	dat = 0;
	//������ݣ�dat
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
	RST=0;					//ֹͣDS1302����
	return dat;
}
//��RTCд��ʱ������
void Ds1302_Write_Time(struct RTC_Dat *RTC_D) 
{
	Ds1302_Write_Byte(0x8E,0X00);//�ر�д����
	Ds1302_Write_Byte(0x80,RTC_D->Seconds);
	Ds1302_Write_Byte(0x82,RTC_D->Minutes);
	Ds1302_Write_Byte(0x84,RTC_D->Hour);
	Ds1302_Write_Byte(0x86,RTC_D->Date);
	Ds1302_Write_Byte(0x88,RTC_D->Month);
	Ds1302_Write_Byte(0x8A,RTC_D->Day);
	Ds1302_Write_Byte(0x8C,RTC_D->Year);
	Ds1302_Write_Byte(0x90,RTC_D->Charger);//�޸ĳ��״̬
	Ds1302_Write_Byte(0x8E,0X80);//��д����
}
//��RTC����ʱ������
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






