#include<STC15.h>
//初始化TM1627的IO口
void	Init_TM1627(void);
//地址增加模式写入数据
void	Show_TM1672(void);
//显示任意数字
//分别是  数字1，数字2，数字3，数字4，点的位置，冒号是否显示,LED显示多少
void	Show_Number(unsigned char N1,unsigned char N2,unsigned char N3,unsigned char N4,unsigned char D,unsigned char D2,unsigned char LED);
//读取按键程序  从低位到高位依次是 3 2 1 
unsigned char	Read_Key(void);






