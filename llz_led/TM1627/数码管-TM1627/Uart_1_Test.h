//���Դ���0����USBת����ֱ������   9600BPS 30MHZ
#include<STC15.h>
void Init_Uart1(void);// ����: ���ڳ�ʼ������.
void Send_Data1(unsigned char dat);//COM1����һ���ֽ�
void Send_Str1(unsigned char *s);//����: COM1����һ���ַ���
//��ʱ����  ��������ʹ��
void Delay1ms(unsigned int a);	// 1ms @30.000MHz