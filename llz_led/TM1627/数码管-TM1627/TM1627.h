#include<STC15.h>
//��ʼ��TM1627��IO��
void	Init_TM1627(void);
//��ַ����ģʽд������
void	Show_TM1672(void);
//��ʾ��������
//�ֱ���  ����1������2������3������4�����λ�ã�ð���Ƿ���ʾ,LED��ʾ����
void	Show_Number(unsigned char N1,unsigned char N2,unsigned char N3,unsigned char N4,unsigned char D,unsigned char D2,unsigned char LED);
//��ȡ��������  �ӵ�λ����λ������ 3 2 1 
unsigned char	Read_Key(void);






