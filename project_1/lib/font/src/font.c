#include "stdio.h"
#include "font.h"

int main(int argc, char const *argv[])
{
	char *String = "test";
	Init_Font(); //初始化字库	

	//清空显示位置的背景颜色
	Clean_Area(0,  
               0,  
			   800, 
			   480,
			   0xFFFFFFFF); 	
	//显示要显示的字体
	Display_characterX(100,          
                       100,          
					   String,   
					   0xFF ,     
					   4); 		

	UnInit_Font(); 
	return 0;
}