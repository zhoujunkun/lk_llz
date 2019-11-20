#include<STC15.h>
//定义一个RTC数据的结构体
struct RTC_Dat
{
	unsigned char	Year;//年
	unsigned char	Month;//月
	unsigned char	Date;//日
	unsigned char	Hour;//小时
	unsigned char	Minutes;//分钟
	unsigned char	Seconds;//秒
	unsigned char	Day;//星期
	unsigned char	WP;//写保护
	unsigned char	Charger;//充电控制
	unsigned char	NC1;//在存储空间里面留出来一个字节的空间
};
//RTC初始化函数
void Ds1302_Init(void) ; 
//向RTC写入一字节数据
void Ds1302_Write_Byte(unsigned char addr, unsigned char d) ; 
//从RTC读出一字节数据
unsigned char Ds1302_Read_Byte(unsigned char addr);
//向RTC写入时钟数据
void Ds1302_Write_Time(struct RTC_Dat *RTC_D); 
//从RTC读出时钟数据
void Ds1302_Read_Time(struct RTC_Dat *RTC_D);