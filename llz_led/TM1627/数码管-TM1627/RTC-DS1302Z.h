#include<STC15.h>
//����һ��RTC���ݵĽṹ��
struct RTC_Dat
{
	unsigned char	Year;//��
	unsigned char	Month;//��
	unsigned char	Date;//��
	unsigned char	Hour;//Сʱ
	unsigned char	Minutes;//����
	unsigned char	Seconds;//��
	unsigned char	Day;//����
	unsigned char	WP;//д����
	unsigned char	Charger;//������
	unsigned char	NC1;//�ڴ洢�ռ�����������һ���ֽڵĿռ�
};
//RTC��ʼ������
void Ds1302_Init(void) ; 
//��RTCд��һ�ֽ�����
void Ds1302_Write_Byte(unsigned char addr, unsigned char d) ; 
//��RTC����һ�ֽ�����
unsigned char Ds1302_Read_Byte(unsigned char addr);
//��RTCд��ʱ������
void Ds1302_Write_Time(struct RTC_Dat *RTC_D); 
//��RTC����ʱ������
void Ds1302_Read_Time(struct RTC_Dat *RTC_D);