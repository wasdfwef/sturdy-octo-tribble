#include "stdio.h"
#include "font.h"

int main(int argc, char const *argv[])
{
	char *String = "test";
	Init_Font(); //��ʼ���ֿ�	

	//�����ʾλ�õı�����ɫ
	Clean_Area(0,  
               0,  
			   800, 
			   480,
			   0xFFFFFFFF); 	
	//��ʾҪ��ʾ������
	Display_characterX(100,          
                       100,          
					   String,   
					   0xFF ,     
					   4); 		

	UnInit_Font(); 
	return 0;
}